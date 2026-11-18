#ifndef ASCIIART_DECODER_H
#define ASCIIART_DECODER_H
#include <filesystem>
#include <string>
#include <vector>
#include "Image.h"

std::vector<std::string> loadPalette(const std::filesystem::path &path);
std::size_t paletteEntryWidth(const std::vector<std::string> &palette);
std::string transformToASCII(const std::vector<Pixel>& data,const std::vector<std::string>& palette, Pixel valeurMax, std::size_t columns = 0);
bool saveToFile(const std::filesystem::path& file, const std::string& data);

#endif //ASCIIART_DECODER_H
