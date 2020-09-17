cmake_minimum_required(VERSION 3.4.1)

aux_source_directory(. SOURCE)

add_library(
        native-lib
        SHARED
        ${SOURCE})


##导入静态库
#add_library(avcode STATIC IMPROTED)
#set_target_properties(avcode PROPERTIES IMPROTED_LOCATION ...)

#设置一个变量
set(libs ${CMAKE_SOURCE_DIR}/${ANDROID_ABI})
#引入库查找路径 -L
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${libs}")

#引入头文件
include_directories(include)

target_link_libraries(
        native-lib
        #armeabi-v7a 下的静态库引入
        avfilter avformat  avcodec avutil swresample swscale rtmp android z
        OpenSLES
        log)