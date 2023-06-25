cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(opengl LANGUAGES CXX)

# 设置可执行文件到bin文件夹下
set(EXECUTE_FILE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXECUTE_FILE})

set(GLEW ${CMAKE_SOURCE_DIR}/lib/glew32.lib)
set(GLFW ${CMAKE_SOURCE_DIR}/lib/glfw3.lib)
set(SOIL2 ${CMAKE_SOURCE_DIR}/lib/soil2-debug.lib)
set(opengl opengl32.lib)

set(SOURCES
    src/opengl.cpp
)#创建

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
) 

target_link_libraries(
    ${PROJECT_NAME}
    ${GLEW}   
	${GLFW}   
	${SOIL2}   
	${opengl}
)

add_custom_command(
        TARGET ${PROJECT_NAME}  PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/lib/glew32.dll
                ${CMAKE_CURRENT_SOURCE_DIR}/build)
