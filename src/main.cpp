#include <cmath>
#include <iostream>
#include <sstream>

#include "decoder.h"
using namespace std;


#include "Image.h"

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#endif


int main() {
#ifdef PLATFORM_WINDOWS
	SetConsoleOutputCP(65001);
#endif
	std::locale::global(std::locale("en_US.UTF-8"));
	std::vector<unsigned long> pixelData = {
		0, 10, 20,30,40, 50,60, 70, 80,90, 100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,255
	};
	std::string defaultPalette = "Wwli:,. ";
	unsigned long valeurMax = 255;

	std::cout << transformToASCII(pixelData, defaultPalette, valeurMax);

	return 0;
}
