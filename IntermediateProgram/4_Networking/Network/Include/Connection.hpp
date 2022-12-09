#pragma once

#ifdef _WIN32
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif
#endif

#define _WIN32_WINNT 0x0601

#include <boost/asio.hpp>
#include <chrono>
#include <functional>
#include <iostream>

#include "CompressionHandler.hpp"
#include "EncryptionHandler.hpp"
#include "Handler.hpp"
#include "Message.hpp"
#include "SafeQueue.hpp"
#include "SerializationHandler.hpp"
#include "YasSerializer.hpp"

class Connection : public std::enable_shared_from_this<Connection>
{
public:
    /** @enum OwnerType
     *  @brief A connection is "owned" by either a server or a client. /
        And its behaviour is slightly different bewteen the two.
     */
    enum class OwnerType
    {
        SERVER,  /// owner is server
        CLIENT   /// owner is client
    };

private:
    /// Connection "owner"
    OwnerType mOwner = OwnerType::SERVER;
    std::uint64_t mConnectionID = uint64_t();

    boost::asio::ip::tcp::socket mSocket;
    boost::asio::io_context& mContextLink;

    /// Strand to protect read operations
    boost::asio::io_context::strand _readStrand;
    /// Strand to protect write operations
    boost::asio::io_context::strand _writeStrand;

    /// References to the incoming queue of the parent object
    SafeQueue<Message>& mIncomingMessagesQueueLink;
    /// Queue all messages to be sent to the remote side of this connection
    SafeQueue<Message> mOutcomingMessagesQueue;

    /// Buffer to store the part of incoming message while it is read
    Message mMessageBuffer;

    void writeHeader()
    {
        yas::shared_buffer bodyBuffer;

        SerializationHandler handler;
        handler.setNext(new CompressionHandler())->setNext(new EncryptionHandler());
        MessageProcessingState result =
            handler.handleOutcomingMessage(mOutcomingMessagesQueue.front(), bodyBuffer);

        Message::MessageHeader outcomingMessageHeader = mOutcomingMessagesQueue.front().mHeader;
        outcomingMessageHeader.mBodySize              = static_cast<uint64_t>(bodyBuffer.size);

        if (result == MessageProcessingState::SUCCESS)
        {
            const auto writeHeaderHandler = [this, bodyBuffer](std::error_code error) {
                if (!error)
                {
                    if (mOutcomingMessagesQueue.front().mBody.has_value())
                    {
                        writeBody(bodyBuffer);
                    }
                    else
                    {
                        mOutcomingMessagesQueue.pop_front();

                        if (!mOutcomingMessagesQueue.empty()) 
                            writeHeader();
                    }
                }
                else
                {
                    std::cout << "[" << mConnectionID << "] Write Header Fail.\n";
                    mSocket.close();
                }
            };

            boost::asio::async_write(mSocket,
                boost::asio::buffer(&outcomingMessageHeader, sizeof(Message::MessageHeader)),
                boost::asio::bind_executor(
                    _writeStrand, std::bind(writeHeaderHandler, std::placeholders::_1)));
        }
    }

    void writeBody(yas::shared_buffer buffer)
    {
        const auto writeBodyHandler = [this](std::error_code error) {
            if (!error)
            {
                mOutcomingMessagesQueue.pop_front();

                if (!mOutcomingMessagesQueue.empty()) 
                    writeHeader();
            }
            else
            {
                std::cout << "[" << mConnectionID << "] Write Body Fail.\n";
                mSocket.close();
            }
        };

        boost::asio::async_write(mSocket, boost::asio::buffer(buffer.data.get(), buffer.size),
            boost::asio::bind_executor(_writeStrand, std::bind(writeBodyHandler, std::placeholders::_1)));
    }

    void readHeader()
    {
        const auto readHeaderHandler = [this](std::error_code error) {
            if (!error)
            {
                if (mMessageBuffer.mHeader.mBodySize > 0)
                    readBody(mMessageBuffer.mHeader.mBodySize);
                else
                    addToIncomingMessageQueue();
            }
            else
            {
                std::cout << "[" << mConnectionID << "] Read Header Fail.\n";
                mSocket.close();
            }
        };

        boost::asio::async_read(mSocket,
            boost::asio::buffer(&mMessageBuffer.mHeader, sizeof(Message::MessageHeader)),
            boost::asio::bind_executor(_readStrand, std::bind(readHeaderHandler, std::placeholders::_1)));
    }

    void readBody(size_t bodySize)
    {
        yas::shared_buffer buffer;
        buffer.resize(bodySize);

        const auto readBodyHandler = [this, buffer](std::error_code error) {
            if (!error)
            {
                EncryptionHandler handler;
                handler.setNext(new CompressionHandler())->setNext(new SerializationHandler());
                MessageProcessingState result =
                    handler.handleIncomingMessageBody(buffer, mMessageBuffer);

                if (result == MessageProcessingState::SUCCESS) 
                    addToIncomingMessageQueue();
            }
            else
            {
                std::cout << "[" << mConnectionID << "] Read Body Fail.\n";
                mSocket.close();
            }
        };

        boost::asio::async_read(mSocket, boost::asio::buffer(buffer.data.get(), buffer.size),
                boost::asio::bind_executor(_readStrand, std::bind(readBodyHandler, std::placeholders::_1)));
    }

    void addToIncomingMessageQueue()
    {
        if (mOwner == OwnerType::SERVER)
        {
            mMessageBuffer.mRemote = this->shared_from_this();
            mIncomingMessagesQueueLink.push_back(mMessageBuffer);
        }
        else
        {
            mIncomingMessagesQueueLink.push_back(mMessageBuffer);
        }

        readHeader();
    }

public:
    Connection(const OwnerType& owner, boost::asio::io_context& contextLink,
        boost::asio::ip::tcp::socket socket, SafeQueue<Message>& incomingMessagesQueueLink)
        : mOwner(owner),
          mSocket(std::move(socket)),
          mContextLink(contextLink),
          _readStrand(contextLink),
          _writeStrand(contextLink),
          mIncomingMessagesQueueLink(incomingMessagesQueueLink)
    {
    }

    /**
     * @brief Method getting connection id.
     * @details This id is used system wide - it is how clients will understand other clients /
     * whole system.
     * @return mId - connection id.
     */
    std::uint64_t getID() const
    {
        return mConnectionID;
    }

    void connectToClient(const uint64_t uid = uint64_t())
    {
        if (mOwner == OwnerType::SERVER)
        {
            if (mSocket.is_open())
            {
                mConnectionID = uid;
                readHeader();
            }
        }
    }

#pragma warning(disable : 4100)
    void connectToServer(const boost::asio::ip::tcp::resolver::results_type& endpoint)
    {
        if (mOwner == OwnerType::CLIENT)
        {
            boost::asio::async_connect(mSocket, endpoint,
                [this](std::error_code ec, boost::asio::ip::tcp::endpoint endpoint) {
                    if (!ec)
                    {
                        readHeader();
                    }
                });
        }
    }

    void disconnect()
    {
        if (isConnected())
            boost::asio::post(mContextLink, [this]() { mSocket.close(); });
    }

    bool isConnected() const
    {
        return mSocket.is_open();
    }

    void send(const Message& message)
    {
        boost::asio::post(_writeStrand, [this, message]() {
            bool isMessageExist = !mOutcomingMessagesQueue.empty();
            mOutcomingMessagesQueue.push_back(message);

            if (!isMessageExist)
                writeHeader();
        });
    }
};
