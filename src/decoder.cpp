#include "decoder.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <format>

std::string transformToASCII(const std::vector<unsigned long> &data, std::filesystem::path path, unsigned long valeurMax) {
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

std::string transformToASCII(const std::vector<uint8_t> &data, const std::string &palette, unsigned long valeurMax) {
	std::stringstream ss;
	for (const auto p : data) {
		double whiteValue = static_cast<double>(p)/static_cast<double>(valeurMax);
		double iDouble = whiteValue*static_cast<double>(palette.size());
		size_t i = std::clamp(static_cast<size_t>(iDouble),static_cast<size_t>(0),palette.size()-1);
		ss << palette[i];
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