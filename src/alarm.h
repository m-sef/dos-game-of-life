#ifndef ALARM_H
#define ALARM_H

#include <stdint.h>
#include <dos.h>

#ifndef ALARMS_CAPACITY
#define ALARMS_CAPACITY 20
#endif

typedef void (*func_ptr)();

typedef struct
{
	func_ptr call;
	uint32_t ticks;
} ALARM;

void update_alarms();

void register_alarm(
	const func_ptr call,
	const uint32_t ticks);

void clear_alarms();

void install_timer_isr();

void restore_old_timer_isr();

#endif
