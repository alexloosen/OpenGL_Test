#pragma once
#include <glew.h>
#include <string>
#include "GLTexture.h"

class Sprite
{
	public:
	Sprite();
	~Sprite();

	void init(float x, float y, float w, float h, std::string texturePath);
	void draw();
	
	private:
	int _x;
	int _y;
	int _w;
	int _h;

	GLuint _vboID;

	GLTexture _texture;
};

