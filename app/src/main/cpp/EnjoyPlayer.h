//
// Created by Joker on 2020/9/16.
//


#ifndef FFMPEG_ENJOYPLAYER_H
#define FFMPEG_ENJOYPLAYER_H


#include <pthread.h>
#include <android/native_window_jni.h>

#include "VideoChannel.h"

extern "C" {
#include <libavformat/avformat.h>
};

class EnjoyPlayer {
    friend void *prepare_t(void *args);

    friend void *start_t(void *args);

public:
    EnjoyPlayer(JavaCallHelper *helper);

    ~EnjoyPlayer();

    void start();


public:
    void setDataSource(const char *path);

    void prepare();

private:
    void _prepare();

    void _start();

private:
    char *path;
    pthread_t prepareTask;
    JavaCallHelper *helper;
    int64_t duration;
    VideoChannel *videoChannel = 0;
//    AudioChannel *audioChannel = 0;
    pthread_t startTask;
    bool isPlaying;
    AVFormatContext *avFormatContext = 0;

    ANativeWindow *window = 0;
};


//class EnjoyPlayer {
//    friend void *prepare_t(void *args);
//    friend void *start_t(void *args);
//
//public:
//    EnjoyPlayer(JavaCallHelper *helper);
//
//    void setDataSource(const char *path);
//
//    void prepare();
//
//    void start();
//
//
//private:
//    void _prepare();
//    void _start();
//
//private:
//    char *path;
//    pthread_t prepareTask;
//    JavaCallHelper *helper;
//    int64_t duration;//时长（秒）
//    VideoChannel *videoChannel=0;
//    bool isPlaying;
//    pthread_t startTask;
//    AVFormatContext *avFormatContext;
//
//
//};
#endif //FFMPEG_ENJOYPLAYER_H