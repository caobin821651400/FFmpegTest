package com.example.ffmpeg;

public class EnjoyPlayer {


    private final long nativeHandle;

    public EnjoyPlayer() {
        nativeHandle = nativeInit();
    }

    public void setDataSource(String path) {
        setDataSource(nativeHandle, path);
    }


    public void prepare() {
        prepare(nativeHandle);
    }


    public void start() {

    }

    public void pause() {

    }

    public void stop() {

    }

    public native long nativeInit();

    public native void setDataSource(long nativeHandle, String path);

    private native void prepare(long nativeHandle);
}