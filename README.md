# Engine room sensesp device for S/V Symphony
This is for the aft-ward sensesp unit installed in S/V Symphony, part of Dark Star LLC's fleet.

It has these proposed measurement responsibilities:
* [electrical.alternators.0.voltage](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexpelectricalalternatorsregexpvoltage)
* [electrical.alternators.0.current](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexpelectricalalternatorsregexpcurrent) (via INA219 and an original brass shunt) 
* [electrical.alternators.0.temperature](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexpelectricalalternatorsregexptemperature) (via DS18B20 "1-Wire" probe)
* [propulsion.0.state](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexpstate)
* 
* [propulsion.0.revolutions](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexprevolutions) (Engine Hz/RPM - via original sensor?)
* [propulsion.0.temperature](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexptemperature)
* [propulsion.0.oilTemperature](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexpoiltemperature)
* [propulsion.0.oilPressure](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexpoilpressure)
* [propulsion.0.runTime](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexpruntime)
* [propulsion.0.coolantTemperature](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexpcoolanttemperature)
* [propulsion.0.coolantPressure](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexpcoolantpressure)
* [propulsion.0.intakeManifoldTemperature](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexpintakemanifoldtemperature)
* [propulsion.0.exhaustTemperature](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexppropulsionregexpexhausttemperature)
* [electrical.batteries.0.voltage](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexpelectricalbatteriesregexpvoltage)
* [electrical.batteries.0.current](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexpelectricalbatteriesregexpcurrent)
* [electrical.batteries.0.temperature](https://signalk.org/specification/1.7.0/doc/vesselsBranch.html#vesselsregexpelectricalbatteriesregexptemperature)


# SensESP

This project was generated using the template for [SensESP](https://github.com/SignalK/SensESP/) projects.

Comprehensive documentation for SensESP, including how to get started with your own project, is available at the [SensESP documentation site](https://signalk.org/SensESP/).

These examples are relevant for the engine room device:
* https://github.com/SignalK/SensESP/blob/main/examples/time_counter.cpp
* https://github.com/SignalK/SensESP/blob/main/examples/pcnt_rpm_counter.cpp
* https://github.com/SignalK/SensESP/blob/main/examples/rpm_counter.cpp
* https://github.com/SignalK/SensESP/blob/main/examples/temperature_sender.cpp
* https://github.com/SignalK/SensESP/blob/main/examples/repeat_sensor_analog_input.cpp
