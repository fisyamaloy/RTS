#pragma once
#include <fstream>
#include <exception>
#include <vector>
#include <iterator>

class FileWriter final
{
public:
	FileWriter() = default;
	FileWriter(const std::string& path) { open(path); }
	FileWriter(FileWriter&&) = delete;
	FileWriter& operator=(const FileWriter&) = delete;
	FileWriter& operator=(FileWriter&&) = delete;
	~FileWriter()
	{
		if (_targetFile)
			_targetFile.close();
	}

	void open(const std::string& path)
	{
		_targetFile.open(path, std::ios_base::binary);
		if (!_targetFile)
			throw std::runtime_error("Target file dosn't exist");
	}

	void close()
	{
		_targetFile.close();
	}

	bool isOpened() const
	{
		return _targetFile.is_open();
	}

	void writeBytesChunk(std::vector<char> incomingData)
	{
		_targetFile << incomingData.data();
	}

private:
	std::ofstream _targetFile;
};
