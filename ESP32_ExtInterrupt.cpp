#include "ESP32_ExtInterrupt.h"
#include <FunctionalInterrupt.h>

ExternalInterrupt::ExternalInterrupt()
{
}

ExternalInterrupt::~ExternalInterrupt()
{
	detachInterrupt(_pin);
}

void ExternalInterrupt::begin(uint8_t pin, uint8_t type)
{
	_pin = pin;
	pinMode(_pin, INPUT_PULLUP);
	attachInterrupt(_pin, std::bind(&ExternalInterrupt::handle, this), type);
}

void IRAM_ATTR ExternalInterrupt::handle()
{
	_interrupt = true;
	_micros = micros() - _micros;
	_state_prev = _state;
	_state = digitalRead(_pin);
	if (_state_prev > _state)
		_edge = FALLING;
	else
		_edge = RISING;
}

bool ExternalInterrupt::available()
{
	bool interrupt = _interrupt;
	_interrupt = false;
	return interrupt;
}

bool ExternalInterrupt::getState()
{
	return _state;
}

bool ExternalInterrupt::getStatePrev()
{
	return _state_prev;
}

bool ExternalInterrupt::getEdge()
{
	return _edge;
}

ulong ExternalInterrupt::getMicros() 
{
	return _micros;
}

