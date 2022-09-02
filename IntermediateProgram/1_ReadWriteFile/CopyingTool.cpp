#include "CopyingTool.hpp"
#include <fstream>
#include <thread>

CopyingTool::CopyingTool(const std::string& sourceFileName, const std::string& targetFileName) :
	_sourceFileName(sourceFileName), _targetFileName(targetFileName)
{
	
}

void CopyingTool::run()
{
	std::thread readingThread(&CopyingTool::reading, this);
	std::thread copyingThread(&CopyingTool::copying, this);

	readingThread.join();
	copyingThread.join();
}

void CopyingTool::reading()
{
	FileReader _fileReader(_sourceFileName);

	while (!_fileReader.isEndOfFile())
	{
		_incomingData.push(std::move(_fileReader.readNextBytesChunk()));
	}
	_isFileRead = true;
}

void CopyingTool::copying()
{
	FileWriter _fileWriter(_targetFileName);

	while (!_isFileRead)
	{
		_incomingData.wait(_isFileRead);

		while (!_incomingData.empty())
		{
			_fileWriter.writeBytesChunk(_incomingData.pop());
		}
	}
}
