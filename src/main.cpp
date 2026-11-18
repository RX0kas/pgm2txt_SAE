#include <iostream>

#include "decoder.h"
#include "Image.h"
using namespace std;

int main() {
	string fileName;
	cout << "Nom du fichier à ouvrir : ";
	cin >> fileName;
	Image images(fileName);
	std::string p = "Wwlmi, ";
	std::cout << transformToASCII(images.getPixelData(),p, 255);
	return 0;
}
