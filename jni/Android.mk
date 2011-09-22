LOCAL_PATH := $(call my-dir)

#
# Define the prebuilt libraries we are going to use
# read docs/PREBUILTS.html of the android ndk
# to understand the syntax
include $(CLEAR_VARS)
LOCAL_MODULE := binder-1-prebuilt
LOCAL_SRC_FILES := ../syslib/native/lib/libutils.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := binder-2-prebuilt
LOCAL_SRC_FILES := ../syslib/native/lib/libbinder.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := binder-3-prebuilt
LOCAL_SRC_FILES :=  ../syslib/native/lib/libui.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := helloworldservice.cpp helloworldclient.cpp main_helloworldservice.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../libhelloworldservice/include \
	$(LOCAL_PATH)/../syslib/native/frameworks/base/include \
	$(LOCAL_PATH)/../syslib/native/system/core/include 



LOCAL_MODULE := helloworldservice

LOCAL_PRELINK_MODULE := false

#
LOCAL_SHARED_LIBRARIES += liblog libutils libbinder libui
LOCAL_LDLIBS +=  -L$(LOCAL_PATH)/../libs/armeabi -lbinder -llog -lutils -lui
LOCAL_CFLAGS += -DPLATFORM_ANDROID
#LOCAL_CFLAGS += -Idalvik/libnativehelper/include/nativehelper

#include $(BUILD_EXECUTABLE)
include $(BUILD_SHARED_LIBRARY)

