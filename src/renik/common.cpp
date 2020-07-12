#ifdef RENIK_ENABLE
#include <renik\cpp\common.h>
#include <renik\cpp\math.h>
#pragma warning( push )
#pragma warning(disable:4244)
namespace renik {
	namespace __internal__ {
		//_4var<T>
		template<typename klass, typename T> _4var<klass(T)>::_4var() {
			this->x = NULL;
			this->y = NULL;
			this->z = NULL;
			this->w = NULL;
		}
		template<typename klass, typename T> _4var<klass(T)>::_4var(T v1, T v2, T v3, T v4) {
			this->x = v1;
			this->y = v2;
			this->z = v3;
			this->w = v4;
		}
		template<typename klass, typename T> bool _4var<klass(T)>::operator == (const klass& p) {
			return this->x == p.x && this->y == p.y && this->z == p.z && this->w == p.w;
		}
		template<typename klass, typename T> bool _4var<klass(T)>::operator != (const klass& p) {
			return this->x != p.x || this->y != p.y || this->z != p.z || this->w != p.w;
		}
		template<typename klass, typename T> klass _4var<klass(T)>::operator + (const klass& p) {
			return klass(this->x + p.x, this->y + p.y, this->z + p.z, this->w + p.w);
		}
		template<typename klass, typename T> klass _4var<klass(T)>::operator - (const klass& p) {
			return klass(this->x - p.x, this->y - p.y, this->z - p.z, this->w - p.w);
		}
		template<typename klass, typename T> klass _4var<klass(T)>::operator * (const T& p) {
			return klass(this->x * p, this->y * p, this->z * p, this->w * p);
		}
		template<typename klass, typename T> klass _4var<klass(T)>::operator / (const T& p) {
			return klass(this->x / p, this->y / p, this->z / p, this->w / p);
		}
		template<typename klass, typename T> klass _4var<klass(T)>::operator += (const klass& p) {
			auto k = (klass*)this;
			k->x += p.x; k->y += p.y; k->z += p.z; k->w += p.w;
			return *k;
		}
		template<typename klass, typename T> klass _4var<klass(T)>::operator -= (const klass& p) {
			auto k = (klass*)this;
			k->x -= p.x; k->y -= p.y; k->z -= p.z; k->w -= p.w;
			return *k;
		}
		template<typename klass, typename T> klass _4var<klass(T)>::operator *= (const klass& p) {
			auto k = (klass*)this;
			k->x *= p.x; k->y *= p.y; k->z *= p.z; k->w *= p.w;
			return *k;
		}
		template<typename klass, typename T> klass _4var<klass(T)>::operator /= (const klass& p) {
			auto k = (klass*)this;
			k->x /= p.x; k->y /= p.y; k->z /= p.z; k->w /= p.w;
			return *k;
		}

		//_3var<T>
		template<typename klass, typename T> _3var<klass(T)>::_3var() {
			this->x = NULL;
			this->y = NULL;
			this->z = NULL;
		}
		template<typename klass, typename T> _3var<klass(T)>::_3var(T v1, T v2, T v3) {
			this->x = v1;
			this->y = v2;
			this->z = v3;
		}
		template<typename klass, typename T> bool _3var<klass(T)>::operator == (const klass& p) {
			return this->x == p.x && this->y == p.y && this->z == p.z;
		}
		template<typename klass, typename T> bool _3var<klass(T)>::operator != (const klass& p) {
			return this->x != p.x || this->y != p.y || this->z != p.z;
		}
		template<typename klass, typename T> klass _3var<klass(T)>::operator + (const klass& p) {
			return klass(this->x + p.x, this->y + p.y, this->z + p.z);
		}
		template<typename klass, typename T> klass _3var<klass(T)>::operator - (const klass& p) {
			return klass(this->x - p.x, this->y - p.y, this->z - p.z);
		}
		template<typename klass, typename T> klass _3var<klass(T)>::operator * (const T& p) {
			return klass(this->x * p, this->y * p, this->z * p);
		}
		template<typename klass, typename T> klass _3var<klass(T)>::operator / (const T& p) {
			return klass(this->x / p, this->y / p, this->z / p);
		}
		template<typename klass, typename T> klass _3var<klass(T)>::operator += (const klass& p) {
			auto k = (klass*)this;
			k->x += p.x; k->y += p.y; k->z += p.z;
			return *k;
		}
		template<typename klass, typename T> klass _3var<klass(T)>::operator -= (const klass& p) {
			auto k = (klass*)this;
			k->x -= p.x; k->y -= p.y; k->z -= p.z;
			return *k;
		}
		template<typename klass, typename T> klass _3var<klass(T)>::operator *= (const klass& p) {
			auto k = (klass*)this;
			k->x *= p.x; k->y *= p.y; k->z *= p.z;
			return *k;
		}
		template<typename klass, typename T> klass _3var<klass(T)>::operator /= (const klass& p) {
			auto k = (klass*)this;
			k->x /= p.x; k->y /= p.y; k->z /= p.z;
			return *k;
		}

