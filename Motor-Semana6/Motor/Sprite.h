#pragma once
#include<GL/glew.h>
using namespace std;
class Sprite
{
private:

	float vertexData;
	GLuint sprintID;
public:
	Sprite(float x, float y, float width, float height, GLuint sprintID);
	~Sprite();
	void init();
	void draw();
	void cleanup();
	float x, y;
	float width, height;
};
