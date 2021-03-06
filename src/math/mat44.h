#pragma once

#include "math/dll.h"
#include "math/vec2.h"
#include "math/vec3.h"
#include "math/vec4.h"

namespace Math
{
	/**
	 * 4x4 Matrix.
	 */
	class MATH_DLL Mat44 final
	{
	private:
		Vec4 Row0_;
		Vec4 Row1_;
		Vec4 Row2_;
		Vec4 Row3_;

	public:
		Mat44() { Identity(); }
		Mat44(const f32* pData);
		Mat44(const Vec4&, const Vec4&, const Vec4&, const Vec4&);

		Mat44(f32 I00, f32 I01, f32 I02, f32 I03, f32 I10, f32 I11, f32 I12, f32 I13, f32 I20, f32 I21, f32 I22,
		    f32 I23, f32 I30, f32 I31, f32 I32, f32 I33);

		// Accessor
		f32* operator[](u32 i) { return reinterpret_cast<f32*>(&Row0_) + (i * 4); }
		const f32* operator[](u32 i) const { return reinterpret_cast<const f32*>(&Row0_) + (i * 4); }

		const Vec4& Row0() const { return Row0_; }
		const Vec4& Row1() const { return Row1_; }
		const Vec4& Row2() const { return Row2_; }
		const Vec4& Row3() const { return Row3_; }

		void Row0(const Vec4& Row0) { Row0_ = Row0; }
		void Row1(const Vec4& Row1) { Row1_ = Row1; }
		void Row2(const Vec4& Row2) { Row2_ = Row2; }
		void Row3(const Vec4& Row3) { Row3_ = Row3; }

		Vec4 Col0() const { return Vec4(Row0_.x, Row1_.x, Row2_.x, Row3_.x); }
		Vec4 Col1() const { return Vec4(Row0_.y, Row1_.y, Row2_.y, Row3_.y); }
		Vec4 Col2() const { return Vec4(Row0_.z, Row1_.z, Row2_.z, Row3_.z); }
		Vec4 Col3() const { return Vec4(Row0_.w, Row1_.w, Row2_.w, Row3_.w); }

		void Col0(const Vec4& Col);
		void Col1(const Vec4& Col);
		void Col2(const Vec4& Col);
		void Col3(const Vec4& Col);

		// Arithmetic
		Mat44 operator+(const Mat44& rhs);
		Mat44 operator-(const Mat44& rhs);
		Mat44 operator*(f32 rhs);
		Mat44 operator/(f32 rhs);
		Mat44 operator*(const Mat44& rhs) const;

		void Identity();
		Mat44 Transposed() const { return Mat44(Col0(), Col1(), Col2(), Col3()); }
		void Transpose() { (*this) = Transposed(); }

		void Rotation(const Vec3&);

		void Translation(const Vec3& Translation) { Row3(Vec4(Translation, 1.0f)); }
		void Translation(const Vec4& Translation) { Row3(Translation); }
		Vec3 Translation() const { return Vec3(Row3_.x, Row3_.y, Row3_.z); }

		void Scale(const Vec3& scale) { Scale(Vec4(scale.x, scale.y, scale.z, 1.0f)); }
		void Scale(const Vec4&);

		f32 Determinant();
		void Inverse();

		void LookAt(const Vec3& Position, const Vec3& LookAt, const Vec3& UpVec);
		void OrthoProjection(f32 Left, f32 Right, f32 Bottom, f32 Top, f32 Near, f32 Far);
		void PerspProjectionHorizontal(f32 Fov, f32 Aspect, f32 Near, f32 Far);
		void PerspProjectionVertical(f32 Fov, f32 Aspect, f32 Near, f32 Far);
		void Frustum(f32 Left, f32 Right, f32 Bottom, f32 Top, f32 Near, f32 Far);

		bool operator==(const Mat44& Other) const;

		bool IsIdentity() const;
	};

	inline Mat44::Mat44(const f32* pData)
	{
		Row0_ = Vec4(pData[0], pData[1], pData[2], pData[3]);
		Row1_ = Vec4(pData[4], pData[5], pData[6], pData[7]);
		Row2_ = Vec4(pData[8], pData[9], pData[10], pData[11]);
		Row3_ = Vec4(pData[12], pData[13], pData[14], pData[15]);
	}

	inline Mat44::Mat44(const Vec4& Row0, const Vec4& Row1, const Vec4& Row2, const Vec4& Row3)
	{
		Row0_ = Row0;
		Row1_ = Row1;
		Row2_ = Row2;
		Row3_ = Row3;
	}

	inline Mat44::Mat44(f32 I00, f32 I01, f32 I02, f32 I03, f32 I10, f32 I11, f32 I12, f32 I13, f32 I20, f32 I21,
	    f32 I22, f32 I23, f32 I30, f32 I31, f32 I32, f32 I33)
	{
		Row0_ = Vec4(I00, I01, I02, I03);
		Row1_ = Vec4(I10, I11, I12, I13);
		Row2_ = Vec4(I20, I21, I22, I23);
		Row3_ = Vec4(I30, I31, I32, I33);
	}

	inline void Mat44::Col0(const Vec4& Col)
	{
		Row0_.x = Col.x;
		Row1_.x = Col.y;
		Row2_.x = Col.z;
		Row3_.x = Col.w;
	}

	inline void Mat44::Col1(const Vec4& Col)
	{
		Row0_.y = Col.x;
		Row1_.y = Col.y;
		Row2_.y = Col.z;
		Row3_.y = Col.w;
	}

	inline void Mat44::Col2(const Vec4& Col)
	{
		Row0_.z = Col.x;
		Row1_.z = Col.y;
		Row2_.z = Col.z;
		Row3_.z = Col.w;
	}

	inline void Mat44::Col3(const Vec4& Col)
	{
		Row0_.w = Col.x;
		Row1_.w = Col.y;
		Row2_.w = Col.z;
		Row3_.w = Col.w;
	}

	inline void Mat44::Identity()
	{
		Row0_ = Vec4(1.0f, 0.0f, 0.0f, 0.0f);
		Row1_ = Vec4(0.0f, 1.0f, 0.0f, 0.0f);
		Row2_ = Vec4(0.0f, 0.0f, 1.0f, 0.0f);
		Row3_ = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	inline void Mat44::Scale(const Vec4& scale)
	{
		Row0(Vec4(scale.x, 0.0f, 0.0f, 0.0f));
		Row1(Vec4(0.0f, scale.y, 0.0f, 0.0f));
		Row2(Vec4(0.0f, 0.0f, scale.z, 0.0f));
		Row3(Vec4(0.0f, 0.0f, 0.0f, scale.w));
	}

	MATH_DLL Vec2 operator*(const Vec2& Lhs, const Mat44& Rhs);
	MATH_DLL Vec3 operator*(const Vec3& Lhs, const Mat44& Rhs);
	MATH_DLL Vec4 operator*(const Vec4& Lhs, const Mat44& Rhs);
} // namespace Math
