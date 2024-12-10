#pragma once

#include <SDL.h>
#include "MathHelper.h"
#include <string>


namespace SDLFramework {

	class InputManager {
	
	public:
		static InputManager* Instance();
		static void Release();

		enum Mousebutton{Left = 0, Right, Middle, Back, Forward};

		bool KeyDown(SDL_Scancode scancode);
		bool KeyPressed(SDL_Scancode scancode);
		bool KeyReleased(SDL_Scancode scancode);


		bool MouseButtonDown(Mousebutton button);
		bool MouseButtonPressed(Mousebutton button);
		bool MouseButtonReleased(Mousebutton button);

		vector2 MousePosition();

		void Update();
		void UpdatePrevInput();

	private:
		static InputManager* sInstance;

		const Uint8* mKeyboardState;
		Uint8* mPrevKeyboardState;
		int mKeyLength;

		Uint32 mPrevMouseState;
		Uint32 mMouseState;

		int mMouseXPos;
		int mMouseYPos;

		InputManager();
		~InputManager();

	};


	

	//namespace
}