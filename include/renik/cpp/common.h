#pragma once
#ifndef RENIK_COMMON_CPP_H
#define RENIK_COMMON_CPP_H
#include <renik\cpp\headers.h>
namespace renik {
	namespace __internal__ {
		template<typename IDType> static IDType __baseObjectMaxId = 0;
		template<typename IDType> static std::vector<IDType> __baseObjectDeletedId = std::vector<IDType>();

		//----TYPES----
		template<typename> struct _4var;
		template<typename> struct _3var;
		template<typename> struct _2var;

		template<typename klass, typename T> struct _4var<klass(T)> {
			union { T x; T r; T h; T top; T topLeft; };
			union { T y; T g; T s; T right; T topRight; };
			union { T z; T b; T l; T bottom; T bottomRight; T width; };
			union { T w; T a; T left; T bottomLeft; T height; };
			_4var();
			_4var(T v1, T v2, T v3, T v4);
			bool operator == (const klass& p);
			bool operator != (const klass& p);
			klass operator + (const klass& p);
			klass operator - (const klass& p);
			klass operator * (const T& p);
			klass operator / (const T& p);
			klass operator += (const klass& p);
			klass operator -= (const klass& p);
			klass operator *= (const klass& p);
			klass operator /= (const klass& p);
			friend klass operator*(const T& num, const klass& p) { return p * num; }
			friend klass operator/(const T& num, const klass& p) { return p / num; }
		};
		template<typename klass, typename T> struct _3var<klass(T)> {
			union { T x; T r; };
			union { T y; T g; };
			union { T z; T b; };
			_3var();
			_3var(T v1, T v2, T v3);

			bool operator == (const klass& p);
			bool operator != (const klass& p);
			klass operator + (const klass& p);
			klass operator - (const klass& p);
			klass operator * (const T& p);
			klass operator / (const T& p);
			klass operator += (const klass& p);
			klass operator -= (const klass& p);
			klass operator *= (const klass& p);
			klass operator /= (const klass& p);
			friend _3var<T> operator*(const T& num, const _3var<T>& p) { return p * num; }
			friend _3var<T> operator/(const T& num, const _3var<T>& p) { return p / num; }
		};
		template<typename klass, typename T> struct _2var<klass(T)> {
			union { T x; T w; T width; };
			union { T y; T h; T height; };
			_2var();
			_2var(T v1, T v2);

			bool operator == (const klass& p);
			bool operator != (const klass& p);

			klass operator + (const klass& p);
			klass operator - (const klass& p);
			klass operator * (T p);
			klass operator / (T p);
			klass operator += (const klass& p);
			klass operator -= (const klass& p);
			klass operator *= (const klass& p);
			klass operator /= (const klass& p);
			friend klass operator*(T num, klass p) { return p * num; }
			friend klass operator/(T num, klass p) { return p / num; }
		};
		template<typename T, int T1, int T2> struct _mat {
		private:
			T* m_vals;
		public:
			_mat() {
				int len = T1 * T2;
				this->m_vals = new T[len];
				ZeroMemory(m_vals, len);
			}
			_mat(T* val) {
				int len = T1 * T2;
				this->m_vals = new T[len];
				CopyMemory(m_vals, val, len);
			}
			~_mat() { delete[] this->m_vals; }

			inline T& operator() (int x, int y) {
				if (x < 0 || x > T1 || y < 0 || y > T2)
					throw;
				return this->m_vals[x + y * T1];
			}
			inline T operator() (int x, int y) const {
				if (x < 0 || x > T1 || y < 0 || y > T2)
					throw;
				return this->m_vals[x + y * T1];
			}
			inline bool operator == (const _mat<T, T1, T2>& p) {
				if (sizeof(this->m_vals) == sizeof(p.m_vals)) {
					auto len = T1 * T2;
					while (len > 0) {
						if (m_vals[len] != p.m_vals[len])
							return false;
						len--;
					}
				}
				return true;
			}
			inline bool operator != (const _mat<T, T1, T2>& p) {
				if (sizeof(this->m_vals) == sizeof(p.m_vals)) {
					auto len = T1 * T2;
					while (len > 0) {
						if (m_vals[len] == p.m_vals[len])
							return false;
						break;
						len--;
					}
				}
				return true;
			}
			inline _mat<T, T1, T2> operator + (const _mat<T, T1, T2>& p) {
				_mat<T, T1, T2> newMat;
				if (sizeof(this->m_vals) == sizeof(p.m_vals)) {
					auto len = T1 * T2;
					while (len > 0) {
						newMat.m_vals[len] = this->m_vals[len] + p.m_vals[len];
						len--;
					}
				}
				return newMat;
			}
			inline _mat<T, T1, T2> operator - (const _mat<T, T1, T2>& p) {
				_mat<T, T1, T2> mat;
				if (sizeof(this->m_vals) == sizeof(p.m_vals)) {
					auto len = T1 * T2;
					while (len > 0) {
						mat.m_vals[len] = this->m_vals[len] - p.m_vals[len];
						len--;
					}
				}
				return mat;
			}
			inline _mat<T, T1, T2> operator * (const T& p) {
				_mat<T, T1, T2> mat;
				auto len = T1 * T2;
				while (len > 0) {
					mat.m_vals[len] = this->m_vals[len] * p;
					len--;
				}
				return mat;
			}
			inline _mat<T, T1, T2> operator / (const T& p) {
				_mat<T, T1, T2> mat;
				auto len = T1 * T2;
				while (len > 0) {
					mat.m_vals[len] = this->m_vals[len] / p;
					len--;
				}
				return mat;
			}
		};
	}
	//----FUNCTION----
	#define RENFUNC(name, retType, ...) retType(*name)(__VA_ARGS__)

