#include "CircleCollider.h"

namespace SDLFramework {

	CircleCollider::CircleCollider(float radius, bool broadPhase) : Collider(ColliderType::Circle) {
		mRadius = radius;
		if (DEBUG_COLLIDERS) {
			if (broadPhase) {
				SetDebugTexture(new Texture("BroadPhaseCollider.png"));
			}
			else {
				SetDebugTexture(new Texture("CircleCollider.png"));
			}
			//circle collider file size is 50px
			mDebugTexture->Scale(vec2_One * (radius * 2 / 50.0f));
		}
	}
	CircleCollider::~CircleCollider() {}
	vector2 CircleCollider::GetFurthestPoint() {
		return vec2_Right * (mRadius + Position(GameEntity::Local)).Magnitude();
	}
	float CircleCollider::GetRadius() {
		return mRadius;
	}
}