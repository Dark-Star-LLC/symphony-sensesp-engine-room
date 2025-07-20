
#include <vector>

#include "sensesp/sensors/digital_input.h"
#include "sensesp/ui/status_page_item.h"
#include "pin_status.h"

static const String _high = String(_PIN_HIGH_CHAR_PTR);
static const String _low = String(_PIN_LOW_CHAR_PTR);

const std::vector<uint8_t> allReadablePins = {
    0, 2, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33, 34, 35, 36, 39
};

const std::vector<uint8_t> allAnalogReadablePins = {
    // why does 33 not work when we have it as digital? is it because of the pullup?
    //2, 4, 12, 13, 14, 15, 25, 26, 27, 32, 33, 34, 35, 36, 39
    2, 4, 12, 13, 14, 15, 25, 26, 27, 32, 34, 35, 36, 39
};

/*std::vector<sensesp::StatusPageItem<String>> makeStatusPageItemsForDigitalInputsAlt(std::vector<sensesp::DigitalInput*> inputs) {
    for (size_t index = 0; index < inputs.size(); ++index) {
        auto input = inputs[index];
        auto foo = input->getPin();
}*/

static const auto statusPageItems = new std::vector<sensesp::StatusPageItem<String>*>();

void makeStatusPageItemsForDigitalInputs(std::vector<uint8_t> pins) {

    int i = 0;
    for (const uint8_t pin : pins) {
        pinMode(pin, INPUT);
        auto name = String("GPIO pin #" + String(pin) + " (digital)");
        auto statusPageItem = new sensesp::StatusPageItem<String>(
            name, _PIN_UNKNOWN_CHAR_PTR, _GPIO_UI_GROUP_DIGITAL_INPUTS, i++);

        auto repeatSensor = new sensesp::RepeatSensor<String>(500, [pin]() {
            return digitalRead(pin) ? _high : _low;
        });

        repeatSensor->connect_to(statusPageItem);
        statusPageItems->push_back(statusPageItem);
        debugI("Configured status page item for digital read on %s", name.c_str());
    }
  }

  void makeStatusPageItemsForAnalogInputs(std::vector<uint8_t> pins) {

    auto statusPageItems = new std::vector<sensesp::StatusPageItem<String>*>();

    int i = 0;
    for (const uint8_t pin : pins) {
        auto name = String("GPIO pin #" + String(pin) + " (analog)");
        auto statusPageItem = new sensesp::StatusPageItem<String>(
            name, _PIN_UNKNOWN_CHAR_PTR, _GPIO_UI_GROUP_ANALOG_INPUTS, i++);

        auto repeatSensor = new sensesp::RepeatSensor<String>(500, [pin]() {
            auto nominalValue = analogRead(pin);
            auto milliVolts = analogReadMilliVolts(pin);
            return String(nominalValue) + " / " + String(milliVolts) + "mV";
        });

        repeatSensor->connect_to(statusPageItem);
        statusPageItems->push_back(statusPageItem);
        debugI("Configured status page item for analog read on %s", name.c_str());
    }
  }
