#ifndef ASCIIART_IMAGE_H
#define ASCIIART_IMAGE_H
#include <vector>

#define PRECISION unsigned long

class Image {
public:
	Image();
	~Image();
	[[nodiscard]] PRECISION getRowNumber() const { return m_rowColumns.first; }
	[[nodiscard]] PRECISION getColumnNumber() const { return m_rowColumns.second; }
	[[nodiscard]] PRECISION getMaxGrayLevel() const { return m_maxGrayLevel; }
	[[nodiscard]] std::vector<PRECISION> getPixelData() const { return m_pixelData; }

private:
	std::vector<PRECISION> m_pixelData;
	std::pair<PRECISION, PRECISION> m_rowColumns;
	PRECISION m_maxGrayLevel;

	void setColumnNumber(const PRECISION n) { m_rowColumns.second = n; }
	void setRowNumber(const PRECISION n) { m_rowColumns.first = n; }

	void setMaxGreyLevel(PRECISION n) {
		m_maxGrayLevel = n;
	}
};


#endif //ASCIIART_IMAGE_H
