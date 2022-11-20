#include "ParticleEmitter.h"

emitter::emitter()
{
	dcommon = DirectXCommon::GetInstance();
}

emitter::~emitter()
{

}

void emitter::init(ParticleManager* particle)
{
	Pmanager = particle;
}


void emitter::add(int life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel, float startScale, float endScale, float rotate, XMFLOAT4 color)
{

	//リストに要素を追加
	Pmanager->particles.emplace_front();

	//追加した要素の参照
	ParticleManager::Particle& p = Pmanager->particles.front();

	//値のセット
	p.position = position;
	p.velocity = velocity;
	p.accel = accel;
	p.numFrame = life;
	p.sScale = startScale;
	p.eScale = endScale;
	p.scale = startScale;
	p.addRotate = rotate;
	p.addColor = color;

}

void emitter::ParticleAdd()
{

	if (std::distance(Pmanager->particles.begin(), Pmanager->particles.end()) >= 1024)
	{
		return;
	}

	for (int i = 0; i < particleNum; i++)
	{

		XMFLOAT3 pos{};

		if (posSplit == minusSplit)
		{
			pos.x = centerPos.x + ((float)rand() / RAND_MAX * addPosWidth.x);
			pos.y = centerPos.y + ((float)rand() / RAND_MAX * addPosWidth.y);
			pos.z = centerPos.z + ((float)rand() / RAND_MAX * addPosWidth.z);
		}

		if (posSplit == centerSplit)
		{
			pos.x = centerPos.x + ((float)rand() / RAND_MAX * addPosWidth.x - addPosWidth.x / 2);
			pos.y = centerPos.y + ((float)rand() / RAND_MAX * addPosWidth.y - addPosWidth.y / 2);
			pos.z = centerPos.z + ((float)rand() / RAND_MAX * addPosWidth.z - addPosWidth.z / 2);
		}

		if (posSplit == plusSplit)
		{
			pos.x = centerPos.x + ((float)rand() / RAND_MAX * addPosWidth.x - addPosWidth.x);
			pos.y = centerPos.y + ((float)rand() / RAND_MAX * addPosWidth.y - addPosWidth.y);
			pos.z = centerPos.z + ((float)rand() / RAND_MAX * addPosWidth.z - addPosWidth.z);
		}

		XMFLOAT3 vel{};

		if (velocitySplit == minusSplit)
		{
			vel.x = ((float)rand() / RAND_MAX * addVelocityWidth.x);
			vel.y = ((float)rand() / RAND_MAX * addVelocityWidth.y);
			vel.z = ((float)rand() / RAND_MAX * addVelocityWidth.z);
		}

		if (velocitySplit == centerSplit)
		{
			vel.x = ((float)rand() / RAND_MAX * addVelocityWidth.x - addVelocityWidth.x / 2);
			vel.y = ((float)rand() / RAND_MAX * addVelocityWidth.y - addVelocityWidth.y / 2);
			vel.z = ((float)rand() / RAND_MAX * addVelocityWidth.z - addVelocityWidth.z / 2);
		}

		if (velocitySplit == plusSplit)
		{
			vel.x = ((float)rand() / RAND_MAX * addVelocityWidth.x - addVelocityWidth.x);
			vel.y = ((float)rand() / RAND_MAX * addVelocityWidth.y - addVelocityWidth.y);
			vel.z = ((float)rand() / RAND_MAX * addVelocityWidth.z - addVelocityWidth.z);
		}

		XMFLOAT3 acc{};

		if (accelSplit == minusSplit)
		{
			acc.x = ((float)rand() / RAND_MAX * addAccelWidth.x);
			acc.y = ((float)rand() / RAND_MAX * addAccelWidth.y);
			acc.z = ((float)rand() / RAND_MAX * addAccelWidth.z);
		}

		if (accelSplit == centerSplit)
		{
			acc.x = ((float)rand() / RAND_MAX * addAccelWidth.x - addAccelWidth.x / 2);
			acc.y = ((float)rand() / RAND_MAX * addAccelWidth.y - addAccelWidth.y / 2);
			acc.z = ((float)rand() / RAND_MAX * addAccelWidth.z - addAccelWidth.z / 2);
		}

		if (accelSplit == plusSplit)
		{
			acc.x = ((float)rand() / RAND_MAX * addAccelWidth.x - addAccelWidth.x);
			acc.y = ((float)rand() / RAND_MAX * addAccelWidth.y - addAccelWidth.y);
			acc.z = ((float)rand() / RAND_MAX * addAccelWidth.z - addAccelWidth.z);
		}

		add(particleLife, pos, vel, acc, startScale, endScale, rotate, color);

	}

}