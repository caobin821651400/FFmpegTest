//
// Created by Joker on 2020/9/16.
//

#include "EnjoyPlayer.h"
#include <cstring>
#include <malloc.h>
#include <pthread.h>
#include "XLog.h"

extern "C" {
#include <libavformat/avformat.h>
}


void *prepare_t(void *args) {
    EnjoyPlayer *player = static_cast<EnjoyPlayer *>(args);
    player->_prepare();
}

/**
 * 构造函数
 * : helper(helper）初始化helper的值
 */
EnjoyPlayer::EnjoyPlayer(JavaCallHelper *helper) : helper(helper) {
    //初始化网络
    avformat_network_init();
}

void EnjoyPlayer::setDataSource(const char *path_) {
//    //申请一块内存空间
//    path = static_cast<char *>(malloc(strlen(path_) + 1));
//    //初始化内存空间
//    memset((void *) path, 0, strlen(path) + 1);
//    //深拷贝防止其他地方释放掉传进来的path
//    memcpy(path, path_, strlen(path_));

    //C++方式
    path = new char[strlen(path_) + 1];
    strcpy(path, path_);
}

void EnjoyPlayer::prepare() {
    //开启线程,this代表参数就是当前的线程
    pthread_create(&prepareTask, 0, prepare_t, this);
}

/**
 * 线程真正执行的方法
 */
void EnjoyPlayer::_prepare() {
    avFormatContext = avformat_alloc_context();
    /**
     * 1.打开媒体文件
     */
    //参数3 输入文件的格式 参数4 map集合
    AVDictionary *opts;
    av_dict_set(&opts, "timeout", "3000000", 0);
    int ret = avformat_open_input(&avFormatContext, path, 0, &opts);

    if (ret != 0) {
        LOGI("打开%s 失败 code:%d msg:%s", path, ret, av_err2str(ret));
        helper->onError(CAN_NOT_OPEN_URL, THREAD_CHILD);
        return;
    }

    /**
     * 2.查找媒体流
     */
    ret = avformat_find_stream_info(avFormatContext, 0);

    if (ret < 0) {
        LOGE("查找媒体流 %s 失败，返回:%d 错误描述:%s", path, ret, av_err2str(ret));
        helper->onError(CAN_NOT_FIND_STREAMS, THREAD_CHILD);
        return;
    }
    //时长
    duration = avFormatContext->duration / AV_TIME_BASE;
    //读取流（视频流、音频流）
    for (int i = 0; i < avFormatContext->nb_streams; ++i) {
        AVStream *avStream = avFormatContext->streams[i];
        //AVStream包含解码信息
        AVCodecParameters *parameters = avStream->codecpar;
        //查找解码器，找不到说明不知此这种格式
        AVCodec *dec = avcodec_find_decoder(parameters->codec_id);
        if (!dec) {
            LOGI("找不到解码器");
            helper->onError(FIND_DECODER_FALL, THREAD_CHILD);
            return;
        }

        //打开解码器 解码器上下文
        AVCodecContext *avCodecContext = avcodec_alloc_context3(dec);
        //媒体信息 赋值给解码器的上下文
        if (!avCodecContext && avcodec_parameters_to_context(avCodecContext, parameters) < 0) {
            LOGI("赋值给解码器的上下文失败");
            helper->onError(ALLOC_CODEC_CONTEXT_FAIL, THREAD_CHILD);
            return;
        }

        //打开解码器 也可以理解为初始化解码器
        if (avcodec_open2(avCodecContext, dec, 0) != 0) {
            LOGI("解码器初始化失败");
            helper->onError(OPEN_DECODER_FAIL, THREAD_CHILD);
            return;
        }

        //判断音频还是视频
        if (parameters->codec_type == AVMEDIA_TYPE_AUDIO) {

        } else if (parameters->codec_type == AVMEDIA_TYPE_VIDEO) {
            //视频
            int fps = av_q2d(avStream->avg_frame_rate);
            videoChannel = new VideoChannel(i, helper, avCodecContext, avStream->time_base, fps);
        } else {

        }

    }

    //没有视频的情况
    if (!videoChannel) {
        LOGI("没有音视频");
        helper->onError(NO_MEDIA, THREAD_CHILD);
        return;
    }

    //准备完成回调给java层
    helper->onPrepare(THREAD_CHILD);
}

/**
 * start执行的方法
 * @param args
 * @return
 */
void *start_t(void *args) {
    EnjoyPlayer *player = static_cast<EnjoyPlayer *>(args);
    player->_start();
    return 0;
}

/**
 * 开始
 */
void EnjoyPlayer::start() {

    isPlaying = 1;
    if (videoChannel) {
        videoChannel->play();
    }

    pthread_create(&startTask, 0, start_t, this);

}

void EnjoyPlayer::_start() {
    int ret;
    while (isPlaying) {
        AVPacket *packet = av_packet_alloc();
        ret = av_read_frame(avFormatContext, packet);
        if (ret == 0) {
            //没有数据了
            if (videoChannel && packet->stream_index == videoChannel->channelId) {
                videoChannel->pkt_queue.enQueue(packet);
            }
        } else if (ret == AVERROR_EOF) {
            //读取完毕
            if (videoChannel->pkt_queue.empty() && videoChannel->frame_queue.empty()) {
                //播放完毕

                return;
            }

        } else {

        }
    }
    isPlaying = 0;
    videoChannel->stop();
}
