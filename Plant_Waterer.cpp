#include "Plant_Waterer.h";

Plant_Waterer::Plant_Waterer(byte sensor_pin, byte motor_pin, byte limit) {
    _sensor_pin = sensor_pin;
    _motor_pin = motor_pin;
    _dry_limit = limit;

    pinMode(_sensor_pin, INPUT);
    pinMode(_motor_pin, OUTPUT);

    digitalWrite(_motor_pin, LOW);
}

void Plant_Waterer::set_dryness_limit(byte percent_limit) {
    _dry_limit = percent_limit;
}
byte Plant_Waterer::get_moisture_level() {
    int sensorvalue = analogRead(_sensor_pin),
        sensorRange = MOISTURE_0 - MOISTURE_100,
        sensorIncrease = MOISTURE_0 - sensorvalue,
        percent_moisture = sensorIncrease * 100 / sensorRange;

    byte result;
    if (percent_moisture < 0)
        result = 0;
    else if (percent_moisture > 100)
        result = 100;
    else
        result = percent_moisture;
    
    return result;
}
int Plant_Waterer::get_analog_value() {
    return analogRead(_sensor_pin);
}
// TODO: add option for motor duration
// TODO: add waiting time before checking dryness
void Plant_Waterer::check_dryness_and_water() {
    if (millis() - _moisture_check_millis > _check_delay) {
        _moisture_check_millis = millis();
        byte moisture_level = get_moisture_level();

        if (moisture_level < _dry_limit) _turn_on_motor();
        else _turn_off_motor();
    }
}
void Plant_Waterer::_turn_on_motor() {
    _motor_state = LOW;
    _motor_start_millis = millis();
    digitalWrite(_motor_pin, _motor_state);
}
void Plant_Waterer::_turn_off_motor() {
    _motor_state = HIGH;
    _motor_stop_millis = millis();
    digitalWrite(_motor_pin, _motor_state);
}
void Plant_Waterer::set_watering_duration(int duration) {
    _watering_duration = duration;
}