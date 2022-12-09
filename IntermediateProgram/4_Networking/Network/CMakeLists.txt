set(TARGET Network)

set(SOURCE_FILES
    Include/CompressionHandler.hpp
    Include/Connection.hpp
    Include/EncryptionHandler.hpp
    Include/Handler.hpp
    Include/SerializationHandler.hpp
    Include/YasSerializer.hpp
    Include/Message.hpp
    Include/SafeQueue.hpp)

add_library(${TARGET} INTERFACE)
target_sources(${TARGET} INTERFACE ${SOURCE_FILES})
target_include_directories(${TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Include)

target_link_libraries(${TARGET} INTERFACE CONAN_PKG::boost CONAN_PKG::yas Utility.Public)
