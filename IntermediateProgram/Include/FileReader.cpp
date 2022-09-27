#include <FileReader.hpp>

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

std::vector<char> FileReader::readNextBytesChunkVec(const size_t bufferSize)
{
    std::vector<char> buffer(bufferSize, '\0');
    _sourceFile.read(buffer.data(), bufferSize);
    const size_t actualRead = _sourceFile.gcount();
    buffer.resize(actualRead);
    return buffer;
}

char* FileReader::readNextBytesChunk(const size_t bufferSize)
{
    const auto bufferVec = readNextBytesChunkVec(bufferSize);
    auto pBuffer = new char[bufferVec.size() + 1];
    std::copy(bufferVec.begin(), bufferVec.end(), pBuffer);
    pBuffer[bufferVec.size()] = '\0';
    return pBuffer;
}