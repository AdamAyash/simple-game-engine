#pragma once

#include <eng.h>
#include <memory>

class Game : public engine::Application
{
public:
	bool Init() override;
	void Update(float deltaTime) override;
	void Destroy() override;

private:
	engine::Scene m_scene;
};