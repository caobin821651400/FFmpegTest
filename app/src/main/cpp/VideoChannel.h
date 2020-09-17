//
// Created by Joker on 2020/9/17.
//

#ifndef FFMPEG_VIDEOCHANNEL_H
#define FFMPEG_VIDEOCHANNEL_H

#include <android/native_window.h>
#include "BaseChannel.h"
#include "AudioChannel.h"

extern "C" {
#include "libavcodec/avcodec.h"
};


#endif //FFMPEG_VIDEOCHANNEL_H

class VideoChannel : public BaseChannel {
public:
    VideoChannel(int channelId, JavaCallHelper *helper, AVCodecContext *avCodecContext,
                 const AVRational &base, double fps);

    virtual void play();

    virtual void stop();

    virtual void decode();


private:
    double fps;
};
