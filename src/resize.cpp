#include "resize.h"

#include <algorithm>

std::vector<PRECISION> resize(const std::pair<PRECISION, PRECISION> &oldSize, const std::pair<PRECISION, PRECISION> &newSize, const std::vector<PRECISION> &data) {
	const auto [oldRows, oldCols] = oldSize;
	const auto [newRows, newCols] = newSize;
	std::vector<PRECISION> result(newRows * newCols);

	for (PRECISION r = 0; r < newRows; ++r) {
		PRECISION r0 = r * oldRows / newRows;
		PRECISION r1 = std::max(r0 + 1, (r + 1) * oldRows / newRows);
		for (PRECISION c = 0; c < newCols; ++c) {
			PRECISION c0 = c * oldCols / newCols;
			PRECISION c1 = std::max(c0 + 1, (c + 1) * oldCols / newCols);

			PRECISION sum = 0;
			for (PRECISION y = r0; y < r1; ++y)
				for (PRECISION x = c0; x < c1; ++x)
					sum += data[y * oldCols + x];

			result[r * newCols + c] = sum / ((r1 - r0) * (c1 - c0));
		}
	}
	return result;
}
