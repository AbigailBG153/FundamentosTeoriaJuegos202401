#pragma once
#include<GL/glew.h>
#include"GLTexture.h"
#include <string>
using namespace std;
class Sprite
{
private:
	float x, y;
	int width, height;
	float vertexData;
	GLuint vboID;
	GLTexture texture;
	string texturePath;

public:
	Sprite(float x, float y, int width, int height, string texturePath, GLuint vboID);
	~Sprite();
	void init();
	void draw();
	void clean();
	
};
