set(TARGET Server.Core.Static)

set(SOURCE_FILES
    Server.hpp
	Server.cpp)

if(WIN32)
	list(APPEND EXTRA_LIBS ws2_32 wsock32)
endif()

add_library(${TARGET} INTERFACE)
target_sources(${TARGET} INTERFACE ${SOURCE_FILES})
target_include_directories(${TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${TARGET} INTERFACE Network Utility.Public CONAN_PKG::boost)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)

