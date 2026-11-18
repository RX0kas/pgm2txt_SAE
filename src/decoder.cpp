#include "decoder.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>

std::string transformToASCII(const std::vector<unsigned long> &data, const std::string &palette, unsigned long valeurMax) {
	std::stringstream ss;
	for (const auto p : data) {
		double whiteValue = static_cast<double>(p)/static_cast<double>(valeurMax);
		double iDouble = whiteValue*static_cast<double>(palette.size());
		size_t i = std::clamp(static_cast<size_t>(iDouble),static_cast<size_t>(0),palette.size()-1);
		ss << palette[i];
	}

	return ss.str();
}
