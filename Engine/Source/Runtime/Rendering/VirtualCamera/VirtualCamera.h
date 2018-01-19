//VirtualCamera.h
//Created 17/07/17
//Created By Daniel Bowler
//
//Super simple virtual camera (Fly camera) - this will be replaced
//later with components && a much better implementation. But for now, 
//a quick camera implementation is required. 
//
//NOTE: LH camera

#pragma once

#include <Core/CoreInclude.h>
#include <Includes/MathIncludes.h>

class FVirtualCamera
{
public:
	FVirtualCamera();
	~FVirtualCamera() {};

	//Set camera view properties at init time (or when the screen resizes in the case
	//of the camera projection properties
	void InitCameraViewProperties(const XMFLOAT3& CameraPosition, const XMFLOAT3& CameraTarget, const XMFLOAT3& WorldUp);
	void InitCameraPerspectiveProjectionProperties(float FovYDegrees, float Aspect, float NearZ, float FarZ);

	//Strafe/Walk the camera a distance.
	void Strafe(float Distance);
	void Walk(float Distance);

	//Rotate the camera (pitch/Yaw)
	void AddPitch(float AngleXDegrees);
	void AddYaw(float AngleYDegrees);

	//Rebuilds the view matrix 
	void RebuildView();

public:
	//Getters
	XMMATRIX GetView() { return XMLoadFloat4x4(&View); };
	XMMATRIX GetProj() { return XMLoadFloat4x4(&Proj); };
	XMMATRIX GetViewProj() { return GetView() * GetProj(); };

	XMFLOAT3 GetPosition() { return Position; };

	//Calculates the inverse view matrix
	XMMATRIX CalculateInverseViewMatrix();

protected:
	//View and projection matricies
	XMFLOAT4X4 View;
	XMFLOAT4X4 Proj;

	//Camera data
	XMFLOAT3 Position;
	XMFLOAT3 Right;
	XMFLOAT3 Up;
	XMFLOAT3 Look;

	//Perspective projection data
	float FovYRads;
	float Aspect;
	float NearZ;
	float FarZ;

	//Is perspective or othogonal projection?
	bool bIsPerspectiveMatrix = false;
};