#include "VirtualCamera.h"

FVirtualCamera::FVirtualCamera()
{
	//Init position and the right, up, look vectors. 
	Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	Look = XMFLOAT3(0.0f, 0.0f, -1.0f);

	//Init projection matrix. 
	NearZ = 1.0f;
	FarZ = 1000.0f;
	Aspect = 1.0f;
	FovYRads = 0.25f* DirectX::XM_PI;
	InitCameraPerspectiveProjectionProperties(FovYRads, Aspect, NearZ, FarZ);
}

void FVirtualCamera::InitCameraViewProperties(const XMFLOAT3& CameraPosition, const XMFLOAT3& CameraTarget, const XMFLOAT3& WorldUp)
{
	XMVECTOR Pos = XMLoadFloat3(&CameraPosition);
	XMVECTOR Target =XMLoadFloat3(&CameraTarget);
	XMVECTOR WorldUpV = XMLoadFloat3(&Up);

	XMVECTOR L = XMVector3Normalize(XMVectorSubtract(Target, Pos));
	XMVECTOR R = XMVector3Normalize(XMVector3Cross(WorldUpV, L));
	XMVECTOR U = XMVector3Cross(L, R);

	XMStoreFloat3(&Position, Pos);
	XMStoreFloat3(&Look, L);
	XMStoreFloat3(&Right, R);
	XMStoreFloat3(&Up, U);
}

void FVirtualCamera::InitCameraPerspectiveProjectionProperties(float FovYDegrees, float Aspect, float NearZ, float FarZ)
{
	XMStoreFloat4x4(&Proj, DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(FovYDegrees), Aspect, NearZ, FarZ));

	//Cache data
	this->FovYRads = DirectX::XMConvertToRadians(FovYDegrees);
	this->Aspect = Aspect;
	this->NearZ = NearZ;
	this->FarZ = FarZ;

	bIsPerspectiveMatrix = true;
}

void FVirtualCamera::Strafe(float Distance)
{
	XMVECTOR S = XMVectorReplicate(Distance);
	XMVECTOR R = XMLoadFloat3(&Right);
	XMVECTOR P = XMLoadFloat3(&Position);

	XMStoreFloat3(&Position, XMVectorMultiplyAdd(S, R, P));
}

void FVirtualCamera::Walk(float Distance)
{
	XMVECTOR S = XMVectorReplicate(Distance);
	XMVECTOR L = XMLoadFloat3(&Look);
	XMVECTOR P = XMLoadFloat3(&Position);

	XMStoreFloat3(&Position, XMVectorMultiplyAdd(S, L, P));
}

void FVirtualCamera::AddPitch(float AngleXDegrees)
{
	//Rotate up and look vector about the right vector.
	XMMATRIX R = XMMatrixRotationAxis(XMLoadFloat3(&Right), XMConvertToRadians(AngleXDegrees));

	XMStoreFloat3(&Up, XMVector3TransformNormal(XMLoadFloat3(&Up), R));
	XMStoreFloat3(&Look, XMVector3TransformNormal(XMLoadFloat3(&Look), R));
}

void FVirtualCamera::AddYaw(float AngleYDegrees)
{
	//Rotate the basis vector about the world axis (y)
	XMMATRIX R = XMMatrixRotationY(XMConvertToRadians(AngleYDegrees));

	XMStoreFloat3(&Right, XMVector3TransformNormal(XMLoadFloat3(&Right), R));
	XMStoreFloat3(&Up, XMVector3TransformNormal(XMLoadFloat3(&Up), R));
	XMStoreFloat3(&Look, XMVector3TransformNormal(XMLoadFloat3(&Look), R));
}

void FVirtualCamera::RebuildView()
{
	XMVECTOR R = XMLoadFloat3(&Right);
	XMVECTOR U = XMLoadFloat3(&Up);
	XMVECTOR L = XMLoadFloat3(&Look);
	XMVECTOR P = XMLoadFloat3(&Position);

	//Keep cameras axis orthogonal to each other and normalized
	L = XMVector3Normalize(L);
	U = XMVector3Normalize(XMVector3Cross(L, R));

	//update right vector - return will already be normalized because u and l
	//have been above.
	R = XMVector3Cross(U, L);

	//Fill in view matrix entries.
	float X = -XMVectorGetX(XMVector3Dot(P, R));
	float Y = -XMVectorGetX(XMVector3Dot(P, U));
	float Z = -XMVectorGetX(XMVector3Dot(P, L));

	XMStoreFloat3(&Right, R);
	XMStoreFloat3(&Up, U);
	XMStoreFloat3(&Look, L);

	View(0, 0) = Right.x;
	View(1, 0) = Right.y;
	View(2, 0) = Right.z;
	View(3, 0) = X;

	View(0, 1) = Up.x;
	View(1, 1) = Up.y;
	View(2, 1) = Up.z;
	View(3, 1) = Y;

	View(0, 2) = Look.x;
	View(1, 2) = Look.y;
	View(2, 2) = Look.z;
	View(3, 2) = Z;

	View(0, 3) = 0.0f;
	View(1, 3) = 0.0f;
	View(2, 3) = 0.0f;
	View(3, 3) = 1.0f;
}

XMMATRIX FVirtualCamera::CalculateInverseViewMatrix()
{
	XMMATRIX ViewXM = XMLoadFloat4x4(&View);

	XMVECTOR Det = XMMatrixDeterminant(ViewXM);
	XMMATRIX InvView = XMMatrixInverse(&Det, ViewXM);

	return InvView;
}