#include "Sprite.h"



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

void Sprite::init(float x, float y, float w, float h)
{
	_x = x;
	_y = y;
	_w = w;
	_h = h;

	if (_vboID == 0)
	{
		glGenBuffers(1, &_vboID);
	}

	float vertexData[12];
	// first triangle
	vertexData[0] = _x + _w;
	vertexData[1] = _y + _h;

	vertexData[2] = _x;
	vertexData[3] = _y + _h;

	vertexData[4] = _x;
	vertexData[5] = _y;

	// second triangle
	vertexData[6] = _x;
	vertexData[7] = _y;

	vertexData[8] = _x + _w;
	vertexData[9] = _y;

	vertexData[10] = _x + _w;
	vertexData[11] = _y + _h;

	// bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	// upload data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	// unbind buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
