//Matrix3x3
//Created 17/07/17
//Created By Daniel Bowler
//
//3x3 matrix

#pragma once

struct FMatrix3x3
{
private:
	//Private entries - Use the () operator
	//to access components in [row][col]
	float m[3][3];

public:
	//Inits everything to zero
	FMatrix3x3()
	{
		ZeroMemory(this, sizeof(FMatrix3x3));
	};

	//Inits everything along the diagonal to diagonal
	FMatrix3x3(float Diagonal)
	{
		ZeroMemory(this, sizeof(FMatrix3x3));
		m[0][0] = Diagonal;
		m[1][1] = Diagonal;
		m[2][2] = Diagonal;
	};

	//Init each component of the matrix
	FMatrix3x3(float M00, float M01, float M02,
		float M10, float M11, float M12,
		float M20, float M21, float M22)
	{
		m[0][0] = M00; m[0][1] = M10; m[0][2] = M20;
		m[1][0] = M01; m[1][1] = M11; m[1][2] = M21;
		m[2][0] = M02; m[2][1] = M12; m[2][2] = M22;
	};

	//Copies the vector3D data in to each matrix column
	FMatrix3x3(FVector3D Col0, FVector3D Col1, FVector3D Col2)
	{
		m[0][0] = Col0.x; m[0][1] = Col0.y; m[0][2] = Col0.z;
		m[1][0] = Col1.x; m[1][1] = Col1.y; m[1][2] = Col1.z;
		m[2][0] = Col2.x; m[2][1] = Col2.y; m[2][2] = Col2.z;
	};

	FMatrix3x3(FMatrix3x3&  Other)
	{
		memcpy(this, &Other, sizeof(FMatrix3x3));
	}

	FMatrix3x3& operator=(FMatrix3x3& Other)
	{
		memcpy(this, &Other, sizeof(FMatrix3x3));
		return (*this);
	};

	//Accessors for the entires data
	float& operator() (int Row_i, int Col_j)
	{
		return (m[Col_j][Row_i]);
	};

	const float& operator() (int Row_i, int Col_j) const
	{
		return (m[Col_j][Row_i]);
	};

	FVector3D& operator[] (int Col_j)
	{
		return (*reinterpret_cast<FVector3D*>(&m[Col_j]));
	};

	const FVector3D& operator[] (int Col_j) const
	{
		return (*reinterpret_cast<const FVector3D*>(&m[Col_j]));
	};
};