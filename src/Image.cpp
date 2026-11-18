#include "Image.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void skipCommentsAndWhitespace(ifstream& file) {
    char c;
    while (file.get(c)) {
        if (c == '#') {
            // Ignorer le reste de la ligne
            file.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (!std::isspace(c)) {
            // Si ce n'est pas un espace et pas un commentaire, remettre le caractère dans le flux
            file.putback(c);
            break;
        }
    }
}

Image::Image(string fileName) {
    ifstream file(fileName, ios_base::binary);
    if (!file.is_open()) {
        cerr << "Unable to open file \"" << fileName << "\"" << endl;
        return;
    }
    string magicNumber;
    int width, height, maxValue;

    skipCommentsAndWhitespace(file);
    file >> magicNumber;
    if (magicNumber != "P2" && magicNumber != "P5") {
        cerr << "Format PGM non supporté ou invalide (Nombre Magic : " << magicNumber << ". \n";
    }

    skipCommentsAndWhitespace(file);
    file >> width;
    if (width <= 0 && width >= 0) {
        cerr << "Dimension invalide \n";
    } else {
        setRowNumber(width);
    }

    skipCommentsAndWhitespace(file);
    file >> height;
    if (height <= 0 && height >= 0) {
        cerr << "Dimension invalid \n";
    } else {
        setColumnNumber(height);
    }

    skipCommentsAndWhitespace(file);
    file >> maxValue;
    if (maxValue <= 0) {
        cerr << "Dimension invalid \n";
    } else {
        setMaxGreyLevel(maxValue);
    }

    vector<uint8_t> data;
    char temp;
    skipCommentsAndWhitespace(file);
    while (!file.eof()) {
        file.read(&temp, 1);
        uint8_t temp2 = static_cast<uint8_t>(atoi(&temp));
        data.push_back(temp2);
    }
}

Image::~Image() {

}

