# Engine room sensesp device for S/V Symphony
This is for the aft-ward sensesp unit installed in S/V Symphony, part of Dark Star LLC's fleet.

It has these proposed measurement responsibilities:
* [electrical.alternators.main.voltage](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexpelectricalalternatorsregexpvoltage)
* [electrical.alternators.main.current](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexpelectricalalternatorsregexpcurrent) (via INA219 and an original brass shunt) 
* [electrical.alternators.main.temperature](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexpelectricalalternatorsregexptemperature) (via DS18B20 "1-Wire" probe)
* [propulsion.main.state](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexpstate)
* [propulsion.main.revolutions](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexprevolutions) (Engine Hz/RPM - via original sensor?)
* [propulsion.main.temperature](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexptemperature)
* [propulsion.main.oilTemperature](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexpoiltemperature)
* [propulsion.main.oilPressure](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexpoilpressure)
* [propulsion.main.runTime](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexpruntime)
* [propulsion.main.coolantTemperature](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexpcoolanttemperature)
* [propulsion.main.coolantPressure](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexpcoolantpressure)
* [propulsion.main.intakeManifoldTemperature](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexpintakemanifoldtemperature)
* [propulsion.main.exhaustTemperature](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexpexhausttemperature)
* [electrical.batteries.starter.voltage](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexpelectricalbatteriesregexpvoltage)
* [electrical.batteries.starter.current](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexpelectricalbatteriesregexpcurrent)
* [electrical.batteries.starter.temperature](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexpelectricalbatteriesregexptemperature)
* CO, NO2, or other hazardous gases/particulates in the engine room, using some combination of sensors such as MQ-2, MQ-135, ADS1X15, and BME280.
* The state of the primary bilge pump (via current detection) and a cycle counter
* The high water alarm (via current detection?)
 
# SensESP

This project was generated using the template for [SensESP](https://github.com/SignalK/SensESP/) projects.

Comprehensive documentation for SensESP, including how to get started with your own project, is available at the [SensESP documentation site](https://signalk.org/SensESP/).

These examples are relevant for the engine room device:
* https://github.com/SignalK/SensESP/blob/main/examples/time_counter.cpp
* https://github.com/SignalK/SensESP/blob/main/examples/pcnt_rpm_counter.cpp
* https://github.com/SignalK/SensESP/blob/main/examples/rpm_counter.cpp
* https://github.com/SignalK/SensESP/blob/main/examples/temperature_sender.cpp
* https://github.com/SignalK/SensESP/blob/main/examples/repeat_sensor_analog_input.cpp
