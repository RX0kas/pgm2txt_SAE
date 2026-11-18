#ifndef ASCIIART_RESIZE_H
#define ASCIIART_RESIZE_H
#include <vector>
#include "Image.h"

std::vector<PRECISION> resize(const std::pair<PRECISION, PRECISION> &oldSize, const std::pair<PRECISION, PRECISION> &newSize, const std::vector<PRECISION>& data);

#endif //ASCIIART_RESIZE_H
