#ifndef ASCIIART_DECODER_H
#define ASCIIART_DECODER_H
#include <filesystem>
#include <vector>
#include "Image.h"

std::string transformToASCII(const std::vector<uint8_t>& data,const std::string& palette, uint8_t valeurMax);
std::string transformToASCII(const std::vector<uint8_t>& data, std::filesystem::path path, uint8_t valeurMax);
bool saveToFile(const std::filesystem::path& file, const std::string& data);

#endif //ASCIIART_DECODER_H
