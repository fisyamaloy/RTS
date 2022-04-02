set(TARGET WindowsWidgets)

set(SOURCE_FILES
        WindowsButton.hpp
        WindowsCheckBox.hpp
        WindowsField.hpp
        WindowsWidgets.hpp)

add_library(${TARGET} STATIC ${SOURCE_FILES})

set_target_properties(${TARGET} PROPERTIES
    LINKER_LANGUAGE CXX)

target_link_libraries(${TARGET} PUBLIC Widgets.Static)
