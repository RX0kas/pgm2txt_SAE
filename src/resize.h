#ifndef ASCIIART_RESIZE_H
#define ASCIIART_RESIZE_H
#include <vector>
#include "Image.h"

std::vector<uint8_t> resize(const std::pair<uint8_t, uint8_t> &oldSize, const std::pair<uint8_t, uint8_t> &newSize, const std::vector<uint8_t>& data);

#endif //ASCIIART_RESIZE_H
