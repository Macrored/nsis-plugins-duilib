cmake_minimum_required(VERSION 3.0)

# 设置工程属性
project(NsisPluginsDemo)
add_definitions(-DUNICODE -D_UNICODE) # 定义工程的字符编码为Unicode编码
set(CMAKE_CXX_FLAGS_RELEASE "/MT") # Release模式使用静态链接其他动态库
set(CMAKE_CXX_FLAGS_DEBUG "/MTd") # Debug模式使用静态链接其他动态库

# 引用Boost库
find_package(Boost 1.7.0 REQUIRED COMPONENTS system)
set(Boost_USE_STATIC_LIBS ON)

# 编译参数
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_definitions(-std=c++14) # c++14标准
    add_compile_options(-g) # gdb调试模式，默认则是三级二进制优化模式-O3
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions(/std:c++14)
endif(CMAKE_SYSTEM_NAME MATCHES "Linux")

# 获取源文件
aux_source_directory(. SourceFiles)
message(STATUS "Boost_INCLUDE_DIRS:${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS:${Boost_LIBRARY_DIRS}")
message(STATUS "Boost_LIBRARIES:${Boost_LIBRARIES}")

# 头文件查找路径
include_directories(
    ${PROJECT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS})
# 库文件查找路径
link_directories(${Boost_LIBRARY_DIRS})

add_subdirectory(DuiLib)
add_subdirectory(360SafeDemo)
add_subdirectory(NsisPlugin)