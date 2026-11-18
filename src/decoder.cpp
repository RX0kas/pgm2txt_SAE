#include "decoder.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <format>

std::string transformToASCII(const std::vector<PRECISION> &data, std::filesystem::path path, PRECISION valeurMax) {
	std::ifstream stream(path);
	if (!stream.is_open()) {
		std::cout << std::format("The file {} can't be open",path.string());
		exit(1);
	}

	std::string palette;
	while (!stream.eof()) {
		std::string temp;
		getline(stream, temp);
		std::string chars;
		for (auto c : temp) {
			if (c!='\r') {
				chars += c;
			}
		}
		palette+=chars;
	}

	return transformToASCII(data,palette, valeurMax);
}

std::string transformToASCII(const std::vector<PRECISION> &data, const std::string &palette, PRECISION valeurMax) {
	if (palette.empty() || valeurMax <= 0) return {};

	std::stringstream ss;
	for (const auto p : data) {
		double whiteValue = static_cast<double>(p)/static_cast<double>(valeurMax);
		double iDouble = whiteValue*static_cast<double>(palette.size());
		size_t i = std::clamp(static_cast<size_t>(iDouble),static_cast<size_t>(0),palette.size()-1);
		char c = palette[i];
		ss << c;
	}

	return ss.str();
}

bool saveToFile(const std::filesystem::path& file, const std::string &data) {
	std::ofstream stream(file);
	if (!stream.is_open()) {
		std::cout << std::format("The file {} can't be open",file.string());
		return false;
	}

	stream << data;
	stream.close();

	return !stream.fail();
}