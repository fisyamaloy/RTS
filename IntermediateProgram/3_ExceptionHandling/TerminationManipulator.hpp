#pragma once
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>

using boost::interprocess::open_or_create;
using boost::interprocess::read_only;
using boost::interprocess::read_write;

class TerminationManipulator final
{
public:
    enum State
    {
        ERROR = -1,
        SUCCESS = 0,
    };

    TerminationManipulator()
    {
        boost::interprocess::shared_memory_object temp{open_or_create, "StateShMem", read_write};
        _smo.swap(temp);
    }

    TerminationManipulator(const TerminationManipulator&) = delete;
    TerminationManipulator(TerminationManipulator&& tm) noexcept 
    {
        _smo = std::move(tm._smo);
    }
    ~TerminationManipulator()
    {
        boost::interprocess::shared_memory_object::remove("StateShMem");
    }
    TerminationManipulator*  operator=(TerminationManipulator&) = delete;
    TerminationManipulator* operator=(TerminationManipulator&& tm) noexcept
    {
        _smo = std::move(tm._smo);
        return this;
    }

    void setTerminationState(State st) 
    {
        _smo.truncate(sizeof(st));
        boost::interprocess::mapped_region regionWriter(_smo, read_write);
        
        auto pState = static_cast<State*>(regionWriter.get_address());
        *pState     = st;
    }

    State getTerminationState()
    {
        boost::interprocess::mapped_region regionReader(_smo, read_only);
        const auto pState = static_cast<State*>(regionReader.get_address());
        return *pState;
    }

private:
    boost::interprocess::shared_memory_object _smo;
};
