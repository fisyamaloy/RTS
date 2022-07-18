set(TARGET WindowsWidgets)

set(SOURCE_FILES
        WindowsButton.hpp
        WindowsCheckBox.hpp
        WindowsField.hpp
        WindowsWidgets.hpp)

add_library(${TARGET} ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/DesignPatterns/Factory/WidgetsAbstract/)

set_target_properties(${TARGET} PROPERTIES
    LINKER_LANGUAGE CXX)

target_include_directories(${TARGET} PUBLIC ${CMAKE_SOURCE_DIR}/DesignPatterns/Factory/WidgetsAbstract/)