		//_2var<T>
		template<typename klass, typename T> _2var<klass(T)>::_2var() {
			this->x = NULL;
			this->y = NULL;
		}
		template<typename klass, typename T> _2var<klass(T)>::_2var(T v1, T v2) {
			this->x = v1;
			this->y = v2;
		}
		template<typename klass, typename T> bool _2var<klass(T)>::operator == (const klass& p) {
			return this->x == p.x && this->y == p.y;
		}
		template<typename klass, typename T> bool _2var<klass(T)>::operator != (const klass& p) {
			return this->x != p.x || this->y != p.y;
		}
		template<typename klass, typename T> klass _2var<klass(T)>::operator + (const klass& p) {
			return klass(this->x + p.x, this->y + p.y);
		}
		template<typename klass, typename T> klass _2var<klass(T)>::operator - (const klass& p) {
			return klass(this->x - p.x, this->y - p.y);
		}
		template<typename klass, typename T> klass _2var<klass(T)>::operator * (T p) {
			return klass(this->x * p, this->y * p);
		}
		template<typename klass, typename T> klass _2var<klass(T)>::operator / (T p) {
			return klass(this->x / p, this->y / p);
		}
		template<typename klass, typename T> klass _2var<klass(T)>::operator += (const klass& p) {
			auto k = (klass*)this;
			k->x += p.x; k->y += p.y;
			return *k;
		}
		template<typename klass, typename T> klass _2var<klass(T)>::operator -= (const klass& p) {
			auto k = (klass*)this;
			k->x -= p.x; k->y -= p.y;
			return *k;
		}
		template<typename klass, typename T> klass _2var<klass(T)>::operator *= (const klass& p) {
			auto k = (klass*)this;
			k->x *= p.x; k->y *= p.y;
			return *k;
		}
		template<typename klass, typename T> klass _2var<klass(T)>::operator /= (const klass& p) {
			auto k = (klass*)this;
			k->x /= p.x; k->y /= p.y;
			return *k;
		}
	}

	//Color
	Color32::Color32() {
		this->r = 0;
		this->g = 0;
		this->b = 0;
		this->a = 0;
	}
	Color32::Color32(byte r, byte g, byte b, byte a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	ColorHLSA::ColorHLSA() {
		this->h = 0;
		this->l = 0;
		this->s = 0;
		this->a = 0;
	}
	ColorHLSA::ColorHLSA(float h, float s, float l, float a) {
		this->h = Math::Clamp(h, 0.0f, 1.0f);
		this->s = Math::Clamp(s, 0.0f, 1.0f);
		this->l = Math::Clamp(l, 0.0f, 1.0f);
		this->a = Math::Clamp(a, 0.0f, 1.0f);
	}

	Color::Color() {
		this->r = 0.0f;
		this->g = 0.0f;
		this->b = 0.0f;
		this->a = 0.0f;
	}
	Color::Color(float r, float g, float b, float a) {
		this->r = Math::Clamp(r, 0.0f, 1.0f);
		this->g = Math::Clamp(g, 0.0f, 1.0f);
		this->b = Math::Clamp(b, 0.0f, 1.0f);
		this->a = Math::Clamp(a, 0.0f, 1.0f);
	}
	Color::Color(byte r, byte g, byte b, byte a) {
		this->r = static_cast<float>(r) / 255.0f;
		this->g = static_cast<float>(g) / 255.0f;
		this->b = static_cast<float>(b) / 255.0f;
		this->a = static_cast<float>(a) / 255.0f;
	}

	//Rect
	RectF::RectF() {
		this->x = 0;
		this->y = 0;
		this->width = 0;
		this->height = 0;
	}
	RectF::RectF(float x, float y, float width, float height) {
		this->x = x; this->y = y; this->width = width; this->height = height;
	}
	RectF::RectF(const Vec2<float>& pos, const Vec2<float>& size) {
		this->x = pos.x;
		this->y = pos.y;
		this->width = size.x;
		this->height = size.y;
	}
	SizeF RectF::getSize() {
		return SizeF(width, height);
	}
	Vec2<float> RectF::getPos() {
		return Vec2<float>(x, y);
	}
	void RectF::setSize(const SizeF& value) {
		this->width = value.width; this->height = value.height;
	}
	Vec2<float> RectF::getCenterPos() {
		return Vec2<float>((x + (x + width)) / 2.0f, (y + (y + height)) / 2.0f);
	}

	RectI::RectI() {
		this->x = 0;
		this->y = 0;
		this->width = 0;
		this->height = 0;
	}
	RectI::RectI(int x, int y, int width, int height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
	RectI::RectI(const Vec2<int>& pos, const Vec2<int>& size) {
		this->x = pos.x;
		this->y = pos.y;
		this->width = size.x;
		this->height = size.y;
	}
	SizeI RectI::getSize() {
		return SizeI(width, height);
	}
	Vec2<int> RectI::getPos() {
		return Vec2<int>(x, y);
	}
	void RectI::setSize(const Vec2<int>& value) {
		this->x = value.x; this->y = value.y;
	}
	Vec2<int> RectI::getCenterPos() {
		return Vec2<int>((x + (x + width)) / 2.0f, (y + (y + height)) / 2.0f);
	}
}
#pragma warning( pop )
#endif