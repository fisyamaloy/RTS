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

	~FileReader()
	{
		if (_sourceFile)
			_sourceFile.close();
	}

	void open(const std::string& path)
	{
		_sourceFile.open(path, std::ios_base::binary);
		if (!_sourceFile)
			throw std::exception("Source file dosn't exist");
	}

	void close() { _sourceFile.close(); }

	bool isOpened() const { return _sourceFile.is_open(); }

	bool isEndOfFile() const { return _sourceFile.eof(); }

	std::vector<char> readNextBytesChunk()
	{
		constexpr size_t BUFFER_SIZE = 4096;

		std::vector<char> buffer(BUFFER_SIZE, '\0');
		_sourceFile.read(reinterpret_cast<char*>(&buffer[0]), BUFFER_SIZE);

		const size_t actualRead = _sourceFile.gcount();
		buffer.resize(actualRead);

		return buffer;
	}

private:
	std::ifstream _sourceFile;
};
