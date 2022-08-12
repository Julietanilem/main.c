cmake_minimum_required(VERSION 3.21)
project(JuegoETE C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)

include_directories("C:/allegro/include")
link_directories("C:/allegro/lib")

add_executable(JuegoETE main.c)
target_link_libraries(JuegoETE PUBLIC allegro_monolith)