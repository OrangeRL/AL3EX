#include "ParticleManager.h"
using namespace std;

void ParticleManager::CreateParticle(Vector3 beginPos, Vector3 scale)
{
	particles.emplace_back(new Particle);
	particles.back()->Initialize(beginPos, model_);
	particles.back()->SetScale(scale);
}

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
	particles.clear();
}

void ParticleManager::Initialize(Model* model, TextureHandle tex)
{
	model_ = model;
	this->tex = tex;
	for (unique_ptr<Particle>& particle : particles)
	{
		particle->LoadModel(model_);
	}
}

void ParticleManager::Update(Vector3 beginPos, Vector3 scale)
{
	particles.remove_if([](std::unique_ptr<Particle>& particle) {
		return particle->IsDead();
		});

	if (particles.size() <= LIMIT)
	{
		CreateParticle(beginPos, scale);
	}

	for (unique_ptr<Particle>& particle : particles)
	{
		particle->Update();
	}
}

void ParticleManager::Draw(ViewProjection view)
{
	for (unique_ptr<Particle>& particle : particles)
	{
		particle->Draw(view, tex);
	}
}