	//----BASEOBJECT---
	template<typename IDType, class T> class BaseObject {
	private:
		IDType m_id;
	public:
		BaseObject() {
			auto len = __internal__::__baseObjectDeletedId<IDType>.size();
			if (len > 0) {
				m_id = __internal__::__baseObjectDeletedId<IDType>[0];
				__internal__::__baseObjectDeletedId<IDType>.erase(__internal__::__baseObjectDeletedId<IDType>.begin());
			}
			else {
				__internal__::__baseObjectMaxId<IDType>++;
				m_id = __internal__::__baseObjectMaxId<IDType>;
			}
		}
		~BaseObject() {
			__internal__::__baseObjectDeletedId<IDType>.push_back(m_id);
		}
		IDType get_id() { return m_id; }
		virtual std::string toString() {
			return typeid(T).name();
		}
		virtual size_t hashCode() {
			return typeid(T).hash_code();
		}
		bool operator == (BaseObject<IDType, T>& obj) {
			return this->hashCode() == obj.hashCode();
		}
		bool operator != (BaseObject<IDType, T>& obj) {
			return this->hashCode() != obj.hashCode();
		}
	};

	//----DELEGATE----
	template<typename> struct DelegateFunc;
	template<typename> class Delegate;
	template<typename retType, typename... Args> class DelegateFunc<retType(Args...)> {
	public:
		typedef retType(*func)(Args...);
	private:
		func f;
	public:
		DelegateFunc(func func) { f = func; }
		operator func() const { return f; }

		retType operator()(Args... args) const {
			return (*f)(args...);
		}
	};
	template<typename retType, typename... Args> class Delegate<retType(Args...)> {
	private:
		std::vector<DelegateFunc<retType(Args...)>> m_func;

	public:
		Delegate() { this->m_func = std::vector<DelegateFunc<retType(Args...)>>();}
		bool subscribe(const DelegateFunc<retType(Args...)>& func) {
			this->m_func.push_back(func);
			return true;
		}
		bool unsubscribe(const DelegateFunc<retType(Args...)>& func) {
			size_t len = this->m_func.size();
			for (size_t i = 0; i < len; i++)
			{
				if (m_func[i] == func)
				{
					m_func.erase(m_func.begin() + i);
					return true;
				}
			}
			return false;
		}
		void clear() {
			return this->m_func.clear();
		}
		DelegateFunc<retType(Args...)>* data() {
			return this->m_func.data();
		}
		size_t count() {
			return this->m_func.size();
		}

		retType operator()(Args... args) const {
			size_t len = this->m_func.size();
			if (len == 0)
				return retType();
			if (len == 1)
				return (*m_func[0])(args...);

			for (size_t i = 0; i < len; i++) {
				(*m_func[i])(args...);
			}
		}
		bool operator==(const Delegate<retType(Args...)>& obj) const {
			size_t len1 = this->m_func.size();
			size_t len2 = obj.m_func.size();

			if (len1 == len2) {
				for (size_t i = 0; i < len1; i++)
				{
					bool same = false;
					for (size_t j = 0; j < len1; j++) {
						if (obj.m_func[j] == m_func[i]) {
							same = true;
							break;
						}
					}
					if (!same)
						return false;
				}
				return true;
			}
			return false;
		}
		bool operator!=(const Delegate<retType(Args...)>& obj) const {
			size_t len1 = this->m_func.size();
			size_t len2 = obj.m_func.size();

			if (len1 == len2) {
				for (size_t i = 0; i < len1; i++)
				{
					bool same = false;
					for (size_t j = 0; j < len2; j++)
					{
						if (obj.m_func[j] == m_func[i]) {
							same = true;
							break;
						}
					}
					if (!same)
						return true;
				}
				return false;
			}
			return true;
		}
	};

