//
// Created by Joker on 2020/9/16.
//

#include <opencl-c-base.h>
#include <pthread.h>
#include "JavaCallHelper.h"

#ifndef FFMPEG_ENJOYPLAYER_H
#define FFMPEG_ENJOYPLAYER_H

#endif //FFMPEG_ENJOYPLAYER_H


class EnjoyPlayer {
public:
    EnjoyPlayer(JavaCallHelper *helper);

    friend void *prepare_t(void *args);

    void setDataSource(const char *path);

    void prepare();

private:
    char *path;
    pthread_t prepareTask;
    JavaCallHelper *helper;
    int64_t duration;//时长（秒）

    void _prepare();
};