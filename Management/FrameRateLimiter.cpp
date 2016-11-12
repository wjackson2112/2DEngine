#include "FrameRateLimiter.hpp"

FrameRateLimiter::FrameRateLimiter(double frameRate) : mPrevFrameTime{0}, mFrameRate{frameRate}
{

}

long FrameRateLimiter::wait()
{
	long prevFrameTime, currFrameTime, nextFrameTime;

	if(mPrevFrameTime == 0)
	{
		mPrevFrameTime = (double) SDL_GetPerformanceCounter()/(double) SDL_GetPerformanceFrequency()*SEC_TO_USEC;
	}

	prevFrameTime = mPrevFrameTime;

	//Zero for frame rate represents no limit
	if(mFrameRate != 0)
	{
		nextFrameTime = prevFrameTime + (1.0/mFrameRate)*SEC_TO_USEC;
		currFrameTime = (double) SDL_GetPerformanceCounter()/(double) SDL_GetPerformanceFrequency()*SEC_TO_USEC;

		usleep(nextFrameTime - currFrameTime);
	}

	mPrevFrameTime = (double) SDL_GetPerformanceCounter()/(double) SDL_GetPerformanceFrequency()*SEC_TO_USEC;

	return mPrevFrameTime - prevFrameTime;
}