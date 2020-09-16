//
// Created by Joker on 2020/9/16.
//

#ifndef FFMPEG_JAVACALLHELPER_H
#define FFMPEG_JAVACALLHELPER_H

#endif //FFMPEG_JAVACALLHELPER_H

#include <jni.h>

//标记线程 子线程attach
#define THREAD_MAIN 1
#define THREAD_CHILD 1

//打不开视频,地址有误
#define CAN_NOT_OPEN_URL 1
//找不到流媒体
#define CAN_NOT_FIND_STREAMS 2
//找不到解码器
#define FIND_DECODER_FALL 3
//无法根据解码器创建上下文
#define ALLOC_CODEC_CONTEXT_FAIL 4
//根据流信息 配置上下文参数失败
#define CODEC_CONTEXT_PARAMETERS_FAIL 5
//打开解码器失败
#define OPEN_DECODER_FAIL 7
//没有音视频
#define NO_MEDIA 8

class JavaCallHelper {
public:
    JavaCallHelper(JavaVM *_javaVM, JNIEnv *_env, jobject &_job);

    ~JavaCallHelper();

    void onError(int code,int thread = THREAD_MAIN);

    void onPrepare(int thread = THREAD_MAIN);

    void onProgress(int progress,int thread = THREAD_MAIN);

public:
    JavaVM *javaVM;
    JNIEnv *env;
    jobject jobj;
    jmethodID jmid_error;
    jmethodID jmid_prepare;
    jmethodID jmid_progress;
};

