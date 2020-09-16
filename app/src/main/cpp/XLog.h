//
// Created by Joker on 2020/9/16.
//

#ifndef FFMPEG_XLOG_H
#define FFMPEG_XLOG_H

#include <android/log.h>

#define  LOG_TAG    "nativeprint"

#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif //FFMPEG_XLOG_H
