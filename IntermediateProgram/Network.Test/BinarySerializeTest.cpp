#include <array>
#include <gtest/gtest.h>
#include <list>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "Connection.hpp"
#include "Message.hpp"
#include "YasSerializer.hpp"
#include <Primitives.hpp>
#include <FileReader.hpp>

TEST(Test, YasSerializer)
{
    const int serializedValue = 10;
    yas::shared_buffer buffer;
    SerializedState state = YasSerializer::serialize(buffer, serializedValue);
    EXPECT_TRUE(state == SerializedState::SUCCESS);

    int deserializedValue;
    state = YasSerializer::deserialize(buffer, deserializedValue);
    EXPECT_TRUE(state == SerializedState::SUCCESS);

    EXPECT_TRUE(serializedValue == deserializedValue);
}

TEST(FileInfo, YasSerializer)
{
    FileReader fileReader("source.txt");

    const auto FILE_NAME = fileReader.getFileName();
    const auto FILE_SIZE = fileReader.getFileSize();

    std::wstring FILE_TEXT(FILE_SIZE + 1, '\0');
    auto*        bytesChunck = fileReader.readNextBytesChunk(FILE_SIZE);
    std::copy(bytesChunck, bytesChunck + FILE_SIZE, FILE_TEXT.begin());

    FileInfo serializedValue(FILE_SIZE, FILE_NAME, FILE_TEXT);

    yas::shared_buffer buffer;
    SerializedState    state = YasSerializer::serialize(buffer, serializedValue);
    EXPECT_TRUE(state == SerializedState::SUCCESS);

    FileInfo deserializedValue;
    state = YasSerializer::deserialize(buffer, deserializedValue);
    EXPECT_TRUE(state == SerializedState::SUCCESS);

    EXPECT_TRUE(serializedValue == deserializedValue);
}
