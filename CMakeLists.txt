cmake_minimum_required(VERSION 3.10)
project(GertecMicroterminal VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(src/Config.hpp.in Config.hpp)

include_directories(
    "${PROJECT_BINARY_DIR}"
    src/
) 

file(GLOB SRCS 
    "${PROJECT_SOURCE_DIR}/src/*/*.cpp"
)

# Tests 
## TcpTransport test 
add_executable(TcpTransport tests/TcpTransport.cpp ${SRCS})
set_target_properties(TcpTransport PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")


