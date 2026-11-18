#ifndef ASCIIART_DECODER_H
#define ASCIIART_DECODER_H
#include <filesystem>
#include <vector>

ImageData decode(std::filesystem::path file);
ImageData decodeFromSource(std::string data);


#endif //ASCIIART_DECODER_H
