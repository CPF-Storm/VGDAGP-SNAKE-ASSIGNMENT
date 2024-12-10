#include "BoxCollider.h"

namespace SDLFramework {

	BoxCollider::BoxCollider(vector2 size) : Collider(ColliderType::Box) {
		AddVert(0, vector2(-0.5f * size.x, -0.5f * size.y));
		AddVert(1, vector2(0.5f * size.x, -0.5f * size.y));
		AddVert(2, vector2(-0.5f * size.x, 0.5f * size.y));
		AddVert(3, vector2(0.5f * size.x, 0.5f * size.y));
		if (DEBUG_COLLIDERS) {
			SetDebugTexture(new Texture("BoxCollider.png"));
			mDebugTexture->Scale(size);
		}
	}
	BoxCollider::~BoxCollider() {
		for (auto vert : mVerts) {
			delete vert;
			vert = nullptr;
		}
	}
	vector2 BoxCollider::GetFurthestPoint() {
		vector2 localPos = Position(GameEntity::Local);
		int furthestIndex = 0;
		float dist = (localPos + mVerts[0]->Position(GameEntity::Local)).Magnitude();
		float otherDist = 0.0f;
		for (int i = 0; i < MAX_VERTS; i++) {
			//Calculate the magnitude for EACH vert in our BoxCollider
			otherDist = (localPos + mVerts[i]->Position(GameEntity::Local)).Magnitude();
			if (otherDist > dist) {
				furthestIndex = i;
				dist = otherDist;
			}
		}
		return localPos + mVerts[furthestIndex]->Position(GameEntity::Local);
	}
	vector2 BoxCollider::GetVertexPos(int index) {
		return mVerts[index]->Position();
	}
	void BoxCollider::AddVert(int index, vector2 pos) {
		mVerts[index] = new GameEntity(pos);
		mVerts[index]->Parent(this);
	}
}