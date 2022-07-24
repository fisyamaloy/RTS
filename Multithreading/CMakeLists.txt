set(TARGET Multithreading)

add_subdirectory(PThreadExamples)
add_subdirectory(CppThreadsExamples)

add_library(${TARGET} INTERFACE)
