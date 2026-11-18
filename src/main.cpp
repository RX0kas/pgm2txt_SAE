#include <iostream>
#include "Image.h"
using namespace std;

int main() {
	string fileName;
	cout << "Nom du fichier à ouvrir : ";
	cin >> fileName;
	Image images(fileName);
	return 0;
}