	//----COLOR---
	struct Color : public __internal__::_4var<Color(float)> {
	public:
		Color();
		Color(float r, float g, float b, float a);
		Color(byte r, byte g, byte b, byte a);
	};
	struct Color32 : public __internal__::_4var<Color32(byte)> {
	public:
		Color32();
		Color32(byte r, byte g, byte b, byte a);
	};
	struct ColorHLSA : public __internal__::_4var<ColorHLSA(float)> {
	public:
		ColorHLSA();
		ColorHLSA(float h, float s, float l, float a);
	};

	//----MATRIX----
	struct Mat2x2 : public __internal__::_mat<float, 2, 2> {
		inline Mat2x2 operator * (const Mat2x2& b) {
			Mat2x2 m = Mat2x2();
			auto a = *this;
			m(0, 0) = a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0);
			m(0, 1) = a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1);

			m(1, 0) = a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0);
			m(1, 1) = a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1);
			return m;
		}
	};
	struct Mat3x3 : public __internal__::_mat<float, 3, 3> {
		inline Mat3x3 operator * (const Mat3x3& b) {
			Mat3x3 m = Mat3x3();
			auto a = *this;
			m(0, 0) = a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0);
			m(0, 1) = a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1);
			m(0, 2) = a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2);

			m(1, 0) = a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0);
			m(1, 1) = a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1);
			m(1, 2) = a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2);

			m(2, 0) = a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0);
			m(2, 1) = a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1);
			m(2, 2) = a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2);
			return m;
		}
	};
	struct Mat4x4 : public __internal__::_mat<float, 4, 4> {
		inline Mat4x4 operator * (const Mat4x4& b) {
			Mat4x4 m = Mat4x4();
			auto a = *this;
			m(0, 0) = a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0);
			m(0, 1) = a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1) + a(0, 3) * b(3, 1);
			m(0, 2) = a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2) + a(0, 3) * b(3, 2);
			m(0, 3) = a(0, 0) * b(0, 3) + a(0, 1) * b(1, 3) + a(0, 2) * b(2, 3) + a(0, 3) * b(3, 3);

			m(1, 0) = a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0) + a(1, 3) * b(3, 0);
			m(1, 1) = a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1) + a(1, 3) * b(3, 1);
			m(1, 2) = a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2) + a(1, 3) * b(3, 2);
			m(1, 3) = a(1, 0) * b(0, 3) + a(1, 1) * b(1, 3) + a(1, 2) * b(2, 3) + a(1, 3) * b(3, 3);

			m(2, 0) = a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0) + a(2, 3) * b(3, 0);
			m(2, 1) = a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1) + a(2, 3) * b(3, 1);
			m(2, 2) = a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2) + a(2, 3) * b(3, 2);
			m(2, 3) = a(2, 0) * b(0, 3) + a(2, 1) * b(1, 3) + a(2, 2) * b(2, 3) + a(2, 3) * b(3, 3);

			m(3, 0) = a(3, 0) * b(0, 0) + a(3, 1) * b(1, 0) + a(3, 2) * b(2, 0) + a(3, 3) * b(3, 0);
			m(3, 1) = a(3, 0) * b(0, 1) + a(3, 1) * b(1, 1) + a(3, 2) * b(2, 1) + a(3, 3) * b(3, 1);
			m(3, 2) = a(3, 0) * b(0, 2) + a(3, 1) * b(1, 2) + a(3, 2) * b(2, 2) + a(3, 3) * b(3, 2);
			m(3, 3) = a(3, 0) * b(0, 3) + a(3, 1) * b(1, 3) + a(3, 2) * b(2, 3) + a(3, 3) * b(3, 3);
			return m;
		}
	};

	//----VECTOR----
	template<typename> struct Vec2;
	template<typename> struct Vec3;
	template<typename> struct Vec4;

	template<typename T> struct Vec3 : public __internal__::_3var<Vec3<T>(T)> {
		Vec3() : __internal__::_3var<Vec3<T>(T)>(NULL, NULL, NULL) {}
		Vec3(T x, T y, T z) : __internal__::_3var<Vec3<T>(T)>(x, y, z) {}

		Vec3(const Vec2<T>& val) : Vec3<T>(val.x, val.y, NULL) {}
		Vec3(const Vec4<T>& val) : Vec3<T>(val.x, val.y, val.z) {}
		Vec3(const Vec3<T>& val) : __internal__::_3var<Vec3<T>(T)>(val) {}

		operator Vec2<T>() { return Vec2<T>(this->x, this->y); }
		operator Vec4<T>() { return Vec4<T>(this->x, this->y, this->z, NULL); }

		Vec3 operator= (const Vec2<T>& v) { this->x = v.x; this->y = v.y; this->z = NULL; return *this; }
		Vec3 operator= (const Vec4<T>& v) { this->x = v.x; this->y = v.y; this->z = this->z; return *this; }
	};
	template<typename T> struct Vec4 : public __internal__::_4var<Vec4<T>(T)> {
		Vec4() : __internal__::_4var<Vec4<T>(T)>(NULL, NULL, NULL, NULL) {}
		Vec4(T x, T y, T z, T w) :__internal__::_4var<Vec4<T>(T)>(x, y, z, w) {}

		Vec4(const Vec3<T>& val) : Vec4(val.x, val.y, val.z, NULL) {}
		Vec4(const Vec2<T>& val) : Vec4(val.x, val.y, NULL, NULL) {}
		Vec4(const Vec4<T>& val) : __internal__::_4var<Vec4<T>(T)>(val) {}

		operator Vec2<T>() { return Vec2<T>(this->x, this->y); }
		operator Vec3<T>() { return Vec3<T>(this->x, this->y, this->z); }

		Vec4<T> operator= (const Vec2<T>& v) { this->x = v.x; this->y = v.y; this->z = NULL; this->w = NULL; return *this; }
		Vec4<T> operator= (const Vec3<T>& v) { this->x = v.x; this->y = v.y; this->z = v.z; this->w = NULL; return *this; }
	};
	template<typename T> struct Vec2 : public __internal__::_2var<Vec2<T>(T)> {
		Vec2() : __internal__::_2var<Vec2<T>(T)>(NULL, NULL) {}
		Vec2(T x, T y) : __internal__::_2var<Vec2<T>(T)>(x, y) {}

		Vec2(const Vec3<T>& val) : Vec2(val.x, val.y) {}
		Vec2(const Vec4<T>& val) : Vec2(val.x, val.y) {}
		Vec2(const Vec2<T>& val) : __internal__::_2var<Vec2<T>(T)>(val) {}

		operator Vec3<T>() { return Vec3<T>(this->x, this->y, NULL); }
		operator Vec4<T>() { return Vec4<T>(this->x, this->y, NULL, NULL); }

		Vec2 operator= (const Vec3<T>& v) { this->x = v.x; this->y = v.y; return *this; }
		Vec2 operator= (const Vec4<T>& v) { this->x = v.x; this->y = v.y; return *this; }
	};

	typedef Vec3<float> Vec3F;
	typedef Vec3<int> Vec3I;
	typedef Vec2<float> Vec2F;
	typedef Vec2<int> Vec2I;
	typedef Vec4<float> Vec4F;
	typedef Vec4<int> Vec4I;

	//----SIZE----
	typedef Vec2<float> SizeF;
	typedef Vec2<int> SizeI;

	//----QUATERNION----
	typedef Vec4<float> Quaternion;

	//----RECT----
	struct RectF :public __internal__::_4var<RectF(float)> {
		RectF();
		RectF(float x, float y, float width, float height);
		RectF(const Vec2<float>& pos, const Vec2<float>& size);

		SizeF getSize();
		Vec2<float> getPos();
		void setSize(const SizeF& value);
		Vec2<float> getCenterPos();
	};
	struct RectI : public __internal__::_4var<RectI(int)> {
		RectI();
		RectI(int x, int y, int width, int height);
		RectI(const Vec2<int>& pos, const Vec2<int>& size);

		SizeI getSize();
		Vec2<int> getPos();
		void setSize(const Vec2<int>& value);
		Vec2<int> getCenterPos();
	};

	//----DATAPACK----
	template<typename T> struct Array {
	public:
		T* ptr = nullptr;
		size_t size = 0U;
		uint stride = 1U;
		uint sizePerElement = sizeof(T);

		Array(T* ptr = nullptr, size_t size = 0U, uint stride = 1U, uint sizePerElement = sizeof(T)) {
			this->ptr = ptr;
			this->size = size;
			this->stride = stride;
			this->sizePerElement = sizePerElement;
		}

		size_t size_Total() {
			return size * stride;
		}
		size_t size_TotalData() {
			return sizePerElement * size_Total();
		}
	};
}
#endif // !RENIK_COMMON_CPP_H
