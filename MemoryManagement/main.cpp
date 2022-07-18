#include <iostream>
#include <vector>

#include "MemoryResources.hpp"

int main()
{
    // Throws an exception
    /*auto p = example_1::null_memory_resource()->allocate(4);
    (p);*/

    int* a = static_cast<int*>(example_2::new_delete_resource()->allocate(sizeof(int)));
    *a     = 10;
    example_2::new_delete_resource()->deallocate(a, sizeof(int));

    alignas(std::max_align_t) char      bigBuffer[5];
    std::pmr::monotonic_buffer_resource mbr(
        bigBuffer, sizeof(bigBuffer), example_1::null_memory_resource());

    int* b = static_cast<int*>(mbr.allocate(sizeof(int)));
    *b     = 300;

    // exception is here
    //int* c = static_cast<int*>(mbr.allocate(sizeof(int)));
    //*c     = 150;

    return 0;
}
