#include "FileWriter.hpp"
#include <exception>

FileWriter::~FileWriter() noexcept
{
    if (_targetFile) 
        _targetFile.close();
}

void FileWriter::open(const std::string& path)
{
    _targetFile.open(path, std::ios_base::binary);
    if (!_targetFile) 
        throw std::runtime_error("Target file dosn't exist");
}
