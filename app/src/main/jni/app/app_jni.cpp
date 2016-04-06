/*
 * Copyright (C) 2009 The Android Open Source Project
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
 *
 */

#include <string.h>
#include <jni.h>

#include <logging.h>


jstring
Java_com_rex_sample_AppJNI_nativeGetABI(JNIEnv* env, jobject thiz)
{
#if defined(__arm__)
  #if defined(__ARM_ARCH_7A__)
    #if defined(__ARM_NEON__)
      #if defined(__ARM_PCS_VFP)
        #define ABI "armeabi-v7a/NEON (hard-float)"
      #else
        #define ABI "armeabi-v7a/NEON"
      #endif
    #else
      #if defined(__ARM_PCS_VFP)
        #define ABI "armeabi-v7a (hard-float)"
      #else
        #define ABI "armeabi-v7a"
      #endif
    #endif
  #else
   #define ABI "armeabi"
  #endif
#elif defined(__i386__)
   #define ABI "x86"
#elif defined(__x86_64__)
   #define ABI "x86_64"
#elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
   #define ABI "mips64"
#elif defined(__mips__)
   #define ABI "mips"
#elif defined(__aarch64__)
   #define ABI "arm64-v8a"
#else
   #define ABI "unknown"
#endif

    return (*env)->NewStringUTF(env, "Hello from JNI !  Compiled with ABI " ABI ".");
}

extern "C" jint
JNI_OnLoad(JavaVM * vm, void * reserved)
{
    JNIEnv *	env	= NULL;
    jclass	clazz;
    LOGV("JNI_Onload vm:%p reserved:%p", vm, reserved);

    if (JNI_OK != vm->GetEnv((void**) &env, JNI_VERSION_1_4)) {
	LOGE("JNI_OnUnload GetEnv JNI_VERSION_1_4 failed");
	return;
    }

    logback_init(vm, env);

    return JNI_VERSION_1_4;
}

extern "C" void
JNI_OnUnload(JavaVM * vm, void * reserved)
{
    JNIEnv *    env     = NULL;
    LOGV("JNI_OnUnload vm:%p reserved:%p", vm, reserved);

    if (JNI_OK != vm->GetEnv((void**) &env, JNI_VERSION_1_4)) {
	LOGE("JNI_OnUnload GetEnv JNI_VERSION_1_4 failed");
	return;
    }

    logback_uninit(env);
}

// vim:ts=8:sw=4:

