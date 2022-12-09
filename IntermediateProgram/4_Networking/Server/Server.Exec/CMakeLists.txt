set(TARGET Server.Exec)

set(SOURCE_FILES
   main.cpp)

if(WIN32)
    set(EXTRA_LIBS ws2_32 wsock32)
endif()

add_executable(${TARGET} ${SOURCE_FILES})

target_link_libraries(${TARGET} PRIVATE ${EXTRA_LIBS} Network CONAN_PKG::boost CONAN_PKG::yas)
target_link_libraries(${TARGET} PUBLIC Server.Core.Static)

#install(TARGETS ${TARGET}
#        CONFIGURATIONS Debug
#        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin/Server/Debug)
#install(TARGETS ${TARGET}
#        CONFIGURATIONS Release
#        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin/Server/Release)
