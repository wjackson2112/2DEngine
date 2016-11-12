#ifndef FRAME_RATE_LIMITER_HPP
#define FRAME_RATE_LIMITER_HPP

#include <unistd.h>
#include <SDL2/SDL.h>
#include <iostream>

#define SEC_TO_USEC 1000000.0

class FrameRateLimiter
{
	long mPrevFrameTime; //In microseconds
	double mFrameRate; //Number of frames in a second, zero is no limit
public:
	FrameRateLimiter(double frameRate);

	long wait();
};

#endif