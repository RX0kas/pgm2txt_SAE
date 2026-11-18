#ifndef ASCIIART_DECODER_H
#define ASCIIART_DECODER_H
#include <filesystem>
#include <vector>

std::string transformToASCII(const std::vector<uint8_t>& data,const std::string& palette, unsigned long valeurMax);
std::string transformToASCII(const std::vector<unsigned long>& data, std::filesystem::path path, unsigned long valeurMax);
bool saveToFile(const std::filesystem::path& file, const std::string& data);

#endif //ASCIIART_DECODER_H
