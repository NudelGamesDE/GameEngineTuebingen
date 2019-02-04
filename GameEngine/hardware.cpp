#include "hardware.h"

int FPS;
float render_time_in_ms;

/**	\brief Determines time to render a scene

\param starting_point starting point of time measuring
\param ending_point ending point of time measuring
*/
void hardware::render_time(clock_t starting_point, clock_t ending_point)
{
	float ticks_to_render = ending_point - starting_point;
	render_time_in_ms = (ticks_to_render / CLOCKS_PER_SEC) * 1000;
}

/**	\brief Determines frames rendered per second

\param starting_point starting point of time measuring
\param ending_point ending point of time measuring
*/
void hardware::frames_per_second(clock_t starting_point, clock_t ending_point)
{
	FPS = 0;
	float ticks_per_frame = ending_point - starting_point;
	if(ticks_per_frame > 0)
		FPS = (CLOCKS_PER_SEC / ticks_per_frame);
}

