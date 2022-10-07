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
  static const byte DEFAULT_DRY_LIMIT = 30;
  static const int DEFAULT_WATERING_DURATION = 30;
  int MOISTURE_0 = 4095;
  int MOISTURE_100 = 2350;
  byte _sensor_pin;
  byte _motor_pin;
  byte _dry_limit = DEFAULT_DRY_LIMIT;
  int _watering_duration = DEFAULT_WATERING_DURATION;
  unsigned long _motor_start_millis = 0;
  unsigned long _moisture_check_millis = 0;
  int _motor_state = LOW;
  void _turn_on_motor(int duration = DEFAULT_WATERING_DURATION);
  void _turn_off_motor();
};

#endif