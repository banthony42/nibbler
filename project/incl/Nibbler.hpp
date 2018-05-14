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
#include <map>
#include <dlfcn.h>
#include "AGraphics.hpp"
#include "AScene.hpp"
#include "SceneMenu.hpp"
#include "SceneSkin.hpp"
#include "SceneGame.hpp"
#include "SceneGameEnd.hpp"

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

class Nibbler {

public:
	typedef std::map<eScene, AScene *> MapScene;

	static void *_dlHandle;
	static AGraphics *_aGraphics;

	static int iRound(double a);
	static int getWindowWidth();
	static void setWindowWidth(int w);
	static int getWindowHeight();
	static void setWindowHeight(int h);
	static eScene getCurrentScene();
	static void setCurrentScene(eScene _currentScene);

	static Nibbler *getInstance();
	static bool loadLibrary(std::string const string);
	static void closeDlHandle();

	void run();

private:
	static AGraphics *(*_deleteAGraphics)(AGraphics *);
	static Nibbler *_singleton;
	static eScene _currentScene;
	static int WINDOW_WIDTH;
	static int WINDOW_HEIGHT;
	MapScene _callScene;

	static void initAGraphics();
	void initRun();

	Nibbler(); // Canonical
	Nibbler(Nibbler const &copy); // Canonical
	~Nibbler(); // Canonical
	Nibbler &operator=(Nibbler const &copy); // Canonical
};

#endif //PROJECT_NIBBLER_HPP











