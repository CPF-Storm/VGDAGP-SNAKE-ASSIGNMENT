#pragma once
#include <SDL.h>

namespace SDLFramework 
{
	class Timer {
	public:
		static Timer* Instance();
		static void Release();

		void Reset();
		float DeltaTime();

		void TimeScale(float timescale);
		float TimeScale();

		void Update();

		Timer();
		~Timer();
			

	private:
		static Timer* sInstance;
		unsigned int mStartTick;
		unsigned int mElapsedTicks;
		float mDeltaTime;
		float mTimeScale;
	};
}