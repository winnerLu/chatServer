
aux_source_directory(. SRC_LIST)

# 也可以使用set()定义源文件列表，需要手动添加
# set(SRC_LIST
#     muduo_server.cpp
# )
# 指定生成可执行文件
add_executable(ChatServer ${SRC_LIST})

# 为目标设置包含目录
target_include_directories(ChatServer PRIVATE ${PROJECT_SOURCE_DIR}/include/server)

# 链接库文件
target_link_libraries(ChatServer muduo_net muduo_base pthread)