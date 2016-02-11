/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Logging support, provide the level definition and support logging to logcat, stdout and Java logback
 * When using logback, need add com/rex/logger/NdkLogger.java into project
 */

#ifndef _LOGGING_H_
#define _LOGGING_H_

#ifndef LOG_TAG
#  define LOG_TAG	"Rex"
#endif

#ifndef LOG_LEVEL
#  define LOG_LEVEL	LOG_LEVEL_DEBUG
#endif

// values here must match those in android_LogPriority
#define	LOG_LEVEL_ALL		1
#define	LOG_LEVEL_VERBOSE	2
#define	LOG_LEVEL_DEBUG		3
#define	LOG_LEVEL_INFO		4
#define	LOG_LEVEL_WARN		5
#define	LOG_LEVEL_ERROR		6
#define	LOG_LEVEL_FATAL		7
#define	LOG_LEVEL_SILENT	8

#include <stdio.h>
#include <stdarg.h>
#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

void __stdout_log_print(const int level, const char * format, ...);
void __stdout_log_vprint(const int level, const char * format, va_list ap);
void __stdout_log_write(const int level, const char * msg);

void logback_init(JavaVM * jVM, JNIEnv * env);
void logback_uninit(JNIEnv * env);
void __logback_print(const int level, const char * format, ...);
void __logback_vprint(const int level, const char * format, va_list ap);
void __logback_write(const int level, const char * msg);

#ifdef __cplusplus
} //extern "C"
#endif


#ifdef LOG_OUTPUT_STDOUT
#  define LOG_PRINT(prio, format, ...)	__stdout_log_print(prio, format, ##__VA_ARGS__)
#  define LOG_VPRINT(prio, format, ap)	__stdout_log_vprint(prio, format, ap)
#  define LOG_WRITE(prio, msg)		__stdout_log_write(prio, msg)
#elif defined(LOG_OUTPUT_LOGBACK)
#  define LOG_PRINT(prio, format, ...)	__logback_print(prio, format, ##__VA_ARGS__)
#  define LOG_VPRINT(prio, format, ap)	__logback_vprint(prio, format, ap)
#  define LOG_WRITE(prio, msg)		__logback_write(prio, msg)
#else
#  include <android/log.h>
#  define LOG_PRINT(prio, format, ...)	__android_log_print(prio, LOG_TAG, format, ##__VA_ARGS__)
#  define LOG_VPRINT(prio, format, ap)	__android_log_vprint(prio, LOG_TAG, format, ap)
#  define LOG_WRITE(prio, msg)		__android_log_write(prio, LOG_TAG, msg)
#endif

#if LOG_LEVEL > LOG_LEVEL_VERBOSE
#  define LOGV(...)
#else
#  define LOGV(...)	LOG_PRINT(LOG_LEVEL_VERBOSE, __VA_ARGS__)
#endif

#if LOG_LEVEL > LOG_LEVEL_DEBUG
#  define LOGD(...)
#else
#  define LOGD(...)	LOG_PRINT(LOG_LEVEL_DEBUG, __VA_ARGS__)
#endif

#if LOG_LEVEL > LOG_LEVEL_INFO
#  define LOGI(...)
#else
#  define LOGI(...)	LOG_PRINT(LOG_LEVEL_INFO, __VA_ARGS__)
#endif

#if LOG_LEVEL > LOG_LEVEL_WARN
#  define LOGW(...)
#else
#  define LOGW(...)	LOG_PRINT(LOG_LEVEL_WARN, __VA_ARGS__)
#endif

#if LOG_LEVEL > LOG_LEVEL_ERROR
#  define LOGE(...)
#else
#  define LOGE(...)	LOG_PRINT(LOG_LEVEL_ERROR, __VA_ARGS__)
#endif


#endif /* #ifndef _LOGGING_H_ */

// vim:ts=8:sw=4:
