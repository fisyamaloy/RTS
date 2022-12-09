#pragma once
#include <exception>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>

class FileReader final
{
public:
    FileReader() = default;
    FileReader(const std::string& path) : 
        _filePath{std::make_unique<std::filesystem::path>(path)}
    { open(path); }
    FileReader(const FileReader&)            = delete;
    FileReader(FileReader&&)                 = delete;
    FileReader& operator=(const FileReader&) = delete;
    FileReader& operator=(FileReader&&)      = delete;

    ~FileReader() noexcept;

    void              open(const std::string& path);
    std::vector<char> readNextBytesChunkVec(const size_t bufferSize);
    char*             readNextBytesChunk(const size_t bufferSize);

    void close() { _sourceFile.close(); }
    bool isOpened() const{ return _sourceFile.is_open(); }
    bool isEndOfFile() const { return _sourceFile.eof(); }
    std::size_t getFileSize() const;
    std::string getFileName() const;

private:
    std::ifstream _sourceFile;
    std::unique_ptr<std::filesystem::path> _filePath;
};
