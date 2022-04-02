set(TARGET LinuxWidgets)

set(SOURCE_FILES
        LinuxButton.hpp
        LinuxCheckBox.hpp
        LinuxField.hpp
        LinuxWidgets.hpp)

add_library(${TARGET} STATIC ${SOURCE_FILES})

set_target_properties(${TARGET} PROPERTIES
    LINKER_LANGUAGE CXX)

target_link_libraries(${TARGET} PUBLIC WidgetsAbstract)
