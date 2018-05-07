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
										SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN))) {
		std::cout << "ERROR : " << SDL_GetError() << std::endl;
		return (-1);
	}
	this->_img = SDL_GetWindowSurface(this->_win);
	this->_windowTerminated = false;
	return (1);
}

void Graphics::cleanUp() {
	if (this->_win) {
		SDL_DestroyWindow(this->_win);
	}
	SDL_Quit();
	this->_windowTerminated = true;
}

int Graphics::loopUpdate() {
	return !this->_windowTerminated;
}

void Graphics::display() {
	SDL_UpdateWindowSurface(this->_win);
}

void Graphics::clear() {

}

void Graphics::putStrScreen(std::string str, int posX, int posY, float size) {

}

void Graphics::loadTexture(std::string path, int key) {
	SDL_Surface *image = IMG_Load(path.c_str());
	if (image == nullptr) {
		std::cout << "IMG_Load: " << IMG_GetError() << "\n";
		return;
	}
	this->_textureList[key] = image;
}

void Graphics::putTexture(int key, int posX, int posY, int sizeX, int sizeY) {
	SDL_Surface *surface;

	std::cout << "test" << std::endl;
	surface = this->_textureList[key];
	SDL_Rect srcRect = {0, 0, surface->w, surface->h};
	SDL_Rect destRect = {posX, posY, sizeX, sizeY};
	SDL_BlitSurface(surface, &srcRect, this->_img, &destRect);
}

void Graphics::closeWindow() {
	this->cleanUp();
}

std::vector<eEvent> &Graphics::getEvent() {
	SDL_Event e{};
	AGraphics::clearEvent();
	while (SDL_PollEvent(&e) != 0) {
		int keysym = e.key.keysym.sym;
		if (e.type == SDL_QUIT || keysym == SDLK_ESCAPE) {
			AGraphics::addEvent(ECHAP);
		} else if (keysym == SDLK_UP) {
			AGraphics::addEvent(UP);
		} else if (keysym == SDLK_DOWN) {
			AGraphics::addEvent(DOWN);
		} else if (keysym == SDLK_LEFT) {
			AGraphics::addEvent(LEFT);
		} else if (keysym == SDLK_RIGHT) {
			AGraphics::addEvent(RIGHT);
		} else if (keysym == SDLK_RETURN || keysym == SDLK_KP_ENTER) {
			AGraphics::addEvent(ENTER);
		}
	}
	return AGraphics::_eventList;
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



















