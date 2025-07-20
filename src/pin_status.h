#ifndef _PIN_STATUS_H
#define _PIN_STATUS_H


#define _GPIO_UI_GROUP_ANALOG_INPUTS "Analog Inputs"
#define _GPIO_UI_GROUP_DIGITAL_INPUTS "Digital Inputs"

#define _PIN_LOW_CHAR_PTR       "LOW"
#define _PIN_HIGH_CHAR_PTR      "HIGH"
#define _PIN_UNKNOWN_CHAR_PTR   "UNKNOWN"

extern const std::vector<uint8_t> allReadablePins;
extern const std::vector<uint8_t> allAnalogReadablePins;

void makeStatusPageItemsForAnalogInputs(std::vector<uint8_t> pins = allReadablePins);
void makeStatusPageItemsForDigitalInputs(std::vector<uint8_t> pins = allAnalogReadablePins);

#endif // _PIN_STATUS_H