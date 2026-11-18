#include <algorithm>
#include <cctype>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "decoder.h"
#include "Image.h"
#include "resize.h"

#ifdef PLATFORM_WINDOWS
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#endif

const std::vector<std::string> defaultPalette = {"W", "w", "l", "i", ":", ",", ".", " "};

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
	<< "--width nombre    Spécifie la largeur max de l'Ascii Art.\n"
	<< "                  Si ce paramètre n'est pas spécifié, aucune limite n'est fixée.\n"
	<< "                  Voir Remarques.\n"
	<< "--height nombre   Spécifie la hauteur max de l'Ascii Art.\n"
	<< "                  Si ce paramètre n'est pas spécifié, aucune limite n'est fixée.\n"
	<< "                  Voir Remarques.\n"
	<< "--help            Affiche cette aide.\n\n"
	<< "Remarques :\n"
	<< "Quelles que soient les valeurs des options --width et --height, la taille de l'Ascii Art\n"
	<< "est bornée par la taille de l'image en entrée. La taille de l'ascii art conserve\n"
	<< "toujours le même ratio que l'image d'entrée, les valeurs des options --width et --height\n"
	<< "ne sont que des maximums." << std::endl;
}

// convertit une chaine en entier pos, renvoie 0 si invalide
std::size_t parseSize(const std::string &str) {
	if (str.empty() || !std::all_of(str.begin(), str.end(), [](unsigned char c) { return std::isdigit(c); })) {
		return 0;
	}
	try {
		return std::stoul(str);
	} catch (const std::exception &) {
		return 0;
	}
}

// calcule la taille finale
std::pair<std::size_t, std::size_t> computeSize(std::size_t rows, std::size_t cols, std::size_t maxWidth, std::size_t maxHeight) {
	double scale = 1.0;
	if (maxWidth > 0 && maxWidth < cols) {
		scale = std::min(scale, static_cast<double>(maxWidth) / static_cast<double>(cols));
	}
	if (maxHeight > 0 && maxHeight < rows) {
		scale = std::min(scale, static_cast<double>(maxHeight) / static_cast<double>(rows));
	}
	if (scale >= 1.0) return {rows, cols};

	const auto newRows = std::max<std::size_t>(1, static_cast<std::size_t>(static_cast<double>(rows) * scale));
	const auto newCols = std::max<std::size_t>(1, static_cast<std::size_t>(static_cast<double>(cols) * scale));
	return {std::min(newRows, rows), std::min(newCols, cols)};
}

int main(int argc, char* argv[]) {
#ifdef PLATFORM_WINDOWS
	SetConsoleOutputCP(65001);
#endif
	std::string fileName;
	std::string outputFileName;
	std::string paletteFilename;
	std::size_t maxWidth = 0;  // 0 = pas de limite
	std::size_t maxHeight = 0; // 0 = pas de limite

	// Parcours des arguments (argv[0] est le nom du programme)
	for (int i = 1; i < argc; i++) {
		const std::string arg = argv[i];
		if (arg == "--help" || arg == "-h") {
			showHelp();
			return 0;
		}

		if (arg != "--input" && arg != "--output" && arg != "--palette" && arg != "--width" && arg != "--height") {
			std::cerr << "Option inconnue : " << arg << " (voir --help)\n";
			return 1;
		}
		if (i + 1 >= argc) {
			std::cerr << "L'option " << arg << " attend une valeur\n";
			return 1;
		}
		const std::string value = argv[++i];

		if (arg == "--input") {
			fileName = value;
		} else if (arg == "--output") {
			outputFileName = value;
		} else if (arg == "--palette") {
			paletteFilename = value;
		} else {
			const std::size_t size = parseSize(value);
			if (size == 0) {
				std::cerr << "Valeur invalide pour " << arg << " : " << value
					<< " (un entier strictement positif est attendu)\n";
				return 1;
			}
			(arg == "--width" ? maxWidth : maxHeight) = size;
		}
	}

	// pas de --input : on demande le fichier avec la console
	if (fileName.empty()) {
		std::cout << "Fichier à convertir : " << std::flush;
		if (!std::getline(std::cin, fileName)) fileName.clear();
		if (!fileName.empty() && fileName.back() == '\r') fileName.pop_back();
	}

	if (fileName.empty() || !std::filesystem::is_regular_file(fileName)) {
		std::cerr << "Le fichier à convertir est introuvable : \"" << fileName << "\"\n";
		return 1;
	}
	if (!paletteFilename.empty() && !std::filesystem::is_regular_file(paletteFilename)) {
		std::cerr << "Le fichier palette est introuvable : \"" << paletteFilename << "\"\n";
		return 1;
	}
	if (!outputFileName.empty() && std::filesystem::exists(outputFileName)) {
		std::cerr << "[WARN] Le fichier de sortie existe déjà, il sera écrasé\n";
	}

	std::string result;
	try {
		const std::vector<std::string> palette = paletteFilename.empty() ? defaultPalette : loadPalette(paletteFilename);

		const Image image(fileName);

		const std::size_t entryWidth = paletteEntryWidth(palette);
		const std::size_t maxPixelColumns = maxWidth == 0 ? 0 : std::max<std::size_t>(1, maxWidth / entryWidth);

		const std::pair<std::size_t, std::size_t> oldSize = {image.getRowNumber(), image.getColumnNumber()};
		const auto newSize = computeSize(oldSize.first, oldSize.second, maxPixelColumns, maxHeight);
		const std::vector<Pixel> pixels = newSize == oldSize ? image.getPixelData() : resize(oldSize, newSize, image.getPixelData());

		result = transformToASCII(pixels, palette, image.getMaxGrayLevel(), newSize.second);
	} catch (const std::exception &e) {
		std::cerr << "Erreur : " << e.what() << '\n';
		return 1;
	}

	if (outputFileName.empty()) {
		std::cout << result << '\n';
	} else if (!saveToFile(outputFileName, result)) {
		return 1;
	}

	return 0;
}
