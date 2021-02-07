#ifndef TANGO_VISUAL_AID_UTIL_H
#define TANGO_VISUAL_AID_UTIL_H

#include <android/log.h>

// used to get logcat outputs which can be regex filtered by the LOG_TAG we give
// So in Logcat you can filter this example by putting VisualAid
#define LOG_TAG "VisualAid"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif //TANGO_VISUAL_AID_UTIL_H
