#pragma once
#include <math.h>


namespace SDLFramework {

#define PI 3.1415926535
#define Deg_to_Rad PI / 180.0f

	struct vector2
	{
		float x;
		float y;

		vector2(float _x = 0.0f, float _y = 0.0f) : x{ _x }, y{ _y } {

		}

		float Magnitude() {
			return (float)sqrt(x * x + y * y);
		}

		float Magnitudesqr() {
			return x * x + y * y;
		}

		vector2 Normalized() {
			float mag = Magnitude();
				return vector2(x / mag, y / mag);
		}

		vector2 & operator+= (const vector2 & rhs) {
			x += rhs.x;
			y += rhs.y;
			return *this;

		}

		vector2& operator-=(const vector2& rhs) {
			x -= rhs.x;
			y -= rhs.y;
			return *this;

		}

		vector2 operator-() const {
			return vector2(-x, -y);
		}

	};

	inline vector2 operator+ (const vector2& lhs, const vector2& rhs) {
		return vector2(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	inline vector2 operator- (const vector2& lhs, const vector2& rhs) {
		return vector2(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	inline vector2 operator* (const vector2& lhs, float rhs) {
		return vector2(lhs.x * rhs, lhs.y * rhs);
	}

	inline vector2 operator* (float lhs, const vector2& rhs) {
		return vector2(lhs * rhs.x, lhs * rhs.y);
	}

	inline vector2 lerp(const vector2& start, const vector2& end, float time) {
		if (time <= 0.0f) {
			return start;
		}
		if (time >= 1.0f) {
			return end;
		}
		vector2 dir = (end - start).Normalized();
		float mag = (end - start).Magnitude();

		return start + dir * mag * time;
	}

	inline vector2 RotateVector(const vector2& vec, float angle) {
		float radAngle = (float)(angle * Deg_to_Rad);

		return vector2((float)vec.x * cos(radAngle) - vec.y * sin(radAngle), // rotate x
						(float)vec.x * sin(radAngle) + vec.y * cos(radAngle)); // rotate y
	}

	inline float Dot(const vector2& vec1, const vector2& vec2) {
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}

	inline float Clamp(const float& value, const float& min, const float& max) {
		if (value > max) {
			return max;
		}
		if (value < min) {
			return min;
		}

		return value;
	}

	inline float PointToLineDistance(const vector2& lineStart, const vector2& lineEnd, const vector2& point) {

		//a * b / ||b||
		vector2 slope = lineEnd - lineStart;
		float param = Clamp(Dot(point - lineStart, slope) / slope.Magnitudesqr(), 0.0f, 1.0f);
		vector2 nearestPoint = lineStart + slope * param;
		return (point - nearestPoint).Magnitude();

	}

	inline bool PointInPolygon(vector2* verts, int vertCount, const vector2& point) {

		bool retVal = false;
		//Creating 2 local variables
		for (int i = 0, j = vertCount - 1; i < vertCount; j = i++) {
			if ((verts[i].y >= point.y) != (verts[j].y >= point.y)) {
				vector2 vec1 = (verts[i] - verts[j]).Normalized();
				vector2 proj = verts[j] + vec1 * Dot(point - verts[j], vec1);
				if (proj.x > point.x) {
					//Flipping the boolean to its opposite value
					retVal = !retVal;
				}
			}
		}

		return retVal;
	}
	


	const vector2 vec2_Zero = { 0.0f, 0.0f };
	const vector2 vec2_One = { 1.0f, 1.0f };
	const vector2 vec2_Up = { 0.0f, 1.0f };
	const vector2 vec2_Right = { 1.0f, 0.0f };
// stay above
}