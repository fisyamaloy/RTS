#pragma once
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>

using boost::interprocess::open_or_create;
using boost::interprocess::read_only;
using boost::interprocess::read_write;

class ShMemTerminationHandler final
{
public:
    enum State
    {
        ERROR = -1,
        SUCCESS = 0,
    };

    ShMemTerminationHandler()
    {
        boost::interprocess::shared_memory_object temp{open_or_create, "StateShMem", read_write};
        smo.swap(temp);
    }

    ShMemTerminationHandler(const ShMemTerminationHandler&) = delete;
    ShMemTerminationHandler(ShMemTerminationHandler&& th) noexcept 
    {
        smo = std::move(th.smo);
    }
    ~ShMemTerminationHandler()
    {
        boost::interprocess::shared_memory_object::remove("StateShMem");
    }
    ShMemTerminationHandler* operator=(ShMemTerminationHandler&) = delete;
    ShMemTerminationHandler* operator=(ShMemTerminationHandler&& th) noexcept
    {
        smo = std::move(th.smo);
        return this;
    }

    void sendStateToSecondProcess(State st) 
    {
        smo.truncate(sizeof(st));
        boost::interprocess::mapped_region regionWriter(smo, read_write);
        
        auto pState = static_cast<State*>(regionWriter.get_address());
        *pState     = st;
    }

    State getStateFromAnotherProcess()
    {
        boost::interprocess::mapped_region regionReader(smo, read_only);
        const auto pState = static_cast<State*>(regionReader.get_address());
        return *pState;
    }

private:
    boost::interprocess::shared_memory_object smo;
};
