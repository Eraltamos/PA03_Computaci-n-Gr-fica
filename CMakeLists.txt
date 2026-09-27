cmake_minimum_required(VERSION 3.10)
project(PA3_ComputacionGrafica CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Aqui tuve que usar IA especificamente en la línea 9 por un problema de configuracion llamado "_ZNSi5seekgESt4fposI9_MbstatetE"
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(SOURCES
    src/main.cpp
    src/Application.cpp
    src/Camera.cpp
    src/Light.cpp
    src/Model.cpp
    src/Scene.cpp
    src/Texture.cpp
)

add_executable(render3d ${SOURCES})

target_link_libraries(render3d
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
)

if(APPLE)
    target_link_libraries(render3d "-framework OpenGL -framework GLUT")
endif()