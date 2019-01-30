#include "hardware.h"

float FPS;
float render_time_in_ms;

void hardware::render_time(clock_t starting_point, clock_t ending_point)
{
	float ticks_to_render = ending_point - starting_point;
	render_time_in_ms = (ticks_to_render / CLOCKS_PER_SEC) * 1000;
}

void hardware::frames_per_second(clock_t starting_point, clock_t ending_point)
{
	FPS = 0;
	float ticks_per_frame = ending_point - starting_point;
	if(ticks_per_frame > 0)
		FPS = (CLOCKS_PER_SEC / ticks_per_frame);
}

