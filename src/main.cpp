#include <algorithm>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "decoder.h"
#include "Image.h"
#include "resize.h"

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#endif


int main() {
#ifdef PLATFORM_WINDOWS
	SetConsoleOutputCP(65001);
#else
	try {
		std::locale::global(std::locale("en_US.UTF-8"));
	} catch (const std::exception &e) {
		std::cerr << "Error: "<< e.what() << std::endl;
	}
#endif

	std::string fileName;
	std::cout << "Nom du fichier à ouvrir : ";
	std::cin >> fileName;

	try {
		Image image(fileName);
		const std::vector<std::string> palette = {"W", "w", "l", "m", "i", ",", " "};
		std::cout << transformToASCII(image.getPixelData(), palette, image.getMaxGrayLevel()) << '\n';
	} catch (const std::exception &e) {
		std::cerr << e.what() << '\n';
		return 1;
	}

	return 0;
}
