#pragma once
#ifndef RENIK_MATH_CPP_H
#define RENIK_MATH_CPP_H
#include <math.h>
#include <limits>
namespace renik {
	namespace Math {
		//Basic Limit
		inline static int MIN_INT() { return std::numeric_limits<int>().min(); }
		inline static int MAX_INT() { return std::numeric_limits<int>().max(); }
		inline static float MIN_FLOAT() { return std::numeric_limits<float>().min(); }
		inline static float MAX_FLOAT() { return std::numeric_limits<float>().max(); }
		inline static double MIN_DOUBLE() { return std::numeric_limits<double>().min(); }
		inline static double MAX_DOUBLE() { return std::numeric_limits<double>().max(); }

		//Common Math Function
		template<typename T> inline static T Abs(const T& value) {
			if (value < 0)
				return -value;
			return value;
		}
		template<typename T> inline static T Clamp(const T& value, const T& min, const T& max) {
			if (value < min)
				return min;
			else if (value > max)
				return max;
			return value;
		}
		template<typename T> inline static T Lerp(const T& min, const T& max, float t) { return (T)(min + (max - min) * t); }

		inline static float Sin(float v) { return sinf(v); }
		inline static float Cos(float v) { return cosf(v); }
		inline static float Tan(float v) { return tanf(v); }
		inline static float Asin(float v) { return asinf(v); }
		inline static float Acos(float v) { return acosf(v); }
		inline static float Atan(float v) { return atanf(v); }
		inline static float Atan2(float y, float x) { return atan2f(y, x); }
	}
}
#endif // !RENIK_MATH_CPP_H

