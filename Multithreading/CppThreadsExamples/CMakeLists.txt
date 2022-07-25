set(TARGET CppThreadsExamples)

set(SOURCE_FILES
   main.cpp
   CppThreadsExamples.hpp)

find_package(Threads)

add_executable(${TARGET} ${SOURCE_FILES})
