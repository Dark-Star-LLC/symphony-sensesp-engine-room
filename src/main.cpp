// Signal K application template file.
//
// This application demonstrates core SensESP concepts in a very
// concise manner. You can build and upload the application as is
// and observe the value changes on the serial port monitor.
//
// You can use this source file as a basis for your own projects.
// Remove the parts that are not relevant to you, and add your own code
// for external hardware libraries.

#include <memory>

#include "sensesp.h"
#include "sensesp_app_builder.h"
#include "sensesp/sensors/digital_input.h"
#include "sensesp/signalk/signalk_output.h"
#include "sensesp/transforms/lambda_transform.h"

using namespace sensesp;

// The setup function performs one-time application initialization.
void setup() {
  SetupLogging(ESP_LOG_DEBUG);

  // Construct the global SensESPApp() object
  SensESPAppBuilder builder;
  sensesp_app = (&builder)
    ->set_hostname("symphony-sensesp-engine-room")
    //->set_wifi_client("My WiFi SSID", "my_wifi_password")
    ->set_wifi_access_point("symphony-sensesp-engine-room", "thisisfine")
    ->set_sk_server("Marks-MacBook-Pro.local", 3000)
    ->enable_system_info_sensors("sensors.")
    ->get_app();

  const String hostname = sensesp_app->get_hostname();
  auto ipAddress = MDNS.queryHost(hostname.c_str(), 1000);
  debugI("Hostname: %s, ipAddress=%s", hostname.c_str(), ipAddress.toString().c_str());

  auto infraredFlameSensor = std::make_shared<DigitalInputChange>(
    33, INPUT_PULLUP, CHANGE,
      "/sensors/engineRoom/infraredFlame");

  auto debugTransform = std::make_shared<LambdaTransform<boolean, boolean>>([](boolean input) {
    debugD("digitalInputChange value=%s", input ? "true" : "false");
    return input;
  });

  auto negate = std::make_shared<LambdaTransform<boolean, boolean>>([](boolean input) {
    // LOW means flame detected, HIGH is normal
    return !input;
  });

  auto flameSensorSkOut = new SKOutputBool("sensors.engineRoom.openFlame", "",
      new SKMetadata("", "Engine Room Flame Detection"));

  infraredFlameSensor->connect_to(debugTransform)->connect_to(negate)->connect_to(flameSensorSkOut);

  while (true) {
    loop();
  }
}

void loop() { event_loop()->tick(); }
