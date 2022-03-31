set(TARGET LinuxWidgets)

set(SOURCE_FILES
        LinuxButton.hpp
        LinuxCheckBox.hpp
        LinuxField.hpp
        LinuxWidgets.hpp)

add_library(${TARGET} INTERFACE)
target_sources(${TARGET} INTERFACE ${SOURCE_FILES})
target_include_directories(${TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/LinuxWidgets)
