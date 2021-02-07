#include <jni.h>

#include "VisualAid.h"

static VisualAid app;

#ifdef __cplusplus
extern "C" {
#endif
jint JNI_OnLoad(JavaVM* vm, void*) {
  // We need to store a reference to the Java VM so that we can call into the
  // Java layer to trigger pulse function.
  app.SetJavaVM(vm);
  return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL
Java_com_spencerfricke_tango_1visual_1aid_TangoJniNative_onCreate(
    JNIEnv* env, jobject clazz, jobject activity) {
  app.OnCreate(env, activity);
}

JNIEXPORT void JNICALL
Java_com_spencerfricke_tango_1visual_1aid_TangoJniNative_onTangoServiceConnected(
    JNIEnv* env, jobject, jobject binder) {
  app.OnTangoServiceConnected(env, binder);
}

JNIEXPORT void JNICALL
Java_com_spencerfricke_tango_1visual_1aid_TangoJniNative_newIp(
    JNIEnv* env, jobject, jobject binder, jstring ipAddr) {

  jboolean copy = JNI_TRUE;
  // Need to fix, crashes on getString
//  const char* _ipAddr = env->GetStringUTFChars(ipAddr, &copy);
//  app.NewIp(_ipAddr);
}

JNIEXPORT void JNICALL
Java_com_spencerfricke_tango_1visual_1aid_TangoJniNative_onPause(
    JNIEnv*, jobject) {
  app.OnPause();
}

JNIEXPORT void JNICALL
Java_com_spencerfricke_tango_1visual_1aid_TangoJniNative_onDestroy(
    JNIEnv*, jobject) {
  app.OnDestroy();
}

#ifdef __cplusplus
}
#endif