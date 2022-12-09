#pragma once

#include <any>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <memory>
#include <vector>

#include "Connection.hpp"

class Connection;

struct Message
{
    enum class MessageType : std::uint32_t
    {
        ServerAccept,
        ServerPing,
        MessageAll,
        ServerMessage,
        SendFileRequest,
        SendFileAnswer,
    };

    struct MessageHeader
    {
        MessageType mMessageType = MessageType();
        std::uint64_t mBodySize  = std::uint64_t();
        std::chrono::time_point<std::chrono::system_clock> mTimestamp =
            std::chrono::system_clock::now();
    };

    std::shared_ptr<Connection> mRemote = nullptr;

    MessageHeader mHeader;
    std::any mBody;

    friend bool operator<(const Message& lhs, const Message& rhs)
    {
        return lhs.mHeader.mTimestamp < rhs.mHeader.mTimestamp;
    }

    friend bool operator>(const Message& lhs, const Message& rhs)
    {
        return lhs.mHeader.mTimestamp > rhs.mHeader.mTimestamp;
    }
};

template <typename Archive>
void serialize(Archive& ar, Message::MessageHeader& o)
{
    ar& o.mMessageType& o.mBodySize& o.mTimestamp;
}
