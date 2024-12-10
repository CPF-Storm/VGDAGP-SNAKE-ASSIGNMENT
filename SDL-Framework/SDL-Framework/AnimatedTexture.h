#pragma once
#include "Texture.h"
#include "Timer.h"


namespace SDLFramework {

	class AnimatedTexture : public Texture {
	public:

		enum WrapMode {Once=0, Loop};
		enum AniDir {Horizontal = 0, Vertical};

		AnimatedTexture (std::string filename, int x, int y, int width, int height, int framecount, float animspeed, AniDir animationdir, bool managed = false);
		~AnimatedTexture();

		void setWrapMode(WrapMode mode);

		bool isAnimating();
		virtual void ResetAnimation();

		void Update();

	protected:
		virtual void RunAnimation();

		Timer* mTimer;
		int mStartx;
		int mStarty;

		int mFrameCount;

		float mAnimationSpeed;
		float mTimePerFrame;
		float mAnimationTimer;

	
		WrapMode mWrapMode;
		AniDir mAnimationDirection;

		bool mAnimationDone;
	};

	//
}