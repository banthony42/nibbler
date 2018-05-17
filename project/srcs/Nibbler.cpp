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
	aGraphics->loadFontTexture("./textures/snake_font.tga");
}

void Nibbler::initRun() {
	this->_callScene[MENU] = new SceneMenu(&this->_aGraphics);
	this->_callScene[SKIN] = new SceneSkin(&this->_aGraphics);
	this->_callScene[GAME] = new SceneGame(&this->_aGraphics);
	this->_callScene[GAME_END] = new SceneGameEnd(&this->_aGraphics);
	Nibbler::initAGraphics(this->_aGraphics);
	DeltaTime::setMaxFps(30);
}
// TODO 1000 constant fps for the sfml is suspect
// TODO lock fps



// -----------------------------
// TODO CRITIQUES :
	// TODO SUJET : on doit pouvoir changer de lib en faisant F1 F2 ou F3
	// TODO SUJET : une foret de if pour les events n'est PAS acceptable

// TODO A FAIRE :
	// TODO SUJET : toute les erreurs doivent etre a base de Throw
	// TODO SUJET : les deux binomes doivent etre incollable sur chacune des partie de l'autres (faut que tu m'explique en details l'affichage du texte a l'ecran)

// TODO OPTIONNEL :
	// TODO SUJET : les bonus qu'il faut qu'on face : Augmenter la vitesse plus rapidement / ajouter des objstacles
// ----------------------------



void Nibbler::run() {
	try {
		this->initRun();
	} catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		return ;
	}

	/****************** MAIN WHILE ******************/
	while (Nibbler::_aGraphics->loopUpdate()) {
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
			std::cerr << "Failed to load function [" << dlerror() << "]" << std::endl;
		} else {
			std::cerr << "Failed to load [createGraphics]" << std::endl;
		}
		return false;
	}
	// get deleteGraphics function
	deleteGraphics = (AGraphics *(*)(AGraphics *)) dlsym(dlHandle, "deleteGraphics");
	if (!deleteGraphics) {
		if (DEBUG_MODE) {
			std::cerr << "Failed to load function [" << dlerror() << "]" << std::endl;
		} else {
			std::cerr << "Failed to load [deleteGraphics]" << std::endl;
		}
		return false;
	}


	AGraphics *aGraphics = createGraphics();
	if (toReload) {
		try {
			// if it doesnt work, we don't override the current aGraphics
			Nibbler::initAGraphics(aGraphics);
		} catch (std::runtime_error &e) {
			std::cout << e.what() << std::endl;
			return false;
		}
	}
	Nibbler::_aGraphics = aGraphics;
	Nibbler::_deleteAGraphics = deleteGraphics;
	Nibbler::_dlHandle = dlHandle;
	return true;
}

void Nibbler::closeDlHandle() {
	dlclose(Nibbler::_dlHandle);
}