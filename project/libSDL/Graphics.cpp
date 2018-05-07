#include "Graphics.hpp"

/*
 * Declaration de la variable static
 * Permet la modification de l'_eventList dans la fonction
 * de callback et donc en dehors de l'instance de la Lib
 */
std::vector<eEvent> AGraphics::_eventList;

Graphics::Graphics() {

}

Graphics::Graphics(Graphics const &copy) {
	*this = copy;
}

Graphics::~Graphics() {

}

Graphics &Graphics::operator=(Graphics const &copy) {
	if (this != &copy) {
		// copy
	}
	return *this;
}

int Graphics::init(int windowWidth, int windowHeight) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) ||
		!(this->_win = SDL_CreateWindow("SDL NIBBLER", SDL_WINDOWPOS_UNDEFINED,
										SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN)) ||
		!(this->_img = SDL_CreateRGBSurface(0, windowWidth, windowHeight, 32, 0, 0, 0, 0))) {
		std::cout << "ERROR : " << SDL_GetError() << std::endl;
		return (-1);
	}
	return (1);
}

int Graphics::loopUpdate() {
	return !SDL_UpdateWindowSurface(this->_win);
}

void Graphics::display() {

}

void Graphics::clear() {

}

void Graphics::putStrScreen(std::string str, int posX, int posY, float size) {

}

void Graphics::loadTexture(std::string path, int key) {

}

void Graphics::putTexture(int key, int posX, int posY, int sizeX, int sizeY) {

}

void Graphics::cleanUp() {

}

void Graphics::closeWindow() {

}

std::vector<eEvent> &Graphics::getEvent() {
	SDL_Event e {};

	AGraphics::clearEvent();
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			AGraphics::addEvent(ECHAP);
		} else if (e.type == SDLK_UP) {
			AGraphics::addEvent(UP);
		} else if (e.type == SDLK_DOWN) {
			AGraphics::addEvent(DOWN);
		} else if (e.type == SDLK_LEFT) {
			AGraphics::addEvent(LEFT);
		} else if (e.type == SDLK_RIGHT) {
			AGraphics::addEvent(RIGHT);
		} else if (e.type == SDLK_RETURN || e.type == SDLK_KP_ENTER) {
			AGraphics::addEvent(ENTER);
		}
	}
	return Graphics::_eventList;
}

unsigned char Graphics::getChar() {
	return 0;
}

Graphics *createGraphics() {
	return new Graphics();
}

void deleteGraphics(Graphics *graphics) {
	delete graphics;
}



















