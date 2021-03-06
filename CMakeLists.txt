cmake_minimum_required(VERSION 3.17.0)

project(RTS)

# Global settings. Should probably be moved to a separate file later.
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CXX_EXTENSIONS off)

# For those VSCode users
set(EXPORT_COMPILE_COMMANDS TRUE)

# Set warnings level higher and force treating them as errors.
# GCC TBD
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -O3 -pedantic -Werror)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/master/conan.cmake"
                 "${CMAKE_BINARY_DIR}/conan.cmake" TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

function(conan_cmake_run_for_special_conanfile conanfile_name)
    conan_cmake_run(CONANFILE conanfiles/${conanfile_name}
                    BASIC_SETUP CMAKE_TARGETS
                    BUILD missing)
endfunction()

IF (WIN32)
    conan_cmake_run_for_special_conanfile(windows_conanfile.txt)
ELSEIF (UNIX)
    conan_cmake_run_for_special_conanfile(unix_conanfile.txt)
ENDIF()

enable_testing()

add_subdirectory(DesignPatterns)
add_subdirectory(MemoryManagement)
add_subdirectory(Multithreading)
add_subdirectory(RTTI)
