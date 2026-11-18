#ifndef ASCIIART_DECODER_H
#define ASCIIART_DECODER_H
#include <filesystem>
#include <vector>
#include "Image.h"

std::string transformToASCII(const std::vector<Pixel>& data,const std::vector<std::string>& palette, Pixel valeurMax);
std::string transformToASCII(const std::vector<Pixel>& data, std::filesystem::path path, Pixel valeurMax);
bool saveToFile(const std::filesystem::path& file, const std::string& data);

#endif //ASCIIART_DECODER_H
