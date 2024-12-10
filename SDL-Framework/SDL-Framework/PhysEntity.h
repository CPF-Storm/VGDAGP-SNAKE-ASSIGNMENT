#pragma once

#include "Collider.h"
#include <vector>
namespace SDLFramework {

	//Base class for any object we want to have colliders
	class PhysEntity : public GameEntity {
	public:

		PhysEntity();
		virtual ~PhysEntity();
		unsigned long GetId();
		bool CheckCollision(PhysEntity* other);
		virtual void Hit(PhysEntity* other) { std::cout << "A collision has happened!" << std::endl; }
		virtual void Render() override;

	protected:

		
		std::vector<Collider*> mColliders;
		Collider* mBroadPhaseCollider;
		virtual bool IgnoreCollisions();

	public:

		unsigned long mId;
		void AddCollider (Collider* collider, vector2 locaPos = vec2_Zero);
	};
}
