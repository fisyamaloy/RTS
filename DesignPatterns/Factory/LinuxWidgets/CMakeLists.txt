set(TARGET LinuxWidgets)

set(SOURCE_FILES
        LinuxButton.hpp
        LinuxCheckBox.hpp
        LinuxField.hpp
        LinuxWidgets.hpp)

add_library(${TARGET} ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/DesignPatterns/Factory/WidgetsAbstract/ButtonAbstract.hpp)

set_target_properties(${TARGET} PROPERTIES
    LINKER_LANGUAGE CXX)

target_include_directories(${TARGET} PUBLIC ${CMAKE_SOURCE_DIR}/DesignPatterns/Factory/WidgetsAbstract/)
