#pragma once
#include "Graphics.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "PhysicsManager.h"
#include "PhysEntity.h"

namespace SDLFramework {
	
	class GameManager {
	public:

		static GameManager* Instance();
		static void Release();

		GameManager();
		~GameManager();

		void update();
		void lateUpdate();

		void Render();

		void Run();
	
	
	private:
		const int Frame_Rate = 60;
		static GameManager* sInstance;

		bool mQuit;

		// modules
		Graphics* mGraphics;
		Timer* mTimer;
		AssetManager* mAssetManager;
		InputManager* mInputManager;
		AudioManager* mAudioManager;
		PhysicsManager* mPhysicsManager;
		
		

		PhysEntity* mPhysOne;
		PhysEntity* mPhysTwo;
		PhysEntity* mPhysThree;
		PhysEntity* mPhysFour;

		SDL_Event mEvents;
		
	};

}