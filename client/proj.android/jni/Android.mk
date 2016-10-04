LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# $(call import-add-path, $(LOCAL_PATH)/../../cocos2d)
# $(call import-add-path, $(LOCAL_PATH)/../../cocos2d/external)
# $(call import-add-path, $(LOCAL_PATH)/../../cocos2d/cocos)
# $(call import-add-path,$(LOCAL_PATH)/../../../../../cocos2d/cocos/audio/include)
$(call import-add-path, $(LOCAL_PATH)/../../../../../cocos2d/cocos/prebuilt-mk)
$(call import-add-path, $(LOCAL_PATH))

LOCAL_MODULE := BrrGame_shared

LOCAL_MODULE_FILENAME := libBrrGame

# /opt/protobuf/src/google/protobuf/stubs/atomicops_internals_x86_gcc.cc
CC_LITE_SRC_FILES := /opt/protobuf/src/google/protobuf/stubs/common.cc \
/opt/protobuf/src/google/protobuf/stubs/once.cc \
/opt/protobuf/src/google/protobuf/stubs/strutil.cc \
/opt/protobuf/src/google/protobuf/stubs/status.cc \
/opt/protobuf/src/google/protobuf/stubs/stringpiece.cc \
/opt/protobuf/src/google/protobuf/stubs/stringprintf.cc \
/opt/protobuf/src/google/protobuf/stubs/int128.cc \
/opt/protobuf/src/google/protobuf/stubs/structurally_valid.cc \
/opt/protobuf/src/google/protobuf/extension_set.cc \
/opt/protobuf/src/google/protobuf/generated_message_util.cc \
/opt/protobuf/src/google/protobuf/message_lite.cc \
/opt/protobuf/src/google/protobuf/repeated_field.cc \
/opt/protobuf/src/google/protobuf/arenastring.cc \
/opt/protobuf/src/google/protobuf/arena.cc \
/opt/protobuf/src/google/protobuf/wire_format_lite.cc \
/opt/protobuf/src/google/protobuf/io/coded_stream.cc \
/opt/protobuf/src/google/protobuf/io/zero_copy_stream.cc \
/opt/protobuf/src/google/protobuf/io/zero_copy_stream_impl_lite.cc

FILE_LIST := $(wildcard $(LOCAL_PATH)/../../Classes/*.c*)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/*/*.c*)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/*/*/*.c*)

LOCAL_SRC_FILES := cpp/main.cpp \
$(FILE_LIST:$(LOCAL_PATH)/%=%) \
$(CC_LITE_SRC_FILES)

LOCAL_CPPFLAGS := -DSDKBOX_ENABLED

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
$(LOCAL_PATH)/../../Classes/Dialog \
$(LOCAL_PATH)/../../Classes/Libs \
$(LOCAL_PATH)/../../Classes/MessageSerializer \
$(LOCAL_PATH)/../../Classes/Network \
$(LOCAL_PATH)/../../Classes/ProtoMessages \
/opt/protobuf/src

LOCAL_LDLIBS := -landroid
LOCAL_LDLIBS += -llog

LOCAL_WHOLE_STATIC_LIBRARIES := android_native_app_glue
LOCAL_WHOLE_STATIC_LIBRARIES += sdkbox
LOCAL_WHOLE_STATIC_LIBRARIES += PluginIAP
LOCAL_WHOLE_STATIC_LIBRARIES += PluginGoogleAnalytics
LOCAL_WHOLE_STATIC_LIBRARIES += PluginVungle
LOCAL_WHOLE_STATIC_LIBRARIES += PluginSdkboxPlay

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,./sdkbox)
$(call import-module,./pluginiap)
$(call import-module,./plugingoogleanalytics)
$(call import-module,./pluginvungle)
$(call import-module,./pluginsdkboxplay)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
