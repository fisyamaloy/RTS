set(TARGET Network.Test)

set(SOURCE_FILES
        BinarySerializeTest.cpp tests.cpp)

if (WIN32)
    set(EXTRA_LIBS ws2_32 wsock32)
else ()
endif ()

add_executable(${TARGET} ${SOURCE_FILES})

target_link_libraries(${TARGET} PRIVATE ${EXTRA_LIBS} CONAN_PKG::boost CONAN_PKG::gtest IntermediateProgram)

target_link_libraries(${TARGET} PUBLIC Network Utility.Public)
