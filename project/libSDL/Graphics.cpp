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
	this->_windowTerminated = true;
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

int Graphics::init(int windowWidth, int windowHeight, std::string windowName) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) ||
		!(this->_win = SDL_CreateWindow(std::string(windowName + ": SDL").c_str(), SDL_WINDOWPOS_UNDEFINED,
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
		// info : do not free the _img surface, it is destroyed with the _win
		SDL_FreeSurface(this->_fontTexture);
		for (auto it = this->_textureList.begin(); it != this->_textureList.end(); ++it) {
			SDL_FreeSurface(it->second);
		}
		SDL_Quit();
		this->_windowTerminated = true;
	}
}

void Graphics::loadTexture(std::string path, int key) {
	SDL_Surface *image = IMG_Load(path.c_str());
	if (image == nullptr) {
		throw std::runtime_error(std::string("error: Failed to load texture : ") + path);
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

int Graphics::loopUpdate() {
	return !this->_windowTerminated;
}

void Graphics::display() {
	if (this->_windowTerminated) {
		return ;
	}
	SDL_UpdateWindowSurface(this->_win);
}

void Graphics::clear() {
	if (this->_windowTerminated) {
		return ;
	}
	SDL_FillRect(this->_img, nullptr, 0x000000);
}

void Graphics::putCharScreen(char const c, t_coordd pos, t_coordd sizeFont) {
	if (this->_windowTerminated) {
		return ;
	}
	if (c < '!' || c > '~')
		return;

	SDL_Rect srcRect = {FONT_START_X(c), FONT_START_Y(c), CHAR_SIZE_X, CHAR_SIZE_Y};
	SDL_Rect dstRect = {static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(sizeFont.x),
						static_cast<int>(sizeFont.y)};
	SDL_BlitScaled(this->_fontTexture, &srcRect, this->_img, &dstRect);
}

void Graphics::putStrScreen(std::string str, int posX, int posY, float size) {
	if (this->_windowTerminated) {
		return ;
	}
	char const *c_str = str.c_str();
	t_coordd pos = {};

	if (!c_str || !str.size() || posX > this->windowWidth || posY > windowHeight || posX < 0 || posY < 0)
		return;
	if (size <= 0)
		size = 1;

	t_coordd sizeFont{};
	sizeFont.x = round(GET_SIZEFONT_X(size));
	sizeFont.y = round(GET_SIZEFONT_Y(size));

	pos.x = posX;
	pos.y = posY;

	while (*c_str) {
		if (*c_str != ' ') {
			putCharScreen(*c_str, pos, sizeFont);
		}
		pos.x += sizeFont.x;
		if (*c_str == '\n' || (pos.x + sizeFont.x) >= this->windowWidth) {
			pos.x = posX;
			if ((pos.y + sizeFont.y) < this->windowHeight)
				pos.y += sizeFont.y;
		}
		c_str++;
	}
}

void Graphics::putTexture(int key, int posX, int posY, int sizeX, int sizeY) {
	if (this->_windowTerminated) {
		return ;
	}
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
	if (this->_windowTerminated) {
		return AGraphics::_eventList;
	}
	SDL_Event e{};
	AGraphics::clearEvent();
	while (SDL_PollEvent(&e) != 0) {
		int keysym = e.key.keysym.sym;
		bool keyPressed = (e.key.type == SDL_KEYDOWN) && !e.key.repeat;
		if (e.type == SDL_QUIT || (keysym == SDLK_ESCAPE && keyPressed)) {
			AGraphics::addEvent(ECHAP);
		} else if (keysym == SDLK_UP && keyPressed) {
			AGraphics::addEvent(UP);
		} else if (keysym == SDLK_DOWN && keyPressed) {
			AGraphics::addEvent(DOWN);
		} else if (keysym == SDLK_LEFT && keyPressed) {
			AGraphics::addEvent(LEFT);
		} else if (keysym == SDLK_RIGHT && keyPressed) {
			AGraphics::addEvent(RIGHT);
		} else if ((keysym == SDLK_RETURN &&keyPressed) || (keysym == SDLK_KP_ENTER  && keyPressed)) {
			AGraphics::addEvent(ENTER);
		}
	}
	return AGraphics::_eventList;
}

unsigned char Graphics::getChar() {
	if (this->_windowTerminated) {
		return 0;
	}
	return 0;
}


Graphics *createGraphics() {
	return new Graphics();
}

void deleteGraphics(Graphics *graphics) {
	delete graphics;
}






