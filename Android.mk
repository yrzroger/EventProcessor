###################################################################
# Copyright (c) 2020 RogerYu.
###################################################################


LOCAL_PATH:= $(call my-dir)

###################################################################
#
#               EventProcessor
#
###################################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := EventProcessor.cpp \
                   EventProcessorTest.cpp

LOCAL_SHARED_LIBRARIES := \
                       liblog \
                       libutils \
                       libstagefright_foundation

LOCAL_C_INCLUDES := \
                 system/core/include/cutils \
                 frameworks/av/include \
                 frameworks/av/media/libstagefright \
                 frameworks/native/include
                 
LOCAL_MODULE_TAGS := optional
#LOCAL_PROPRIETARY_MODULE := true

LOCAL_MODULE := EventProcessorTest

include $(BUILD_EXECUTABLE)


