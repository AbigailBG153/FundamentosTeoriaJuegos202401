#include "MainGame.h"
#include "Sprite.h"

MainGame::MainGame()
{
	window = NULL;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
	time = 0;
	this->nextVboID = 1;
	std::time(&timer);
	selected_position = 0;


}

void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
		return;
	}

	window = SDL_CreateWindow("COLOR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		std::cerr << "Error al crear la ventana: " << SDL_GetError() << std::endl;
		return;
	}
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr) {
		std::cerr << "Error al crear el contexto OpenGL: " << SDL_GetError() << std::endl;
		return;
	}
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		std::cerr << "Error al inicializar GLEW: " << glewGetErrorString(error) << std::endl;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	initShaders();

}

MainGame::~MainGame()
{

}


void MainGame::run()
{
	init();
	update();
}

void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program.use();
	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);
	time += 0.2;
	drawSprite();
	program.unuse();
	SDL_GL_SwapWindow(window);

}

void MainGame::update()
{
	while (gameState != GameState::EXIT) {
		draw();
		clearSprites();
		addSprite();
		processInput();
	}
}

void MainGame::addSprite()
{
	// Genera coordenadas aleatorias en el rango de 0 a -1
	float x = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2.0f)) - 1.0f; 
	float y = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2.0f)) - 1.0f;
	float w = 0.1f;
	float h = 0.1f; 
	Sprite sprite(x, y, w, h, this->nextVboID);
	sprite.init();
	sprites.push_back(sprite);
	this->nextVboID++;

	SDL_Delay(500);
}
void MainGame::drawSprite()
{
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i].draw();
	}

}

void MainGame::clearSprites()
{
	
	if (sprites.size() > 10) {
		sprites.clear();
		nextVboID = 1;
	}
}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			/*cout << " Posicion en X " << event.motion.x
				<< " Posicion en Y " << event.motion.y << endl;*/
			break;
		}
	}
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPosition");
	program.addAtribute("vertexColor");
	program.linkShader();

}