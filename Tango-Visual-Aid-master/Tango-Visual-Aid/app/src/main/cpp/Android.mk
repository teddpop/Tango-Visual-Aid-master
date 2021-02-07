LOCAL_PATH := $(call my-dir)
LIBS_ROOT:= $(call my-dir)/../../../libs

include $(CLEAR_VARS)
LOCAL_MODULE    := libvisual_aid
LOCAL_SHARED_LIBRARIES := tango_client_api tango_support_api
LOCAL_CFLAGS    := -Werror -std=c++11
LOCAL_SRC_FILES := native-lib.cpp \
                   VisualAid.cpp \
                   UdpServer.cpp
LOCAL_LDLIBS    := -llog -lGLESv3 -L$(SYSROOT)/usr/lib
include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(LIBS_ROOT))
$(call import-module,tango_client_api)
$(call import-module,tango_support_api)