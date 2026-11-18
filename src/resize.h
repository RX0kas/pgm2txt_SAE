#ifndef ASCIIART_RESIZE_H
#define ASCIIART_RESIZE_H
#include <vector>
#include "Image.h"

std::vector<Pixel> resize(const std::pair<std::size_t, std::size_t> &oldSize, const std::pair<std::size_t, std::size_t> &newSize, const std::vector<Pixel>& data);

#endif //ASCIIART_RESIZE_H
