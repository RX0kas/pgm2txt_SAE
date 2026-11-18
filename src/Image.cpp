#include "Image.h"

#include <cctype>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <string>

void skipCommentsAndWhitespace(std::istream &file) {
	int c;
	while ((c = file.peek()) != std::char_traits<char>::eof()) {
		if (c == '#') {
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		} else if (std::isspace(static_cast<unsigned char>(c))) {
			file.get();
		} else {
			break;
		}
	}
}

unsigned long readHeaderValue(std::istream &file, const std::string &name) {
	skipCommentsAndWhitespace(file);
	long value = 0;
	if (!(file >> value) || value <= 0) {
		throw std::runtime_error("Invalid PGM header: bad " + name);
	}
	return static_cast<unsigned long>(value);
}

Image::Image(const std::filesystem::path &fileName) {
	std::ifstream file(fileName, std::ios::binary);
	if (!file.is_open()) {
		throw std::runtime_error("Unable to open file \"" + fileName.string() + "\"");
	}

	std::string magicNumber;
	skipCommentsAndWhitespace(file);
	file >> magicNumber;
	if (magicNumber != "P2" && magicNumber != "P5") {
		throw std::runtime_error("Unsupported or invalid PGM format (magic number: \"" + magicNumber + "\")");
	}

	const unsigned long width = readHeaderValue(file, "width");
	const unsigned long height = readHeaderValue(file, "height");
	const unsigned long maxValue = readHeaderValue(file, "max value");
	if (maxValue > 255) {
		throw std::runtime_error("16-bit PGM files (max value > 255) are not supported");
	}

	setColumnNumber(width);
	setRowNumber(height);
	setMaxGreyLevel(maxValue);

	const std::size_t count = width * height;
	m_pixelData.resize(count);

	if (magicNumber == "P5") {
		file.get();
		file.read(reinterpret_cast<char *>(m_pixelData.data()), static_cast<std::streamsize>(count));
		if (file.gcount() != static_cast<std::streamsize>(count)) {
			throw std::runtime_error("Truncated PGM file: expected " + std::to_string(count) +
			                         " pixels, got " + std::to_string(file.gcount()));
		}
	} else {
		for (std::size_t i = 0; i < count; ++i) {
			unsigned long value = 0;
			if (!(file >> value) || value > maxValue) {
				throw std::runtime_error("Invalid or missing pixel value at index " + std::to_string(i));
			}
			m_pixelData[i] = static_cast<uint8_t>(value);
		}
	}
}
