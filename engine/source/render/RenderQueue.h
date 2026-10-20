#pragma once
#include <vector>

namespace engine
{
	class Mesh;
	class Material;
	class GraphicsAPI;

	struct RenderCommand
	{
		Mesh* mesh = nullptr;
		Material* material = nullptr;
	};

	class RenderQueue
	{
	public:
		void Sumbmit(const RenderCommand& command);
		void Draw(GraphicsAPI& graphicsAPI);
	private:
		std::vector<RenderCommand> m_commands;
	};
}