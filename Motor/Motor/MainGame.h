#pragma once
#include <SDL/SDL.h>
#include<GL/eglew.h>
#include <iostream>
#include<vector>
#include <cmath>
#include<memory>
#include "Sprite.h"
#include "GLS_Program.h"
#include "Window.h"
using namespace std;

enum class GameState {

	PLAY, EXIT

};

class MainGame {

private:
	

	int width;
	int height;
	Window* window;
	void init();
	void processInput();
	void initShaders();
	GLS_Program program;
	float time = 0;
	int cont = 1;

	vector<Sprite> sprites;
	time_t timer;
	int selected_position;
	GLuint next_vboID;
	
public:
	MainGame();
	~MainGame();
	GameState gameState;
	void run();
	void draw();
	void update();
	
	void addSprite();
	void drawSprite();
	void cleanSprites();
	

};