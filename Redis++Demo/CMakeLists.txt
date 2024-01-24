cmake_minimum_required(VERSION 3.1)

project(redispub)

add_executable(redispub demo.cc) 

message(${PROJECT_SOURCE_DIR})
message("build with debug mode")

target_link_libraries(redispub
libhiredis.so
libredis++.so
)

#target_link_libraries(redispub ${APP_ROOT}/build/libredis++.so)
