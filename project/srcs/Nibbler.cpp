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

#include <zconf.h>
#include "../incl/Nibbler.hpp"

int DEBUG_MODE = false;

Nibbler *Nibbler::_singleton = nullptr;
AGraphics *Nibbler::_aGraphics = nullptr;
AGraphics *(*Nibbler::_deleteAGraphics)(AGraphics *) = nullptr;

void *Nibbler::_dlHandle = nullptr;
std::string Nibbler::libToLoad = "";
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

void Nibbler::saveBestScore(int i) {
	std::ofstream file;

	remove(SCORE_PATH);
	file.open(SCORE_PATH);
	if (file.is_open()) {
		file << std::to_string(i);
		file.close();
	} else {
		std::cout << "failed to save the score" << std::endl;
	}
}

int Nibbler::loadBestScore() {
	std::ifstream file;
	std::string output;

	file.open(SCORE_PATH);
	if (file.is_open()) {
		file >> output;
		try {
			return std::stoi(output);
		} catch (std::exception &e) {
			remove(SCORE_PATH);
			Nibbler::saveBestScore(0);
		}
		file.close();
	} else {
		Nibbler::saveBestScore(0);
	}
	return 0;
}

int Nibbler::iRound(double a) {
	return round(a);
}

void Nibbler::initAGraphics(AGraphics *aGraphics) {

	aGraphics->init(Nibbler::WINDOW_WIDTH, Nibbler::WINDOW_HEIGHT, "Nibbler");
	aGraphics->loadTexture("./textures/menu_bckg.png", MENU_BCKG);
	aGraphics->loadTexture("./textures/game_grass.png", GAME_GRASS);
	aGraphics->loadTexture("./textures/game_border.png", GAME_BORDER);
	aGraphics->loadTexture("./textures/fog-overlay.png", FOG_OVERLAY);
	aGraphics->loadTexture("./textures/game_border_grass.png", GAME_BORDER_GRASS);
	aGraphics->loadTexture("./textures/snake_gameOver.png", GAMEOVER_BORDER);
	aGraphics->loadTexture("./textures/game_brick.png", GAME_BRICK);
	aGraphics->loadTexture("./textures/score_bckg.png", SCORE_BCKG);
	aGraphics->loadTexture("./textures/skin_border.png", SKIN_FRAME);
	aGraphics->loadTexture("./textures/snake_head_smb.png", SNAKE_H_SMB);
	aGraphics->loadTexture("./textures/snake_body_smb.png", SNAKE_B_SMB);
	aGraphics->loadTexture("./textures/snake_head_pcm.png", SNAKE_H_PCM);
	aGraphics->loadTexture("./textures/snake_body_pcm.png", SNAKE_B_PCM);
	aGraphics->loadTexture("./textures/snake_head_hk.png", SNAKE_H_HK);
	aGraphics->loadTexture("./textures/snake_body_hk.png", SNAKE_B_HK);
	aGraphics->loadTexture("./textures/melon.png", FOOD);
	aGraphics->loadTexture("./textures/bomb1.png", BOMB1);
	aGraphics->loadTexture("./textures/bomb3.png", BOMB2);
	aGraphics->loadTexture("./textures/bomb3.png", BOMB3);
	aGraphics->loadTexture("./textures/explosion1.png", EXPLOSION1);
	aGraphics->loadTexture("./textures/explosion2.png", EXPLOSION2);
	aGraphics->loadTexture("./textures/explosion3.png", EXPLOSION3);
	aGraphics->loadTexture("./textures/explosion4.png", EXPLOSION4);
	aGraphics->loadFontTexture("./textures/snake_font.tga");
}

void Nibbler::initRun() {
	this->_callScene[MENU] = new SceneMenu(&this->_aGraphics);
	this->_callScene[SKIN] = new SceneSkin(&this->_aGraphics);
	this->_callScene[GAME] = new SceneGame(&this->_aGraphics);
	this->_callScene[GAME_END] = new SceneGameEnd(&this->_aGraphics);
	Nibbler::libToLoad = "";
	Nibbler::initAGraphics(this->_aGraphics);
	DeltaTime::setMaxFps(30);
}

void Nibbler::run() {
	try {
		this->initRun();
	} catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		return;
	}

	/****************** MAIN WHILE ******************/
	while (Nibbler::_aGraphics->loopUpdate()) {
		if (Nibbler::libToLoad != "") {
			loadLibrary(Nibbler::libToLoad);
			Nibbler::libToLoad = "";
		}
		DeltaTime::startDelta();
		DeltaTime::limitFps();

		auto vec = Nibbler::_aGraphics->getEvent();
		this->_callScene[this->_currentScene]->eventHandler(vec);
		this->_callScene[this->_currentScene]->drawScene();

		DeltaTime::endDelta();
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
	} else if (h > 1440) {
		h = 1440;
	}
	Nibbler::WINDOW_HEIGHT = h;
}

void Nibbler::loadLibrary(std::string const string) {
	bool toReload = false;
	void *dlHandle = nullptr;
	AGraphics *(*createGraphics)();
	AGraphics *(*deleteGraphics)(AGraphics *);

	dlHandle = dlopen(string.c_str(), RTLD_LAZY | RTLD_LOCAL);
	if (!dlHandle) {
		if (DEBUG_MODE) {
			throw std::runtime_error(std::string("failed to load library [" + std::string(dlerror()) + "]"));
		} else {
			throw std::runtime_error(std::string("failed to load library [" + string + "]"));
		}
	}

	// free the current aGraphic
	if (Nibbler::_dlHandle != nullptr && Nibbler::_dlHandle != dlHandle) {
		toReload = true;
		Nibbler::_aGraphics->cleanUp();
		Nibbler::_deleteAGraphics(Nibbler::_aGraphics);
		dlclose(Nibbler::_dlHandle);
	} else if (Nibbler::_dlHandle == dlHandle) {
		return;
	}

	// get createGraphics function
	createGraphics = (AGraphics *(*)()) dlsym(dlHandle, "createGraphics");
	if (!createGraphics) {
		if (DEBUG_MODE) {
			throw std::runtime_error(std::string("failed to load function [" + std::string(dlerror()) + "]"));
		} else {
			throw std::runtime_error(std::string("failed to load [createGraphics]"));
		}
	}

	// get deleteGraphics function
	deleteGraphics = (AGraphics *(*)(AGraphics *)) dlsym(dlHandle, "deleteGraphics");
	if (!deleteGraphics) {
		if (DEBUG_MODE) {
			throw std::runtime_error(std::string("failed to load function [" + std::string(dlerror()) + "]"));
		} else {
			throw std::runtime_error(std::string("failed to load [deleteGraphics]"));
		}
	}

	AGraphics *aGraphics = createGraphics();
	if (toReload) {
		// if it doesnt work, we don't override the current aGraphics
		Nibbler::initAGraphics(aGraphics);
	}
	Nibbler::_aGraphics = aGraphics;
	Nibbler::_deleteAGraphics = deleteGraphics;
	Nibbler::_dlHandle = dlHandle;
}

void Nibbler::closeDlHandle() {
	dlclose(Nibbler::_dlHandle);
}