#include <SDL.h>
class Timer
{
private:
	Uint32 time;
	int lastTime = 0;
	int thisTime;
public:
	Timer() = default;
	~Timer() = default;
	bool wait(int msWaitTime)
	{
		if (lastTime == 0) lastTime = SDL_GetTicks();

		thisTime = SDL_GetTicks();

		if (thisTime - lastTime > msWaitTime)
		{
			lastTime = 0;
			return true;
		}
		return false;
	}
};
