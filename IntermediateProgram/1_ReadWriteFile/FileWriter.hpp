#pragma once
#include <fstream>
#include <exception>
#include <vector>

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
			throw std::exception("Target file dosn't exist");
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
		std::copy(incomingData.begin(), incomingData.end(), std::ostream_iterator<char>(_targetFile));
	}

private:
	std::ofstream _targetFile;
};
