#pragma once
#include "MathHelper.h"

namespace SDLFramework {

	class GameEntity {
	public:

		enum Space { Local = 0, World };

		GameEntity(float x = 0.0f, float y = 0.0f);
		GameEntity(const vector2& position);
		~GameEntity();

		void Position(float x, float y);
		void Position(const vector2& pos);
		vector2 Position(Space space = World);

		void Rotation(float rot);
		float Rotation(Space space = World);

		void Scale(vector2 scale);
		vector2 Scale(Space space = World);

		void Active(bool active);
		bool Active() const;

		void Parent(GameEntity* parent);
		GameEntity* Parent();

		void Translate(vector2 vec, Space space = Local);
		void Rotate(float amount);

		virtual void Update() {};
		virtual void Render() {};

	private:
		vector2 mPosition;
		float mRotation;
		vector2 mScale;

		bool mActive;
		GameEntity* mParent;
	};
}