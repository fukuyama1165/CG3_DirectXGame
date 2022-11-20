#pragma once
#include "ParticleManager.h"
#include "DirectXCommon.h"
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <forward_list>
#include "WinApp.h"
class emitter
{
	// Microsoft::WRL::Çè»ó™
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:

	emitter();
	~emitter();

	void init(ParticleManager* particle);

	void CameraMoveVector(XMFLOAT3 move);

	void add(int life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel, float startScale, float endScale, float rotate, XMFLOAT4 color);

	void ParticleAdd();

	ParticleManager* Pmanager=nullptr;

	XMFLOAT3 centerPos = {0,0,0};
	XMFLOAT3 addPosWidth = { 1,1,1 };
	XMFLOAT3 addVelocityWidth = { 0.1f,0.1f,0.1f };
	XMFLOAT3 addAccelWidth = { 0,0.001f,0 };
	int particleNum = 5;
	int particleLife = 60;
	float startScale = 1.0f;
	float endScale = 0.0f;
	float rotate = 10.0f;
	XMFLOAT4 color = { 0.0f,0.0f,0.0f,0.0f };
	int posSplit = centerSplit;
	int velocitySplit = centerSplit;
	int accelSplit = minusSplit;

private:

	DirectXCommon* dcommon=nullptr;

};

