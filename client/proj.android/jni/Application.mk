APP_STL := gnustl_static

APP_CPPFLAGS := -frtti -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -DGOOGLE_PROTOBUF_NO_RTTI -DHAVE_PTHREAD=1 -std=c++11 -fsigned-char
APP_LDFLAGS := -latomic
APP_PLATFORM := android-16
# APP_ABI := armeabi armeabi-v7a x86
APP_ABI := armeabi

ifeq ($(NDK_DEBUG),1)
  APP_CPPFLAGS += -DCOCOS2D_DEBUG=1
  APP_OPTIM := debug
else
  APP_CPPFLAGS += -DNDEBUG
  APP_OPTIM := release
endif
