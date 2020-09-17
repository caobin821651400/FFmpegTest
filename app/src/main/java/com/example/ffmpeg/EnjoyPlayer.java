package com.example.ffmpeg;

import com.example.ffmpeg.listener.OnErrorListener;
import com.example.ffmpeg.listener.OnPrepareListener;
import com.example.ffmpeg.listener.OnProgressListener;

public class EnjoyPlayer {


    private final long nativeHandle;

    private OnErrorListener onErrorListener;
    private OnPrepareListener onPrepareListener;
    private OnProgressListener onProgressListener;


    public EnjoyPlayer() {
        nativeHandle = nativeInit();
    }

    /**
     * 设置播放路径
     *
     * @param path
     */
    public void setDataSource(String path) {
        setDataSource(nativeHandle, path);
    }

    /**
     * 准备阶段
     */
    public void prepare() {
        prepare(nativeHandle);
    }

    /**
     * 开始播放
     */
    public void start() {
        start(nativeHandle);
    }

    /**
     * 暂停
     */
    public void pause() {

    }

    /**
     * 停止
     */
    public void stop() {

    }

    /**
     * 错误回调
     *
     * @param errCode
     */
    private void onError(int errCode) {
        if (onErrorListener != null) {
            onErrorListener.onError(errCode);
        }
    }

    /**
     * 进度
     *
     * @param progress
     */
    private void onProgress(int progress) {
        if (onProgressListener != null) {
            onProgressListener.onProgress(progress);
        }
    }

    /**
     * 准备完成
     */
    private void onPrepared() {
        if (onPrepareListener != null) {
            onPrepareListener.onPrepared();
        }
    }

    /**
     * @param listener
     */
    public void setOnErrorListener(OnErrorListener listener) {
        this.onErrorListener = listener;
    }

    /**
     * @param listener
     */
    public void setOnPrepareListener(OnPrepareListener listener) {
        this.onPrepareListener = listener;
    }

    /**
     * @param listener
     */
    public void setOnProgressListener(OnProgressListener listener) {
        this.onProgressListener = listener;
    }

    public native long nativeInit();

    public native void setDataSource(long nativeHandle, String path);

    private native void prepare(long nativeHandle);

    private native void start(long nativeHandle);
}