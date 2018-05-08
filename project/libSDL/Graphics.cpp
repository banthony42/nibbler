/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graphics.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 18:11:59 by banthony          #+#    #+#             */
/*   Updated: 2018/05/07 18:11:59 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
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
	SDL_FillRect(this->_img, nullptr, 0x000000);
}

void
Graphics::putCharScreen(char const c, t_coord pos, t_coord sizeText, t_coord sizeFont) { // TODO pass this method pure
	SDL_Surface *surface;

	surface = this->_fontTexture;
	SDL_Rect srcRect = {FONT_START_X(c), FONT_START_Y(c), CHAR_SIZE_X, CHAR_SIZE_Y};
	SDL_Rect dstRect = {(int) pos.x, (int) pos.y, (int) (sizeFont.x), (int) (sizeFont.y)};
	SDL_BlitSurface(surface, &srcRect, this->_img, &dstRect);
}

void Graphics::putStrScreen(std::string str, int posX, int posY, float size) {
	char const *c_str = str.c_str();
	t_coord pos{};
	t_coord sizeText{};

	if (!c_str || !str.size() || posX > this->windowWidth || posY > windowHeight || posX < 0 || posY < 0)
		return;
	if (size <= 0)
		size = 1;

	t_coord sizeFont{};
	sizeFont.x = (CHAR_SIZE_X / 2.5) * size;
	sizeFont.y = (CHAR_SIZE_Y / 2.5) * size;

	pos.x = posX;
	pos.y = posY;

	sizeText.x = this->_fontTexture->w;
	sizeText.y = this->_fontTexture->h;

	while (*c_str) {
		if (*c_str != ' ') {
			putCharScreen(*c_str, pos, sizeText, sizeFont);
		}
		pos.x += sizeFont.x;
		if (*c_str == '\n' || (pos.x + sizeFont.x) >= this->windowWidth) {
			pos.x = 0;
			if ((pos.y + sizeFont.y) < this->windowHeight)
				pos.y += sizeFont.y;
		}
		c_str++;
	}
}

void Graphics::loadTexture(std::string path, int key) {
	SDL_Surface *image = IMG_Load(path.c_str());
	if (image == nullptr) {
		std::cout << "IMG_Load: " << IMG_GetError() << "\n";
		return;
	}
	this->_textureList[key] = image;
}

void Graphics::loadFontTexture(std::string path) {
	SDL_Surface *image = IMG_Load(path.c_str());
	if (image == nullptr) {
		std::cout << "IMG_Load: " << IMG_GetError() << "\n";
		return;
	}
	this->_fontTexture = image;
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






