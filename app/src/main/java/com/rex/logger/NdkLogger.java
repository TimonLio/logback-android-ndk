package com.rex.logger;

import android.util.Log;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import proguard.annotation.KeepName;

@KeepName
/**
 * Gather native log into logback, for easy control save log into SDCard
 */
public class NdkLogger {

    private static final Logger sLogger = LoggerFactory.getLogger("Rex");

    @KeepName
    public static void logWrite(int level, String message) {
        //sLogger.trace("level:{} message:{}", level, message);
        switch (level) {
        case Log.VERBOSE:
            sLogger.trace(message);
            break;
        case Log.DEBUG:
            sLogger.debug(message);
            break;
        case Log.INFO:
            sLogger.info(message);
            break;
        case Log.WARN:
            sLogger.warn(message);
            break;
        case Log.ERROR:
            sLogger.error(message);
            break;
        }
    }

    static {
        try {
            System.loadLibrary("logger");
        } catch (UnsatisfiedLinkError ex) {
            sLogger.error("Failed to load library.", ex);
        }
    }
}
