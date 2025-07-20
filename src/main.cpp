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
#include "pin_status.h"
#include "DHTesp.h"
#include "temperature.h"

using namespace sensesp;

DHTesp dht;
const int dhtPin = 23;

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

  makeStatusPageItemsForAnalogInputs({32, 25, 15});
  makeStatusPageItemsForDigitalInputs({32, 33, 25, 15});

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

  pinMode(dhtPin, OUTPUT); // lib sends an initial write and then manages switching between read/write
  dht.setup(dhtPin, DHTesp::DHT22);

  auto tempAndHumiditySensor = new sensesp::RepeatSensor<TempAndHumidity>(20000, []() {
  // Repeat interval is 20s because the underlying sensor read takes about 250ms!
  // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
  // Check if any reads failed; ideally we would exit early to try again instead of inline.
    TempAndHumidity newValues = dht.getTempAndHumidity();
    if (dht.getStatus() != 0) {
      debugE("DHT22 error status: %s", dht.getStatusString());
      newValues = dht.getTempAndHumidity();
    }
    return newValues;
  });

  auto dht22Status = new sensesp::RepeatSensor<String>(5000, []() {
    return dht.getStatusString();
  });

  dht22Status->connect_to(new SKOutputString("sensors.engineRoom.dht22.status", "",
            new SKMetadata("", "Engine Room DHT22 sensor status")));

  auto debugTempAndHumidity = std::make_shared<LambdaTransform<TempAndHumidity, TempAndHumidity>>([](TempAndHumidity input) {
    debugI("Temperature=%f, Humidity=%f, status=%s", input.temperature, input.humidity, dht.getStatusString());
    return input;
  });

  tempAndHumiditySensor->connect_to(debugTempAndHumidity);


  auto temperatureSkOut = new SKOutputFloat("environment.inside.engineRoom.temperature", "",
      new SKMetadata("K", "Engine Room Temperature"));

  auto relativeHumiditySkOut = new SKOutputFloat("environment.inside.engineRoom.relativeHumidity", "",
      new SKMetadata("ratio", "Engine Room Relative Humidity"));

  auto temperatureTransform = std::make_shared<LambdaTransform<TempAndHumidity, float>>([](TempAndHumidity input) {
    return temperature::convertCtoK(input.temperature);
  });

  auto humidityTransform = std::make_shared<LambdaTransform<TempAndHumidity, float>>([](TempAndHumidity input) {
    return input.humidity / 100.0;
  });

  debugTempAndHumidity->connect_to(temperatureTransform)->connect_to(temperatureSkOut);
  debugTempAndHumidity->connect_to(humidityTransform)->connect_to(relativeHumiditySkOut);

  while (true) {
    loop();
  }
}
// ref: https://web.archive.org/web/20160119170853/http://epb.apogee.net/res/refcomf.asp
// possible replacement content and image:
// https://c03.apogee.net/mvc/home/hes/land/el?utilityname=peco&spc=cel&id=1347

// https://www.researchgate.net/publication/259359809_Vehicular_Cabins%27_Thermal_Comfort_Zones_Fanger_and_Berkley_Modeling

void loop() { event_loop()->tick(); }