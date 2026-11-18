#include "resize.h"

#include <algorithm>

std::vector<Pixel> resize(const std::pair<std::size_t, std::size_t> &oldSize, const std::pair<std::size_t, std::size_t> &newSize, const std::vector<Pixel> &data) {
	const auto [oldRows, oldCols] = oldSize;
	const auto [newRows, newCols] = newSize;
	std::vector<Pixel> result(newRows * newCols);

	for (std::size_t r = 0; r < newRows; ++r) {
		std::size_t r0 = r * oldRows / newRows;
		std::size_t r1 = std::max(r0 + 1, (r + 1) * oldRows / newRows);
		for (std::size_t c = 0; c < newCols; ++c) {
			std::size_t c0 = c * oldCols / newCols;
			std::size_t c1 = std::max(c0 + 1, (c + 1) * oldCols / newCols);

			unsigned long sum = 0;
			for (std::size_t y = r0; y < r1; ++y)
				for (std::size_t x = c0; x < c1; ++x)
					sum += data[y * oldCols + x];

			result[r * newCols + c] = sum / ((r1 - r0) * (c1 - c0));
		}
	}
	return result;
}
