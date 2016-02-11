/*
 *  Licensed to the Apache Software Foundation (ASF) under one or more
 *  contributor license agreements.  See the NOTICE file distributed with
 *  this work for additional information regarding copyright ownership.
 *  The ASF licenses this file to You under the Apache License, Version 2.0
 *  (the "License"); you may not use this file except in compliance with
 *  the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

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
