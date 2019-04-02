#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <cstddef>

namespace C3Engine
{
	Sprite::Sprite()
	{
		_vboID = 0;
	}


	Sprite::~Sprite()
	{
		if (_vboID != 0)
		{
			glDeleteBuffers(1, &_vboID);
		}
	}

	void Sprite::init(float x, float y, float w, float h, std::string texturePath)
	{
		_x = x;
		_y = y;
		_w = w;
		_h = h;

		_texture = ResourceManager::getTexture(texturePath);

		if (_vboID == 0)
		{
			glGenBuffers(1, &_vboID);
		}

		Vertex vertexData[6];

		// first triangle
		vertexData[0].setPosition(_x + _w, _y + h);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(_x, _y + h);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPosition(_x, _y);
		vertexData[2].setUV(0.0f, 0.0f);

		// second triangle
		vertexData[3].setPosition(_x, _y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(_x + _w, _y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPosition(_x + _w, _y + h);
		vertexData[5].setUV(1.0f, 1.0f);

		for (int i = 0; i < 3; i++)
		{
			vertexData[i].color.r = 0;
			vertexData[i].color.g = 255;
			vertexData[i].color.b = 0;
			vertexData[i].color.a = 255;
		}
		for (int i = 3; i < 6; i++)
		{
			vertexData[i].color.r = 255;
			vertexData[i].color.g = 0;
			vertexData[i].color.b = 0;
			vertexData[i].color.a = 255;
		}

		//vertexData[1].setColor(255, 0, 0, 255);

		//vertexData[4].setColor(0, 0, 255, 255);


		// bind buffer
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		// upload data
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		// unbind buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::draw()
	{

		glBindTexture(GL_TEXTURE_2D, _texture.id);
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		glEnableVertexAttribArray(0);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, _position));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}