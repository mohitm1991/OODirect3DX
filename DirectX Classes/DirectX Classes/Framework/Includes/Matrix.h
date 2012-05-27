#ifndef MATRIX_H_
#define MATRIX_H_

#include <D3D11.h>
#include <xnamath.h>

class Matrix
{
	private:
		XMFLOAT4X4 matrix;
		Matrix(const XMFLOAT4X4& matrix);
		Matrix(const XMMATRIX& matrix);
	public:
		Matrix();
		Matrix transpose();
		XMMATRIX getNative();

		static Matrix createIdentity();
		static Matrix createLeftOrthographicOffCenter(float left, float right, float bottom, float top, float minDepth, float maxDepth);
		static Matrix createRotationX(float angle);
		static Matrix createRotationY(float angle);
		static Matrix createRotationZ(float angle);
		static Matrix createScaling(float x, float y, float z);
		static Matrix createTranslation(float x, float y, float z);

		const Matrix operator+(const Matrix& otherMatrix) const;
		const Matrix operator-(const Matrix& otherMatrix) const;
		const Matrix operator*(const Matrix& otherMatrix) const;
		const Matrix operator*(const float scalar) const;
		friend const Matrix operator*(const float scalar, const Matrix& matrix);

		Matrix& operator=(const Matrix& otherMatrix);
		Matrix& operator+=(const Matrix& otherMatrix);
		Matrix& operator-=(const Matrix& otherMatrix);
		Matrix& operator*=(const Matrix& otherMatrix);
		Matrix& operator*=(const float scalar);
};

#endif