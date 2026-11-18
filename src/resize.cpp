#include "resize.h"

#include <algorithm>
#include <utility>

std::pair<std::size_t, std::size_t> sourceRange(std::size_t index, std::size_t oldSize, std::size_t newSize) {
	const std::size_t begin = index * oldSize / newSize;
	const std::size_t end = std::max(begin + 1, (index + 1) * oldSize / newSize);
	return {begin, end};
}

std::vector<Pixel> resize(const std::pair<std::size_t, std::size_t> &oldSize, const std::pair<std::size_t, std::size_t> &newSize, const std::vector<Pixel> &data) {
	const auto [oldRows, oldCols] = oldSize;
	const auto [newRows, newCols] = newSize;
	std::vector<Pixel> result(newRows * newCols);

	for (std::size_t row = 0; row < newRows; ++row) {
		const auto [rowBegin, rowEnd] = sourceRange(row, oldRows, newRows);

		for (std::size_t col = 0; col < newCols; ++col) {
			const auto [colBegin, colEnd] = sourceRange(col, oldCols, newCols);

			// somme des pixels du bloc de depart
			unsigned long sum = 0;
			for (std::size_t y = rowBegin; y < rowEnd; ++y) {
				for (std::size_t x = colBegin; x < colEnd; ++x) {
					sum += data[y * oldCols + x];
				}
			}

			const std::size_t blockSize = (rowEnd - rowBegin) * (colEnd - colBegin);
			result[row * newCols + col] = static_cast<Pixel>(sum / blockSize);
		}
	}

	return result;
}
