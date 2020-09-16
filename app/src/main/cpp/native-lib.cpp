#include <jni.h>
#include <string>
#include "EnjoyPlayer.h"


JavaVM *javaVM = 0;
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved){
    javaVM = vm;
    return JNI_VERSION_1_4;
};

/**
 * 实现native与java层简历关联
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ffmpeg_EnjoyPlayer_nativeInit(JNIEnv *env, jobject thiz) {

    EnjoyPlayer *player = new EnjoyPlayer(new JavaCallHelper(javaVM,env,thiz));
    //指针回传给java
    return reinterpret_cast<jlong>(player);
}



extern "C"
JNIEXPORT void JNICALL
Java_com_example_ffmpeg_EnjoyPlayer_setDataSource(JNIEnv *env, jobject thiz, jlong nativeHandle,
                                                  jstring path_) {

    const char *path = env->GetStringUTFChars(path_, 0);

    //java传过来的指针在转成EnjoyPlayer
    EnjoyPlayer *player = reinterpret_cast<EnjoyPlayer *>(nativeHandle);
    player->setDataSource(path);

    env->ReleaseStringUTFChars(path_, path);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_ffmpeg_EnjoyPlayer_prepare(JNIEnv *env, jobject thiz, jlong nativeHandle) {
    //java传过来的指针在转成EnjoyPlayer
    EnjoyPlayer *player = reinterpret_cast<EnjoyPlayer *>(nativeHandle);
    player->prepare();
}