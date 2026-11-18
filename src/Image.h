#ifndef ASCIIART_IMAGE_H
#define ASCIIART_IMAGE_H
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <utility>
#include <vector>

using Pixel = uint8_t;

class Image {
public:
	explicit Image(const std::filesystem::path &fileName);

	[[nodiscard]] std::size_t getRowNumber() const { return m_rowColumns.first; }
	[[nodiscard]] std::size_t getColumnNumber() const { return m_rowColumns.second; }
	[[nodiscard]] Pixel getMaxGrayLevel() const { return m_maxGrayLevel; }
	[[nodiscard]] std::vector<Pixel> getPixelData() const { return m_pixelData; }

private:
	std::vector<Pixel> m_pixelData;
	std::pair<std::size_t, std::size_t> m_rowColumns;
	Pixel m_maxGrayLevel;

	void setColumnNumber(const std::size_t n) { m_rowColumns.second = n; }
	void setRowNumber(const std::size_t n) { m_rowColumns.first = n; }

	void setMaxGreyLevel(Pixel n) {
		m_maxGrayLevel = n;
	}
};


#endif //ASCIIART_IMAGE_H
