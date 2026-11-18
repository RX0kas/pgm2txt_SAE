#ifndef ASCIIART_DECODER_H
#define ASCIIART_DECODER_H
#include <filesystem>
#include <vector>

std::string transformToASCII(const std::vector<unsigned long>& data,const std::string& palette, unsigned long valeurMax);


#endif //ASCIIART_DECODER_H
