#ifndef ASCIIART_IMAGE_H
#define ASCIIART_IMAGE_H
#include <cstdint>
#include <cstdint>
#include <filesystem>
#include <utility>
#include <vector>

using Pixel = uint8_t;

class Image {
public:
	explicit Image(const std::filesystem::path &fileName);

	~Image();
	[[nodiscard]] uint8_t getRowNumber() const { return m_rowColumns.first; }
	[[nodiscard]] uint8_t getColumnNumber() const { return m_rowColumns.second; }
	[[nodiscard]] uint8_t getMaxGrayLevel() const { return m_maxGrayLevel; }
	[[nodiscard]] std::vector<uint8_t> getPixelData() const { return m_pixelData; }

private:
	std::vector<uint8_t> m_pixelData;
	std::pair<uint8_t, uint8_t> m_rowColumns;
	uint8_t m_maxGrayLevel;

	void setColumnNumber(const uint8_t n) { m_rowColumns.second = n; }
	void setRowNumber(const uint8_t n) { m_rowColumns.first = n; }

	void setMaxGreyLevel(uint8_t n) {
		m_maxGrayLevel = n;
	}
};


#endif //ASCIIART_IMAGE_H
