//
// Created by Joker on 2020/9/17.
//

#include "VideoChannel.h"


VideoChannel::VideoChannel(int channelId, JavaCallHelper *helper, AVCodecContext *avCodecContext,
                           const AVRational &base, double fps)
        : BaseChannel(channelId, helper, avCodecContext, base), fps(fps) {


}

void VideoChannel::decode() {

}

void VideoChannel::stop() {

}

void VideoChannel::play() {

}
