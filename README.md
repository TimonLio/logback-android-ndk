# logback-android-ndk
<sup>v0.9.0</sup>

Overview
--------
logback-android-ndk is a NDK wrapper for logback-android, if you are using logback for your apps, it is easily to send logs to file on Java, but if your app also used NDK, you need this library to help you mix the Java logs and NDK logs into logback.


Quick Start
--------
1. Copy native library logger into your NDK project
2. Add logger library as static library in Android.mk
'''
LOCAL_STATIC_LIBRARIES += liblogger
'''
3. Define log output type in Android.mk
'''
ifeq ($(NDK_DEBUG),1)
LOCAL_CFLAGS += -DLOG_OUTPUT_LOGCAT
else
LOCAL_CFLAGS += -DLOG_OUTPUT_LOGBACK
endif
'''
4. Modify JNI_OnLoad() and JNI_OnUnload()
```
extern "C" jint
JNI_OnLoad(JavaVM * vm, void * reserved)
{
    JNIEnv * env = NULL;
    if (JNI_OK == vm->GetEnv((void**) &env, JNI_VERSION_1_4)) {
        logback_init(vm, env);
    }
}

extern "C" void
JNI_OnUnload(JavaVM * vm, void * reserved)
{
    JNIEnv * env = NULL;
    if (JNI_OK == vm->GetEnv((void**) &env, JNI_VERSION_1_4)) {
        logback_uninit(env);
    }
}
```
5. Add com.rex.logger.NdkLogger into your Java source folder


ProGuard
--------
Refer to logback-android, you need to keep for slf4j and logback
```
-keep class ch.qos.** { *; }
-keep class org.slf4j.** { *; }
-keepatributes *Annotation*
```

And ignore warning if you don't use mailing features of logback
```
-dontwarn ch.qos.logback.core.net.*
```

Add ProGuard annotation supports into your project
Or
Keep the wrapper class in proguard rules manually
```
-keep class com.rax.logger.** { *; }
```


Best Practices
--------
Coming soon

