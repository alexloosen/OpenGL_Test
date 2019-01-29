#pragma once
#include <glew.h>

class Sprite
{
	public:
	Sprite();
	~Sprite();

	void init(float x, float y, float w, float h);
	void draw();
	
	private:
	int _x;
	int _y;
	int _w;
	int _h;

	GLuint _vboID;
};

