add_subdirectory(Server.Exec)
add_subdirectory(Server.Core)

set(TARGET Server)

add_library(${TARGET} INTERFACE)
