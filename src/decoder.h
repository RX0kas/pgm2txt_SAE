#ifndef ASCIIART_DECODER_H
#define ASCIIART_DECODER_H
#include <filesystem>
#include <vector>
#include "Image.h"

std::string transformToASCII(const std::vector<PRECISION>& data,const std::string& palette, PRECISION valeurMax);
std::string transformToASCII(const std::vector<PRECISION>& data, std::filesystem::path path, PRECISION valeurMax);
bool saveToFile(const std::filesystem::path& file, const std::string& data);

#endif //ASCIIART_DECODER_H
