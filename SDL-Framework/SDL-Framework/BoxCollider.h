#pragma once
#include "Collider.h"

namespace SDLFramework {

	class BoxCollider : public Collider {

	public:

		BoxCollider(vector2 size);
		~BoxCollider();
		vector2 GetFurthestPoint() override;
		vector2 GetVertexPos(int index);

	private:

		static const int MAX_VERTS = 4;
		GameEntity* mVerts[MAX_VERTS];
		void AddVert(int index, vector2 pos);
	};
}