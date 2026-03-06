#include "readFile.hpp"

std::vector<char>	readFile(const std::string& filename) {
	std::ifstream		file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		file.open(std::string(app::buildToRoot) + filename, std::ios::ate | std::ios::binary);
		if (!file.is_open()) {
			throw std::runtime_error("failed to open file: " + std::string(filename));
		}
	}
	size_t				fileSize = (size_t) file.tellg();
	std::vector<char>	buffer(fileSize);
	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();

	return buffer;
}
