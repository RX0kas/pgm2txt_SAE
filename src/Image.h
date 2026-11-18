#ifndef ASCIIART_IMAGE_H
#define ASCIIART_IMAGE_H
#include <vector>

class Image {
public:
	Image(std::string fileName);

	~Image();
	[[nodiscard]] unsigned long getRowNumber() const { return m_rowColumns.first; }
	[[nodiscard]] unsigned long getColumnNumber() const { return m_rowColumns.second; }
	[[nodiscard]] unsigned long getMaxGrayLevel() const { return m_maxGrayLevel; }
	[[nodiscard]] std::vector<unsigned long> getPixelData() const { return m_pixelData; }

private:
	std::vector<unsigned long> m_pixelData;
	std::pair<unsigned long, unsigned long> m_rowColumns;
	unsigned long m_maxGrayLevel;

	void setColumnNumber(const unsigned long n) { m_rowColumns.second = n; }
	void setRowNumber(const unsigned long n) { m_rowColumns.first = n; }

	void setMaxGreyLevel(unsigned long n) {
		m_maxGrayLevel = n;
	}
};


#endif //ASCIIART_IMAGE_H
