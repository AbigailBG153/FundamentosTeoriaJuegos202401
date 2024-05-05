/*

#include "Sprite.h"
#include "Vertex.h"
#include<cstddef>
#include <iostream>
using namespace std;

Sprite::Sprite(float x, float y, float width, float height, GLuint sprintID)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->sprintID = sprintID;
	vertexData;
}

Sprite::~Sprite()
{

}

void Sprite::init()
{


	Vertex vertexData[6];

	vertexData[0].setPosition(x + width, y + height);
	vertexData[1].setPosition(x, y + height);
	vertexData[2].setPosition(x, y);
	vertexData[3].setPosition(x, y);
	vertexData[4].setPosition(x + width, y);
	vertexData[5].setPosition(x + width, y + height);

	for (int i = 0; i < 6; i++) {
		vertexData[i].setColor(255, 0, 255, 255);
	}
	vertexData[1].setColor(0, 255, 0, 255);
	vertexData[4].setColor(255, 0, 0, 255);

	glBindBuffer(GL_ARRAY_BUFFER, sprintID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	if (sprintID == 0) {
		std::cerr << "No se encontro." << std::endl;
		return;
	}

	glBindBuffer(GL_ARRAY_BUFFER, sprintID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Sprite::cleanup() {
	if (sprintID != 0) {
		glDeleteBuffers(1, &sprintID);
		sprintID = 0;
	}
}
*/

#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"
#include<cstddef>
#include<iostream>

Sprite::Sprite(float x, float y, int width, int height, string texturePath, GLuint vboID)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->texturePath = texturePath;
	this->texture = ResourceManager::getTexture(texturePath);
}
Sprite::~Sprite()
{
}

void Sprite::init()
{
	
	if (vboID == 0) {
		glGenBuffers(1, &vboID);
	}
	texture = ResourceManager::getTexture(texturePath);

	Vertex vertexData[6];

	vertexData[0].setPosition(x + width, y + height);
	vertexData[1].setPosition(x , y + height);
	vertexData[2].setPosition(x, y );
	vertexData[3].setPosition(x, y );
	vertexData[4].setPosition(x + width, y );
	vertexData[5].setPosition(x + width, y + height);


	for (int i = 0; i < 6; i++)
	{
		//	red green blue alpha
		vertexData[i].setColor(255, 0, 0, 255);
	}
	vertexData[1].setColor(0, 0, 255, 255);
	vertexData[4].setColor(0, 255, 0, 255);


	vertexData[0].setUV(1.0f,1.0f);
	vertexData[1].setUV(0.0f, 1.0f);
	vertexData[2].setUV(0.0f, 0.0f);
	vertexData[3].setUV(0.0f, 0.0f);
	vertexData[4].setUV(1.0f, 0.0f);
	vertexData[5].setUV(1.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertexData),vertexData , GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindTexture(GL_TEXTURE_2D, texture.id);


	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//posicion
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,position));

	//color
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	//uv
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)offsetof(Vertex, uv));

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Sprite::clean() {
	if (vboID != 0) {
		glDeleteBuffers(1, &vboID);
		vboID = 0;
	}
}
