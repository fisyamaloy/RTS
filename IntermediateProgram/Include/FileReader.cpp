#include <FileReader.hpp>

namespace
{
    constexpr size_t BUFFER_SIZE = 20480;
}

FileReader::~FileReader() noexcept
{
    if (_sourceFile) 
        _sourceFile.close();
}

void FileReader::open(const std::string& path)
{
    _sourceFile.open(path, std::ios_base::binary);
    if (!_sourceFile) 
        throw std::runtime_error("Source file dosn't exist");
}

std::vector<char> FileReader::readNextBytesChunk()
{
    std::vector<char> buffer(BUFFER_SIZE, '\0');
    _sourceFile.read(buffer.data(), BUFFER_SIZE);

    const size_t actualRead = _sourceFile.gcount();
    buffer.resize(actualRead);

    return buffer;
}
