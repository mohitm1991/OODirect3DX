#include "Includes\Matrix.h"

Matrix::Matrix()
{
	XMStoreFloat4x4(&matrix, XMMatrixIdentity());
}

Matrix::Matrix(const XMFLOAT4X4& mat) : matrix(mat)
{
}

Matrix::Matrix(const XMMATRIX& mat) : matrix()
{
	XMStoreFloat4x4(&matrix, mat);
}

Matrix Matrix::transpose()
{
	return Matrix(XMMatrixTranspose(XMLoadFloat4x4(&matrix)));
}

XMMATRIX Matrix::getNative()
{
	return XMLoadFloat4x4(&matrix);
}

Matrix Matrix::createIdentity()
{
	return Matrix(XMMatrixIdentity());
}

Matrix Matrix::createLeftOrthographicOffCenter(float left, float right, float bottom, float top, float minDepth, float maxDepth)
{
	return Matrix(XMMatrixOrthographicOffCenterLH(left, right, bottom, top, minDepth, maxDepth));
}

Matrix Matrix::createRotationX(float angle)
{
	return Matrix(XMMatrixRotationX(angle));
}

Matrix Matrix::createRotationY(float angle)
{
	return Matrix(XMMatrixRotationY(angle));
}

Matrix Matrix::createRotationZ(float angle)
{
	return Matrix(XMMatrixRotationZ(angle));
}

Matrix Matrix::createScaling(float x, float y, float z)
{
	return Matrix(XMMatrixScaling(x, y, z));
}

Matrix Matrix::createTranslation(float x, float y, float z)
{
	return Matrix(XMMatrixTranslation(x, y, z));
}

const Matrix Matrix::operator+(const Matrix& otherMatrix) const
{
	XMFLOAT4X4 result;
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			result(i, j) = matrix(i, j) + otherMatrix.matrix(i, j);

	return Matrix(result);
}

const Matrix Matrix::operator-(const Matrix& otherMatrix) const
{
	XMFLOAT4X4 result;
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			result(i, j) = matrix(i, j) - otherMatrix.matrix(i, j);

	return Matrix(result);
}

const Matrix Matrix::operator*(const Matrix& otherMatrix) const
{
	return Matrix(XMLoadFloat4x4(&matrix) * XMLoadFloat4x4(&(otherMatrix.matrix)));
}

const Matrix Matrix::operator*(const float scalar) const
{
	XMFLOAT4X4 result;
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			result(i, j) = matrix(i, j) * scalar;

	return Matrix(result);
}

const Matrix operator*(const float scalar, const Matrix& matrix)
{
	return matrix * scalar;
}

Matrix& Matrix::operator=(const Matrix& other)
{
	matrix = other.matrix;
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	matrix = ((*this) + other).matrix;
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	matrix = ((*this) - other).matrix;
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
	matrix = ((*this) * other).matrix;
	return *this;
}

Matrix& Matrix::operator*=(const float scalar)
{
	matrix = ((*this) * scalar).matrix;
	return *this;
}