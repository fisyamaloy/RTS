#pragma once
#include <fstream>
#include <vector>

class FileWriter final
{
public:
	FileWriter() = default;
	FileWriter(const std::string& path) { open(path); }
	FileWriter(FileWriter&&) = delete;
	FileWriter& operator=(const FileWriter&) = delete;
	FileWriter& operator=(FileWriter&&) = delete;
	
	~FileWriter() noexcept;

	void writeBytesChunk(std::vector<char> incomingData) { _targetFile << incomingData.data(); }
	void open(const std::string& path);
	
	void close() { _targetFile.close(); }
	bool isOpened() const { return _targetFile.is_open(); }

private:
	std::ofstream _targetFile;
};
