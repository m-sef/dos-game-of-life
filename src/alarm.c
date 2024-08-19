#include "alarm.h"

#define TIMER_INTERRUPT 0x1c

ALARM Alarms[ALARMS_CAPACITY];
uint32_t ElapsedTicks;

void (__interrupt __far* old_isr)();

void __interrupt __far Timer()
{
	ElapsedTicks++;
}

void update_alarms()
{
	int i;

	if (ElapsedTicks == 0)
	{
		return;
	}

	ElapsedTicks = 0;

	for (i = 0; i < ALARMS_CAPACITY; i++)
	{
		if (Alarms[i].ticks == 0)
		{
			continue;
		}

		Alarms[i].ticks--;

		if (Alarms[i].ticks == 0)
		{
			(*Alarms[i].call)();
		}
	}
}

void register_alarm(const func_ptr call, const uint32_t ticks)
{
	int i;
	
	for (i = 0; i < ALARMS_CAPACITY; i++)
	{
		if (Alarms[i].ticks != 0)
		{
			continue;
		}

		Alarms[i].call = call;
		Alarms[i].ticks = ticks;

		break;
	}
}

void clear_alarms()
{
	int i;

	for (i = 0; i < ALARMS_CAPACITY; i++)
	{
		Alarms[i].ticks = 0;
	}
}

void install_timer_isr()
{
	old_isr = _dos_getvect(TIMER_INTERRUPT);
	_dos_setvect(TIMER_INTERRUPT, Timer);
}

void restore_old_timer_isr()
{
	_dos_setvect(TIMER_INTERRUPT, old_isr);
}
