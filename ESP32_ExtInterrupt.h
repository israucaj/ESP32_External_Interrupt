#ifndef _ESP32_EXTINTERRUPT_h
#define _ESP32_EXTINTERRUPT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class ExternalInterrupt
{
public:
	ExternalInterrupt();
	~ExternalInterrupt();
	void begin(uint8_t pin, uint8_t type);
	bool available();
	bool getState();
	bool getStatePrev();
	bool getEdge();
	ulong getMicros();
protected:
	void IRAM_ATTR handle();
	uint8_t _pin;
	ulong _micros;
	bool _interrupt;
	bool _state;
	bool _state_prev;
	uint8_t _edge;
};

#endif

