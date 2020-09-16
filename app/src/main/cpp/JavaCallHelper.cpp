//
// Created by Joker on 2020/9/16.
//

#include "JavaCallHelper.h"

JavaCallHelper::JavaCallHelper(JavaVM *_javaVM, JNIEnv *_env, jobject &_job) {

    //全局的EnjoyPlayer对象,相当一java层传过来的
    jobj = env->NewGlobalRef(_job);
    jclass jclazz = env->GetObjectClass(jobj);

    jmid_error = env->GetMethodID(jclazz, "onError", "(I)V");
    jmid_prepare = env->GetMethodID(jclazz, "onPrepared", "()V");
    jmid_progress = env->GetMethodID(jclazz, "onProgress", "(I)V");
}

/**
 * 析构函数
 */
JavaCallHelper::~JavaCallHelper() {
//释放全局的jobj
    env->DeleteLocalRef(jobj);
    jobj = 0;
}

/**
 *
 * @param code
 * @param thread
 */
void JavaCallHelper::onError(int code, int thread) {
    if (thread == THREAD_CHILD) {
        JNIEnv *jniEnv;
        //AttachCurrentThread(&jniEnv, 0) 使jniEnv与调用onError()方法的线程绑定
        if (javaVM->AttachCurrentThread(&jniEnv, 0) != JNI_OK) {
            return;
        }
        jniEnv->CallVoidMethod(jobj, jmid_error, code);
        javaVM->DetachCurrentThread();
    } else {
        //参数code是 java的接收的参数
        env->CallVoidMethod(jobj, jmid_error, code);
    }
}

/**
 *
 * @param thread
 */
void JavaCallHelper::onPrepare(int thread) {
    if (thread == THREAD_CHILD) {
        JNIEnv *jniEnv;
        if (javaVM->AttachCurrentThread(&jniEnv, 0) != JNI_OK) {
            return;
        }
        jniEnv->CallVoidMethod(jobj, jmid_prepare);
        javaVM->DetachCurrentThread();
    } else {
        env->CallVoidMethod(jobj, jmid_prepare);
    }
}

/**
 *
 * @param progress
 * @param thread
 */
void JavaCallHelper::onProgress(int progress, int thread) {
    if (thread == THREAD_CHILD) {
        JNIEnv *jniEnv;
        if (javaVM->AttachCurrentThread(&jniEnv, 0) != JNI_OK) {
            return;
        }
        jniEnv->CallVoidMethod(jobj, jmid_progress, progress);
        javaVM->DetachCurrentThread();
    } else {
        env->CallVoidMethod(jobj, jmid_progress, progress);
    }
}




