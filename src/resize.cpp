#include "resize.h"

#include <algorithm>

std::vector<uint8_t> resize(const std::pair<uint8_t, uint8_t> &oldSize, const std::pair<uint8_t, uint8_t> &newSize, const std::vector<uint8_t> &data) {
	const auto [oldRows, oldCols] = oldSize;
	const auto [newRows, newCols] = newSize;
	std::vector<uint8_t> result(newRows * newCols);

	for (uint8_t r = 0; r < newRows; ++r) {
		uint8_t r0 = r * oldRows / newRows;
		uint8_t r1 = std::max(r0 + 1, (r + 1) * oldRows / newRows);
		for (uint8_t c = 0; c < newCols; ++c) {
			uint8_t c0 = c * oldCols / newCols;
			uint8_t c1 = std::max(c0 + 1, (c + 1) * oldCols / newCols);

			uint8_t sum = 0;
			for (uint8_t y = r0; y < r1; ++y)
				for (uint8_t x = c0; x < c1; ++x)
					sum += data[y * oldCols + x];

			result[r * newCols + c] = sum / ((r1 - r0) * (c1 - c0));
		}
	}
	return result;
}
