#ifndef Plant_Waterer_h
#define Plant_Waterer_h

#include "Arduino.h"

class Plant_Waterer {
public:
  Plant_Waterer(
      byte sensor_pin,
      byte motor_pin,
      byte limit = DEFAULT_DRY_LIMIT
  );
  void set_dryness_limit(byte percent_limit);
  byte get_moisture_level();
  void check_dryness_and_water();
  void set_watering_duration(int duration);
  int get_analog_value();

private:
  // constants
  static const byte DEFAULT_DRY_LIMIT = 30; //% (moisture level below which the pump starts)
  static const int DEFAULT_WATERING_DURATION = 5000; //ms (time to turn on the motor for)
  static const int DEFAULT_CHECK_DELAY = 250; //ms (wait between two consecutive tests)
  int MOISTURE_0 = 4095; //analog value at 0 moisture
  int MOISTURE_100 = 2350; //analog value at 100% moisture (inside water)
  // pins
  byte _sensor_pin;
  byte _motor_pin;
  // internal variables
  byte _dry_limit = DEFAULT_DRY_LIMIT;
  int _watering_duration = DEFAULT_WATERING_DURATION;
  int _check_delay = DEFAULT_CHECK_DELAY;
  unsigned long _motor_start_millis = 0;
  unsigned long _motor_stop_millis = millis();
  unsigned long _moisture_check_millis = 0;
  int _motor_state = LOW;
  // functions
  void _turn_on_motor();
  void _turn_off_motor();
};

#endif