#include"GameManager.h"
#include "BoxCollider.h"


namespace SDLFramework {

	GameManager* GameManager::sInstance = nullptr;

	GameManager* GameManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new GameManager();
		}
		return sInstance;
	}

	void GameManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	void GameManager::Run() {
		//main game 
		while (!mQuit) {
			mTimer->Update();
			//event polling loop
			while (SDL_PollEvent(&mEvents))
			{
				switch (mEvents.type) {
				case SDL_QUIT:
					mQuit = true;
					break;
				}
			}

			if (mTimer->DeltaTime() >= 1.0f / Frame_Rate) {
				mTimer->Reset();
				update();
				lateUpdate();
				Render();
			}

		}

	}

	void GameManager::update() {
		mInputManager->Update();

		if (mInputManager->KeyDown(SDL_SCANCODE_W)) {
			mPhysOne->Translate(vector2(0, -40.0f) * mTimer->DeltaTime(), GameEntity::World);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_S)) {
			mPhysOne->Translate(vector2(0, 40.0f) * mTimer->DeltaTime(), GameEntity::World);
		}
		if (mInputManager->KeyDown(SDL_SCANCODE_A)) {
			mPhysOne->Translate(vector2(-40.f, 0) * mTimer->DeltaTime(), GameEntity::World);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_D)) {
			mPhysOne->Translate(vector2(40.0f, 0) * mTimer->DeltaTime(), GameEntity::World);
		}
		
		
	

	}
	void GameManager::lateUpdate() {
		mPhysicsManager->Update();
		mInputManager->UpdatePrevInput();

	}

	void GameManager::Render() {
		mGraphics->ClearBackBuffer();

		

		mPhysOne->Render();
		mPhysTwo->Render();
		mPhysThree->Render();
		mPhysFour->Render();

		

		mGraphics->Render();
	}

	GameManager::GameManager() : mQuit(false){
		mGraphics = Graphics::Instance();

		if (!Graphics::Initialized()) {
			mQuit = true;
		}

		//Init all modules here
		mTimer = Timer::Instance();

		mAssetManager = AssetManager::Instance();
		mInputManager = InputManager::Instance();
		mAudioManager = AudioManager::Instance();
		mPhysicsManager = PhysicsManager::Instance();

		//Create my Physics Layers
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Friendly,
			PhysicsManager::CollisionFlags::Hostile |
			PhysicsManager::CollisionFlags::HostileProjectile);

		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::FriendlyProjectile,
			PhysicsManager::CollisionFlags::Hostile);

		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Hostile,
			PhysicsManager::CollisionFlags::Friendly |
			PhysicsManager::CollisionFlags::FriendlyProjectile);

		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::HostileProjectile,
			PhysicsManager::CollisionFlags::Friendly);


		//Challenge 2 -> Finish setting up the collision layers (FriendlyProjectiles, HostileProjectiles)

		

		mPhysOne = new PhysEntity();
		mPhysOne->Position(vector2(Graphics::SCREEN_WIDTH * 0.3f, Graphics::SCREEN_HEIGHT * 0.5f));
		mPhysOne->AddCollider(new BoxCollider(vector2(20.0f, 20.0f)));
		mPhysOne->mId = mPhysicsManager->RegisterEntity(mPhysOne, PhysicsManager::CollisionLayers::Friendly);

		mPhysTwo = new PhysEntity();
		mPhysTwo->Position(vector2(Graphics::SCREEN_WIDTH * 0.6f, Graphics::SCREEN_HEIGHT * 0.5f));
		mPhysTwo->AddCollider(new BoxCollider(vector2(20.0f, 20.0f)));
		mPhysTwo->mId = mPhysicsManager->RegisterEntity(mPhysTwo, PhysicsManager::CollisionLayers::Hostile);

		mPhysThree = new PhysEntity();
		mPhysThree->Position(vector2(Graphics::SCREEN_WIDTH * 0.3f, Graphics::SCREEN_HEIGHT * 0.25f));
		mPhysThree->AddCollider(new BoxCollider(vector2(20.0f, 20.0f)));
		mPhysThree->mId = mPhysicsManager->RegisterEntity(mPhysThree, PhysicsManager::CollisionLayers::FriendlyProjectile);

		mPhysFour = new PhysEntity();
		mPhysFour->Position(vector2(Graphics::SCREEN_WIDTH * 0.6f, Graphics::SCREEN_HEIGHT * 0.25f));
		mPhysFour->AddCollider(new BoxCollider(vector2(20.0f, 20.0f)));
		mPhysFour->mId = mPhysicsManager->RegisterEntity(mPhysFour, PhysicsManager::CollisionLayers::HostileProjectile);

	}

	GameManager::~GameManager() {

		delete mPhysOne;
		mPhysOne = nullptr;

		delete mPhysTwo;
		mPhysTwo = nullptr;

		delete mPhysThree;
		mPhysThree = nullptr;

		delete mPhysFour;
		mPhysFour = nullptr;

		Graphics::Release();
		mGraphics = nullptr;

		Timer::Release();
		mTimer = nullptr;

		AssetManager::Release();
		mAssetManager = nullptr;

		InputManager::Release();
		mInputManager = nullptr;

		AudioManager::Release();
		mAudioManager = nullptr;

		PhysicsManager::Release();
		mPhysicsManager = nullptr;

		SDL_Quit();
	}

//namespace 
}