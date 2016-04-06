package com.rex.sample;

import android.content.Context;
import android.os.Build;
import android.os.Handler;
import android.os.Message;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.nio.ByteBuffer;

import proguard.annotation.KeepName;

public class AppJNI {

    private static final Logger sLogger = LoggerFactory.getLogger("RexSample");

    public static String getABI() {
        String abi = nativeGetABI();
        sLogger.trace("abi:{}", abi);
        return abi;
    }

    private static native String nativeGetABI();

    static {
        try {
            System.loadLibrary("libapp");
        } catch (UnsatisfiedLinkError ex) {
            sLogger.error("AppJNI load library failed ex:{}", ex.toString());
        }
    }
}
