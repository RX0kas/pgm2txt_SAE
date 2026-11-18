#include "decoder.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

std::vector<std::string> loadPalette(const std::filesystem::path &path) {
	std::ifstream stream(path, std::ios::binary);
	if (!stream.is_open()) {
		throw std::runtime_error("Impossible d'ouvrir le fichier palette \"" + path.string() + "\"");
	}

	std::vector<std::string> palette;
	std::string line;
	while (std::getline(stream, line)) {
		if (!line.empty() && line.back() == '\r') line.pop_back();
		if (!line.empty()) palette.push_back(line);
	}

	if (palette.empty()) {
		throw std::runtime_error("Le fichier palette \"" + path.string() + "\" est vide");
	}
	return palette;
}

std::size_t paletteEntryWidth(const std::vector<std::string> &palette) {
	std::size_t width = 1;
	for (const auto &entry : palette) {
		// attention au octes 10*
		const auto codePoints = static_cast<std::size_t>(std::count_if(entry.begin(), entry.end(),
			[](unsigned char c) { return (c & 0xC0) != 0x80; }));
		width = std::max(width, codePoints);
	}
	return width;
}

std::string transformToASCII(const std::vector<Pixel> &data, const std::vector<std::string> &palette, Pixel valeurMax, std::size_t columns) {
	if (palette.empty() || valeurMax == 0) return {};

	std::stringstream ss;
	for (std::size_t n = 0; n < data.size(); ++n) {
		if (columns > 0 && n > 0 && n % columns == 0) ss << '\n';
		const Pixel p = data[n];
		double whiteValue = static_cast<double>(p)/static_cast<double>(valeurMax);
		double iDouble = whiteValue*static_cast<double>(palette.size());
		size_t i = std::clamp(static_cast<size_t>(iDouble),static_cast<size_t>(0),palette.size()-1);
		ss << palette[i];
	}

	return ss.str();
}

bool saveToFile(const std::filesystem::path& file, const std::string &data) {
	std::ofstream stream(file, std::ios::binary);
	if (!stream.is_open()) {
		std::cerr << "Impossible d'ouvrir le fichier de sortie \"" << file.string() << "\"\n";
		return false;
	}

	stream << data;
	stream.close();

	if (stream.fail()) {
		std::cerr << "Erreur lors de l'écriture du fichier \"" << file.string() << "\"\n";
		return false;
	}
	return true;
}