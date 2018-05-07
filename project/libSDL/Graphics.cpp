#include "Graphics.hpp"

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
		!(this->_img = SDL_CreateRGBSurface(0, windowWidth, windowHeight, 32, 0, 0, 0, 0)))
	{
		std::cout << "ERROR : " << SDL_GetError() << std::endl;
		return (-1);
	}
	return (1);
}

int Graphics::loopUpdate() {


	return 0;
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
	return this->_eventList;
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
