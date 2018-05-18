/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nibbler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:51:29 by banthony          #+#    #+#             */
/*   Updated: 2018/04/26 17:51:29 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_HPP
#define NIBBLER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <dlfcn.h>
#include "AGraphics.hpp"
#include "AScene.hpp"
#include "SceneMenu.hpp"
#include "SceneSkin.hpp"
#include "SceneGame.hpp"
#include "SceneGameEnd.hpp"
#include "DeltaTime.hpp"

// Calcul x % de val
#define PERCENTAGE(x, val) ((x * val) / 100)

enum eScene {
	STATE_VOID,
	MENU,
	GAME,
	SKIN,
	GAME_END,
	NB_STATE
};

#define LIB_SDL_PATH "./libSDL/libgraph.so"
#define LIB_OPENGL_PATH "./libOpenGL/libgraph.so"
#define LIB_SFML_PATH "./libSFML/libgraph.so"

#define SCORE_PATH "./score"

#define WINDOW_MIN_X 800
#define WINDOW_MIN_Y 600

class Nibbler {

public:
	typedef std::map<eScene, AScene *> MapScene;

	static void *_dlHandle;
	static AGraphics *_aGraphics;
	static std::string libToLoad;

	static int iRound(double a);
	static int loadBestScore();
	static void saveBestScore(int i);
	static int getWindowWidth();
	static void setWindowWidth(int w);
	static int getWindowHeight();
	static void setWindowHeight(int h);
	static eScene getCurrentScene();
	static void setCurrentScene(eScene _currentScene);

	static Nibbler *getInstance();
	static void loadLibrary(std::string const string);
	static void closeDlHandle();

	void run();

private:
	static AGraphics *(*_deleteAGraphics)(AGraphics *);
	static Nibbler *_singleton;
	static eScene _currentScene;
	static int WINDOW_WIDTH;
	static int WINDOW_HEIGHT;
	MapScene _callScene;

	static void initAGraphics(AGraphics *aGraphics);
	void initRun();

	Nibbler(); // Canonical
	Nibbler(Nibbler const &copy); // Canonical
	~Nibbler(); // Canonical
	Nibbler &operator=(Nibbler const &copy); // Canonical
};

#endif //PROJECT_NIBBLER_HPP











