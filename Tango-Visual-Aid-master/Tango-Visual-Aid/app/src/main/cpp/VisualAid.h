#ifndef DEPTH_VIBERATION_VISUAL_AID_H
#define DEPTH_VIBERATION_VISUAL_AID_H

#include <jni.h>

#include "tango_client_api.h"   // NOLINT
#include "tango_support_api.h"  // NOLINT

#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include <string>
#include <vector>

#include "Util.h"
#include "UdpServer.h"


void OnPointCloudAvailableRouter(void*, const TangoPointCloud* point_cloud);

// TangoHandler provides functionality to communicate with the Tango Service.
class VisualAid {
public:
  VisualAid() : tango_config_(nullptr) {}

  VisualAid(const VisualAid& other) = delete;

  VisualAid& operator=(const VisualAid& other) = delete;

  ~VisualAid() {
    if (tango_config_ != nullptr) {
      TangoConfig_free(tango_config_);
      tango_config_ = nullptr;
    }
  }

  // Check if the Tango Core version is compatible with this app.
  // If not, the application will exit.
  //
  // @param env, java environment parameter CheckVersion is being called.
  // @param caller_activity, caller of this function.
  void OnCreate(JNIEnv* env, jobject caller_activity);

  // Called when the Tango service is connect. We set the binder object to Tango
  // Service in this function.
  //
  // @param env, java environment parameter.
  // @param iBinder, the native binder object.
  void OnTangoServiceConnected(JNIEnv* env, jobject iBinder);

  // Disconnect and stop Tango service.
  void OnPause();

  void OnDestroy();

  // Cache the Java VM
  //
  // @JavaVM java_vm: the Java VM is using from the Java layer.
  void SetJavaVM(JavaVM* java_vm) { java_vm_ = java_vm; }

  void NewIp(const char* ipAddr);

  // Tango Service point cloud callback function for depth data.
  // Called when new new point cloud data is available from the Tango Service.
  void OnPointCloudAvailable(const TangoPointCloud* point_cloud);

  void OnPoseAvailable(const TangoPoseData* pose);

private:
  TangoConfig tango_config_;

  TangoErrorType err;

  // Cached Java VM, caller activity object
  JavaVM* java_vm_;
  jobject calling_activity_obj_;
  jmethodID on_demand_method_;

  int callback_delay_count = 0;

  UdpServer m_server;
  bool m_server_ready = false;

  std::string TEMP = "192.168.1.172";

  char* message_buffer;

};
#endif //DEPTH_VIBERATION_VISUAL_AID_H
