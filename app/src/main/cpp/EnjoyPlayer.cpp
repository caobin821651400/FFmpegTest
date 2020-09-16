//
// Created by Joker on 2020/9/16.
//

#include "EnjoyPlayer.h"
#include <cstring>
#include <malloc.h>
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
 */
EnjoyPlayer::EnjoyPlayer() {
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
    AVFormatContext *avFormatContext = avformat_alloc_context();
    //参数3 输入文件的格式
    //参数4 map集合
    AVDictionary *opts;
    av_dict_set(&opts, "timeout", "3000000", 0);
    int ret = avformat_open_input(&avFormatContext, path, 0, &opts);

    if (ret != 0) {
        LOGI("打开%s 失败 code:%d msg:%s", path, ret, av_err2str(ret));
        return;
    }

}
