#pragma once
#include <memory_resource>
#include <new>

// There are in standart library we have 2 types of memory resource:
// 1) Real classes with which we can create objects;
// 2) Anonymous classes - singletons.

/*
    The first memory resource is anonymous singleton, to which we have access using
    std::pmr::null_memory_resource().
*/
namespace example_1
{
    class UNKNOWN : public std::pmr::memory_resource
    {
        void* do_allocate(size_t, size_t) override
        {
            throw std::bad_alloc();
        }

        void do_deallocate(void*, size_t, size_t) override {}

        bool do_is_equal(const std::pmr::memory_resource& rhs) const noexcept override
        {
            return this == &rhs;
        }
    };

    // null_memory_resource seems like useful thing, because it is only for throwing an exception
    // when someone wants to allocate memory using null_memory_resource.
    // However it will be needed when we use more complex memory_resource.
    std::pmr::memory_resource* null_memory_resource() noexcept
    {
        static UNKNOWN singleton;
        return &singleton;
    }

}  // namespace example_1
