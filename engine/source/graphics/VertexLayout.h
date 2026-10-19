#pragma once

#include <GL/glew.h>
#include <vector>
#include <stdint.h>

namespace engine
{
	struct VertexElement
	{
		GLuint index; //Att location
		GLuint size; //Number of components
		GLuint type; //Data type
		uint32_t offset;
	};

	struct VertexLayout
	{
		std::vector<VertexElement> elements;
		uint32_t stride = 0;
	};
}