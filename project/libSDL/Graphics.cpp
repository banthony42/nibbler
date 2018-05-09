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

Graphics &Graphics::operator=(Graphics const &copy) {    //TODO les formes canonique en private ? sinon implementation
	if (this != &copy) {
		// copy
	}
	return *this;
}

int Graphics::init(int windowWidth, int windowHeight) { // TODO ajouter le nom de la fenetre en param
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) ||
		!(this->_win = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED,
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
	if (!_windowTerminated) {
		if (this->_win) {
			SDL_DestroyWindow(this->_win);
		}
		SDL_FreeSurface(this->_img);
//		SDL_FreeSurface(this->_fontTexture); // TODO Fix this segfault
		for (auto it = this->_textureList.begin(); it != this->_textureList.end(); ++it) {
			SDL_FreeSurface(it->second);
		}
		SDL_Quit();
		this->_windowTerminated = true;
	}
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

void Graphics::putCharScreen(char const c, t_coordd pos, t_coordd sizeFont) { // TODO pass this method pure
	if (c < '!' || c > '~')
		return;

	SDL_Rect srcRect = {FONT_START_X(c), FONT_START_Y(c), CHAR_SIZE_X, CHAR_SIZE_Y};
	SDL_Rect dstRect = {static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(sizeFont.x),
						static_cast<int>(sizeFont.y)};
	SDL_BlitScaled(this->_fontTexture, &srcRect, this->_img, &dstRect);
}

void Graphics::putStrScreen(std::string str, int posX, int posY, float size) {
	char const *c_str = str.c_str();
	t_coordd pos{};

	if (!c_str || !str.size() || posX > this->windowWidth || posY > windowHeight || posX < 0 || posY < 0)
		return;
	if (size <= 0)
		size = 1;

	t_coordd sizeFont{};
	sizeFont.x = round((CHAR_SIZE_X / 2.5) * size);
	sizeFont.y = round((CHAR_SIZE_Y / 2.5) * size);

	pos.x = posX;
	pos.y = posY;

	while (*c_str) {
		if (*c_str != ' ') {
			putCharScreen(*c_str, pos, sizeFont);
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

	if (!key) {
		SDL_FillRect(this->_img, NULL, 0x000000);
		return;
	}
	surface = this->_textureList[key]; // TODO check the key value
	SDL_Rect srcRect = {0, 0, surface->w, surface->h};
	SDL_Rect dstRect = {posX, posY, sizeX, sizeY};
	SDL_BlitScaled(surface, &srcRect, this->_img, &dstRect);
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






