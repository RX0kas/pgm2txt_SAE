#include <sstream>

#include "decoder.h"
#include "resize.h"
#include <iostream>

using namespace std;


#include "Image.h"

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#endif


int main() {
#ifdef PLATFORM_WINDOWS
	SetConsoleOutputCP(65001);
#else
	std::locale::global(std::locale("en_US.UTF-8"));
#endif
	std::vector<PRECISION> pixelData = {
		0, 10, 20, 30,
		80, 90,100, 110,
		150,160,170,180,
		200, 150, 10, 5
	};
	std::string defaultPalette = "Wwli:,. ";
	PRECISION valeurMax = 255;
	std::vector<PRECISION> newPixelData = resize({4,4}, {2,2},pixelData);

	std::cout << transformToASCII(pixelData,defaultPalette,valeurMax) << '\n';
	std::cout << transformToASCII(newPixelData,defaultPalette,valeurMax);



	return 0;
}
