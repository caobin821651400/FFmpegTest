//
// Created by Administrator on 2019/11/14.
//

#ifndef PLAYER_BASECHANNEL_H
#define PLAYER_BASECHANNEL_H

extern "C" {
#include "include/libavcodec/avcodec.h"
};

#include "JavaCallHelper.h"
#include "XLog.h"
#include "include/libavutil/rational.h"
#include "include/libavutil/frame.h"

class BaseChannel {
public:
    BaseChannel(int channelId, JavaCallHelper *helper, AVCodecContext *avCodecContext, AVRational
    base) {
    }



};

#endif //PLAYER_BASECHANNEL_H
