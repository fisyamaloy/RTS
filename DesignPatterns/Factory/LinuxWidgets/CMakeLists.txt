set(TARGET LinuxWidgets)

set(SOURCE_FILES
        LinuxButton.hpp
        LinuxCheckBox.hpp
        LinuxField.hpp
        LinuxWidgets.hpp)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../WidgetsAbstract/)

add_library(${TARGET} STATIC ${SOURCE_FILES})

set_target_properties(${TARGET} PROPERTIES
    LINKER_LANGUAGE CXX)

target_link_libraries(${TARGET} PUBLIC Widgets.Static)
