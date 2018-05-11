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
AGraphics *(*Nibbler::_deleteAGraphics)(AGraphics *) = nullptr;

void *Nibbler::_dlHandle = nullptr;
eScene Nibbler::_currentScene = MENU;
int Nibbler::WINDOW_WIDTH = 1200;
int Nibbler::WINDOW_HEIGHT = 900;

Nibbler::Nibbler() {
	this->_dlHandle = nullptr;
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

void Nibbler::initAGraphics() {
	Nibbler::_aGraphics->init(Nibbler::WINDOW_WIDTH, Nibbler::WINDOW_HEIGHT, "Nibbler");
	Nibbler::_aGraphics->loadTexture("./textures/menu_bckg.png", MENU_BCKG);
	Nibbler::_aGraphics->loadTexture("./textures/game_bckg.png", GAME_BCKG);
	Nibbler::_aGraphics->loadTexture("./textures/border_game.png", GAME_BORDER);
	Nibbler::_aGraphics->loadTexture("./textures/score_bckg.png", SCORE_BCKG);
	Nibbler::_aGraphics->loadTexture("./textures/skin_border.png", SKIN_FRAME);
	Nibbler::_aGraphics->loadTexture("./textures/snake_head_smb.png", SNAKE_H_SMB);
	Nibbler::_aGraphics->loadTexture("./textures/snake_body_smb.png", SNAKE_B_SMB);
	Nibbler::_aGraphics->loadTexture("./textures/snake_head_pcm.png", SNAKE_H_PCM);
	Nibbler::_aGraphics->loadTexture("./textures/snake_body_pcm.png", SNAKE_B_PCM);
	Nibbler::_aGraphics->loadTexture("./textures/snake_head_hk.png", SNAKE_H_HK);
	Nibbler::_aGraphics->loadTexture("./textures/snake_body_hk.png", SNAKE_B_HK);
	Nibbler::_aGraphics->loadTexture("./textures/melon.png", FOOD);
	Nibbler::_aGraphics->loadFontTexture("./textures/snake_font.tga");
}


// TODO handle the return ERROR of init !!!!!
void Nibbler::initRun() {
	this->_callScene[MENU] = new SceneMenu(&this->_aGraphics);
	this->_callScene[SKIN] = new SceneSkin(&this->_aGraphics);
	this->_callScene[GAME] = new SceneGame(&this->_aGraphics);
	this->_callScene[GAME_END] = new SceneGameEnd(&this->_aGraphics);
	Nibbler::initAGraphics();
}

void Nibbler::run() {
	this->initRun();
	std::string key[NB_EVENT] = {"VOID", "ECHAP", "UP", "DOWN", "LEFT", "RIGHT", "ENTER",}; // debug

	while (Nibbler::_aGraphics->loopUpdate()) {
		auto vec = Nibbler::_aGraphics->getEvent();

		this->_callScene[this->_currentScene]->eventHandler(vec);
		this->_callScene[this->_currentScene]->drawScene();

		// ************************************** DEBUG
//		for (size_t j = 0; j < vec.size(); j++) {
//
//			std::cout << "size:" << vec.size() << std::endl;
//			std::cout << key[vec.at(j)] << std::endl;
//
//			if (vec.at(j) == ECHAP) {
//				Nibbler::_aGraphics->cleanUp();
//			}
//			if (vec.at(j) == UP) {
//				std::cout << "UP catch" << std::endl;
//			}
//		}
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
	bool toReload = false;
	void *dlHandle = nullptr;
	AGraphics *(*createGraphics)();
	AGraphics *(*deleteGraphics)(AGraphics *);

	dlHandle = dlopen(string.c_str(), RTLD_LAZY | RTLD_LOCAL);

	if (!dlHandle) {
		if (DEBUG_MODE) {
			std::cerr << "Failed to load library [" << dlerror() << "]" << std::endl;
		} else {
			std::cerr << "Failed to load library [" << string << "]" << std::endl;
		}
		return false;
	}

	// free the current aGraphic
	if (Nibbler::_dlHandle != nullptr && Nibbler::_dlHandle != dlHandle) {
		toReload = true;
		Nibbler::_aGraphics->cleanUp();
		Nibbler::_deleteAGraphics(Nibbler::_aGraphics);
		dlclose(Nibbler::_dlHandle);
	} else if (Nibbler::_dlHandle == dlHandle) {
		return true;
	}

	// get createGraphics function
	createGraphics = (AGraphics *(*)()) dlsym(dlHandle, "createGraphics");
	if (!createGraphics) {
		if (DEBUG_MODE) {
			std::cerr << "Failed to load function[" << dlerror() << "]" << std::endl;
		} else {
			std::cerr << "Failed to load [createGraphics]" << std::endl;
		}
		return false;
	}
	// get deleteGraphics function
	deleteGraphics = (AGraphics *(*)(AGraphics *)) dlsym(dlHandle, "deleteGraphics");
	if (!deleteGraphics) {
		if (DEBUG_MODE) {
			std::cerr << "Failed to load function[" << dlerror() << "]" << std::endl;
		} else {
			std::cerr << "Failed to load [deleteGraphics]" << std::endl;
		}
		return false;
	}

	Nibbler::_deleteAGraphics = deleteGraphics;
	Nibbler::_aGraphics = createGraphics();
	Nibbler::_dlHandle = dlHandle;
	if (toReload) {
		Nibbler::initAGraphics();
	}
	return true;
}

void Nibbler::closeDlHandle() {
	dlclose(Nibbler::_dlHandle);
}









