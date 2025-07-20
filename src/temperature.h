#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <cmath>

namespace temperature {
  inline float convertKtoC(float degreesK) {
    if (std::isnan(degreesK) || degreesK < 0 ) {
        return NAN;
    }
    return degreesK - 273.15;
  }

  inline float convertKtoF(float degreesK) {
    if (std::isnan(degreesK) || degreesK < 0 ) {
        return NAN;
    }
    return convertKtoC(degreesK) * (9.0 / 5) + 32;
  }

  inline float convertCtoK(float degreesC) {
    if (std::isnan(degreesC) || degreesC < -273.15) {
        return NAN;
    }
    return degreesC + 273.15;
  }
}

#endif /* TEMPERATURE_H */