/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nibbler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:51:20 by banthony          #+#    #+#             */
/*   Updated: 2018/04/26 17:51:20 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Nibbler.hpp"

int DEBUG_MODE = false;

Nibbler *Nibbler::_singleton = nullptr;
AGraphics *Nibbler::_aGraphics = nullptr;
void *Nibbler::dl_handle = nullptr;
eScene Nibbler::_currentScene = MENU;
int Nibbler::WINDOW_WIDTH = 1200;
int Nibbler::WINDOW_HEIGHT = 900;

char *Nibbler::pathLibSDL = const_cast<char *>("./libSDL/libgraph.so");
char *Nibbler::pathLibOpenGL = const_cast<char *>("./libOpenGL/libgraph.so");
char *Nibbler::pathLibSFML = const_cast<char *>("./libSFML/libgraph.so");

Nibbler::Nibbler() {
	this->dl_handle = nullptr;
}

Nibbler::Nibbler(Nibbler const &copy) {
	*this = copy;
}

Nibbler::~Nibbler() {

}

Nibbler &Nibbler::operator=(Nibbler const &copy) {
	if (this != &copy) {
		// copy
	}
	return *this;
}

Nibbler *Nibbler::getInstance() {
	if (!Nibbler::_singleton)
		Nibbler::_singleton = new Nibbler();
	return Nibbler::_singleton;
}

// TODO handle the return ERROR of init !!!!!
void Nibbler::initRun() {
	Nibbler::_aGraphics->init(Nibbler::WINDOW_WIDTH, Nibbler::WINDOW_HEIGHT);
	this->_callScene[MENU] = new SceneMenu(this->_aGraphics);
	this->_callScene[SKIN] = new SceneSkin(this->_aGraphics);
	this->_callScene[GAME] = new SceneGame(this->_aGraphics);
	this->_callScene[GAME_END] = new SceneGameEnd(this->_aGraphics);
	this->_aGraphics->loadTexture("./textures/menu_bckg.png", MENU_BCKG);
	this->_aGraphics->loadTexture("./textures/game_bckg.png", GAME_BCKG);
	this->_aGraphics->loadTexture("./textures/border_game.png", GAME_BORDER);
	this->_aGraphics->loadTexture("./textures/score_bckg.png", SCORE_BCKG);
	this->_aGraphics->loadTexture("./textures/skin_border.png", SKIN_FRAME);
	this->_aGraphics->loadTexture("./textures/snake_head_smb.png", SNAKE_H_SMB);
	this->_aGraphics->loadTexture("./textures/snake_body_smb.png", SNAKE_B_SMB);
	this->_aGraphics->loadTexture("./textures/snake_head_pcm.png", SNAKE_H_PCM);
	this->_aGraphics->loadTexture("./textures/snake_body_pcm.png", SNAKE_B_PCM);
	this->_aGraphics->loadTexture("./textures/snake_head_hk.png", SNAKE_H_HK);
	this->_aGraphics->loadTexture("./textures/snake_body_hk.png", SNAKE_B_HK);
	this->_aGraphics->loadTexture("./textures/melon.png", FOOD);
	this->_aGraphics->loadFontTexture("./textures/snake_font.tga");
}

void Nibbler::run() {
	this->initRun();
	std::string key[NB_EVENT] = {"VOID", "ECHAP", "UP", "DOWN", "LEFT", "RIGHT", "ENTER",}; // debug

	while (Nibbler::_aGraphics->loopUpdate()) {
		auto vec = Nibbler::_aGraphics->getEvent();

		this->_callScene[this->_currentScene]->eventHandler(vec);
		this->_callScene[this->_currentScene]->drawScene();

		// ************************************** DEBUG
		for (size_t j = 0; j < vec.size(); j++) {

			std::cout << "size:" << vec.size() << std::endl;
			std::cout << key[vec.at(j)] << std::endl;

			if (vec.at(j) == ECHAP) {
				Nibbler::_aGraphics->closeWindow();
			}
			if (vec.at(j) == UP) {
				std::cout << "UP catch" << std::endl;
			}
		}
		// *************************************** DEBUG

		// draw
		// event
		// update nibbler
	}
	Nibbler::_aGraphics->cleanUp();
}

eScene Nibbler::getCurrentScene() {
	return Nibbler::_currentScene;
}

void Nibbler::setCurrentScene(eScene currentScene) {
	if (currentScene > STATE_VOID && currentScene < NB_STATE)
		Nibbler::_currentScene = currentScene;
}

int Nibbler::getWindowWidth() {
	return Nibbler::WINDOW_WIDTH;
}

void Nibbler::setWindowWidth(int w) {
	if (w < 70) {
		w = 70;
	} else if (w > 2550) {
		w = 2550;
	}
	Nibbler::WINDOW_WIDTH = w;
}

int Nibbler::getWindowHeight() {
	return Nibbler::WINDOW_HEIGHT;
}

void Nibbler::setWindowHeight(int h) {
	if (h < 60) {
		h = 60;
	} else if (h > 1420) {
		h = 1420;
	}
	Nibbler::WINDOW_HEIGHT = h;
}

bool Nibbler::loadLibrary(std::string const string) {
	AGraphics *(*createGraphics)();

	Nibbler::dl_handle = dlopen(string.c_str(), RTLD_LAZY | RTLD_LOCAL);
	if (!Nibbler::dl_handle) {
		if (DEBUG_MODE) {
			std::cerr << "Failed to load library [" << dlerror() << "]" << std::endl;
		} else {
			std::cerr << "Failed to load library [" << string << "]" << std::endl;
		}
		return false;
	}

	// get createGraphics function
	createGraphics = (AGraphics *(*)()) dlsym(Nibbler::dl_handle, "createGraphics");
	if (!createGraphics) {
		if (DEBUG_MODE) {
			std::cerr << "Failed to load library [" << dlerror() << "]" << std::endl;
		} else {
			std::cerr << "Failed to load library [" << string << "]" << std::endl;
		}
		return false;
	}
	Nibbler::_aGraphics = createGraphics();
	return true;
}








