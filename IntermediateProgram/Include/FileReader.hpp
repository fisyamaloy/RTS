#pragma once
#include <fstream>
#include <exception>
#include <vector>

class FileReader final
{
public:
	FileReader() = default;
	FileReader(const std::string& path) { open(path);}
	FileReader(const FileReader&) = delete;
	FileReader(FileReader&&) = delete;
	FileReader& operator=(const FileReader&) = delete;
	FileReader& operator=(FileReader&&) = delete;

	~FileReader() noexcept;

	void open(const std::string& path);
	std::vector<char> readNextBytesChunk();

	void close() { _sourceFile.close(); }
	bool isOpened() const { return _sourceFile.is_open(); }
	bool isEndOfFile() const { return _sourceFile.eof(); }

private:
	std::ifstream _sourceFile;
};
