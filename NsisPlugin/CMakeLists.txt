# set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKR_FLAGS} /SAFESEH:NO /NODEFAULTLIB:libc.lib")
# set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKR_FLAGS} /NODEFAULTLIB:libc.lib")
# set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKR_FLAGS} /SAFESEH:NO")
# set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /SAFESEH:NO")

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

aux_source_directory(./src Main_Source_Files)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/360SafeDemo
)

# 指定库文件链接路径
link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/nsis
)

# 指定生成目标
add_library(NsisPluginsDemo SHARED ${Main_Source_Files})
add_dependencies(NsisPluginsDemo 360safedemo)

# 指定目标文件链接的库名
target_link_libraries(NsisPluginsDemo 360safedemo)
target_link_libraries(NsisPluginsDemo pluginapi-x86-unicode.lib)

