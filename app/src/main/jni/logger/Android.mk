
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE		:= logger
LOCAL_SRC_FILES         := logging.cpp
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
LOCAL_EXPORT_LDLIBS	:= -llog
include $(BUILD_STATIC_LIBRARY)

