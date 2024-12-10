#include "GameEntity.h"

namespace SDLFramework {

	GameEntity::GameEntity(float x, float y) : mPosition(x, y), mRotation(0.0f),
		mScale(vec2_One), mActive(true), mParent(nullptr) {

	}

	GameEntity::GameEntity(const vector2& position) : mPosition(position), mRotation(0.0f),
		mScale(vec2_One), mActive(true), mParent(nullptr) {
	}

	GameEntity::~GameEntity() {
		mParent = nullptr;
	}

	void GameEntity::Position(float x, float y) {
		mPosition = vector2(x, y);
	}

	void GameEntity::Position(const vector2& pos) {
		mPosition = pos;
	}

	vector2 GameEntity::Position(Space space) {
		if (space == Local || mParent == nullptr) {
			return mPosition;
		}

		vector2 parentScale = mParent->Scale(World);
		vector2 rotPosition = RotateVector(mPosition, mParent->Rotation(Local));

		return mParent->Position(World) + vector2(rotPosition.x * parentScale.x, rotPosition.y * parentScale.y);
	}

	void GameEntity::Rotation(float rot) {
		mRotation = rot;

		while (mRotation > 360.0f) {
			mRotation -= 360.0f;
		}

		while (mRotation < 0.0f) {
			mRotation += 360.0f;
		}
	}

	float GameEntity::Rotation(Space space) {
		if (space == Local || mParent == nullptr) {
			return mRotation;
		}

		return mParent->Rotation(World) + mRotation;
	}

	void GameEntity::Scale(vector2 scale) {
		mScale += scale;
	}

	vector2 GameEntity::Scale(Space space) {
		if (space == Local || mParent == nullptr) {
			return mScale;
		}

		vector2 scale = mParent->Scale(World);
		scale.x *= mScale.x;
		scale.y *= mScale.y;

		return scale;
	}

	void GameEntity::Active(bool active) {
		mActive = active;
	}

	bool GameEntity::Active() const {
		return mActive;
	}

	void GameEntity::Parent(GameEntity* parent) {
		
		if (parent == nullptr) {
			mPosition = Position(World);
			mRotation = Rotation(World);
			mScale = Scale(World);
		}
		else {
			if (mParent != nullptr) {
				
				Parent(nullptr);
			}

			

			vector2 parentScale = parent->Scale(World);

			mPosition = RotateVector(Position(World) - parent->Position(World), - parent->Rotation(World));
			mPosition.x /= parentScale.x;
			mPosition.y /= parentScale.y;

			mRotation -= parent->Rotation(World);
			mScale = vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);
		}

		mParent = parent;
	}

	GameEntity* GameEntity::Parent() {
		return mParent;
	}

	void GameEntity :: Translate (vector2 vec, Space space) {
		if (space == World) {
			mPosition += vec;
	}
		else {
			mPosition += RotateVector(vec, Rotation());
		}
	}

	void GameEntity::Rotate(float amount) {
		mRotation += amount;
	}

	


	//
}