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

const std::vector<std::string> defaultPalette = {"W", "w", "l", "m", "i", ",", " "};

void showHelp() {
	std::cout << "Usage :\n"
	<< "pgm2txt [options]\n\n"
	<< "Options :\n"
	<< "--input fichier   Spécifie le fichier image à convertir\n"
	<< "                  Si ce paramètre n'est pas spécifié, le fichier est demandé via la\n"
	<< "                  console.\n"
	<< "--output fichier  Spécifie le nom du fichier texte qui contiendra l'Ascii Art.\n"
   << "                  Si ce paramètre n'est pas spécifié, l'Ascii Art est sortie dans la\n"
	<< "                  console.\n"
	<< "--palette fichier Spécifie un fichier texte contenant la palette de couleur Ascii.\n"
	<< "                  Chaque ligne du fichier contient un charactère en UTF-8, du plus\n"
	<< "                  sombre au plus clair.\n"
	<< "                  Si ce paramètre n'est pas spécifié, la palette par défaut est\n"
	<< R"(                  "W", "w", "l", "i", ":", ",", ".", " ")" << '\n'
	<< "--help Affiche cette aide." << std::endl;
}

int main(int argc, char* argv[]) {
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
	std::string outputFileName;
	std::string paletteFilename;
	if (argc==1 || argc==2 && (argv[1]==static_cast<std::string>("--help") || argv[1]==static_cast<std::string>("-h"))) {
		showHelp();
		exit(0);
	}

	// Parcour argument
	for (int i = 0; i < argc; i++) {
		std::string arg = argv[i];
		if (arg=="--input") {
			fileName = argv[++i];
		} else if (arg=="--output") {
			outputFileName = argv[++i];
		} else if (arg=="--palette") {
			paletteFilename= argv[++i];
		} else if (arg=="--help" || arg=="-h") {
			showHelp();
			exit(0);
		}
	}

	if (!std::filesystem::exists({fileName})) {
		std::cerr << "Fichier a convertir est introuvable\n";
		exit(0);
	}
	if (!outputFileName.empty() && std::filesystem::exists({outputFileName})) {
		std::cout << "[WARN] Le fichier de sortie existe déja, il sera écrasé\n";
	}
	if (!paletteFilename.empty() && !std::filesystem::exists({paletteFilename})) {
		std::cerr << "Le fichier palette est introuvable\n";
		exit(0);
	}

	std::string result;

	Image image(fileName);
	if (paletteFilename.empty()) {
		try {
			result = transformToASCII(image.getPixelData(), defaultPalette, image.getMaxGrayLevel());
		} catch (const std::exception &e) {
			std::cerr << e.what() << '\n';
			return 1;
		}
	} else {
		try {
			result = transformToASCII(image.getPixelData(), paletteFilename, image.getMaxGrayLevel());
		} catch (const std::exception &e) {
			std::cerr << e.what() << '\n';
			return 1;
		}
	}

	if (outputFileName.empty()) {
		std::cout << result << '\n';
	} else {
		saveToFile(outputFileName,result);
	}

	return 0;
}
