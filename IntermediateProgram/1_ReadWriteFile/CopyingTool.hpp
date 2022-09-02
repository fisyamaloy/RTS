#pragma once

#include <iostream>
#include <string>
#include "FileReader.hpp"
#include "FileWriter.hpp"
#include "SafeQueue.hpp"

class CopyingTool final
{
public:
	CopyingTool() = delete;
	CopyingTool(const std::string& sourceFileName, const std::string& targetFileName);
	CopyingTool(const CopyingTool&) = delete;
	CopyingTool(CopyingTool&&) = delete;
	CopyingTool& operator=(const CopyingTool&) = delete;
	CopyingTool& operator=(CopyingTool&&) = delete;

	~CopyingTool() = default;

	void run();

private:
	void reading();
	void copying();

private:
	std::string _sourceFileName;
	std::string _targetFileName;
	SafeQueue<std::vector<char>> _incomingData;
	std::atomic<bool> _isFileRead = false;
};
