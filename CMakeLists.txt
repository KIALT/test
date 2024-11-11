cmake_minimum_required(VERSION 3.5.0)
project(ForwardModule VERSION 0.1.0 LANGUAGES C CXX)


# 设置C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置c 11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


add_executable(${PROJECT_NAME} main.cpp)

# 设置头文件路径
target_include_directories(${PROJECT_NAME}  PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/base
    ${PROJECT_SOURCE_DIR}/driver
    ${PROJECT_SOURCE_DIR}/helper
    ${PROJECT_SOURCE_DIR}/utils
    ${PROJECT_SOURCE_DIR}/interface
    ${PROJECT_SOURCE_DIR}/plugins
)