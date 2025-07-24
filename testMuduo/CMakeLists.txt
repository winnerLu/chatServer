cmake_minimum_required(VERSION 3.10)
project(chatServer)

# 配置编译选项
set(CMAKE_CXX_STANDARD 11)

# 配置头文件搜索路径
# include_directories(/usr/local/include)
# 配置库文件搜索路径
# link_directories(/usr/local/lib)

# 设置需要编译的源文件列表
set(SRC_LIST muduo_server.cpp)

# 设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 把.指定路径下的所有源文件添加到SRC_LIST变量中
# aux_source_directory(. SRC_LIST)

# 生成可执行文件，由SRC_LIST变量指定源文件编译而来
add_executable(chatServer ${SRC_LIST})
# add_executable(chatServer muduo_server.cpp)

# 链接库文件
target_link_libraries(chatServer muduo_net muduo_base pthread)
