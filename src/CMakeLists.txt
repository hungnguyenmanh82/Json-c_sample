Set(PROJECT_SOURCE_DIR .)
#add thư mục include *.h vào
include_directories (.)

# tạo biến chứa chứa source code
set(HelloWorld_SOURCES main.cpp function.cpp)

# biên dịch file exe => dùng tên hello thay thế tên mặc định 
add_executable(hello ${HelloWorld_SOURCES})


 
