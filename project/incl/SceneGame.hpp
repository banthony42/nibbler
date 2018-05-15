/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneGame.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:46:35 by banthony          #+#    #+#             */
/*   Updated: 2018/04/30 16:46:35 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENEGAME_HPP
#define SCENEGAME_HPP

#include "AScene.hpp"
#include "Nibbler.hpp"

#define BORDER_GAME_HEIGHT 630.f
#define BORDER_GAME_WIDTH 900.f
#define BORDER_GAME_SIDE 74.f

#define FLOOR_SCENE_START_X (int)(PERCENTAGE(((BORDER_GAME_SIDE / BORDER_GAME_WIDTH) * 100.f), Nibbler::getWindowWidth()) / 2)
#define FLOOR_SCENE_START_Y (int)(PERCENTAGE(((BORDER_GAME_SIDE / BORDER_GAME_HEIGHT) * 100.f), Nibbler::getWindowHeight()) / 2)

#define FLOOR_SCENE_END_X (Nibbler::getWindowWidth() - FLOOR_SCENE_START_X * 1)
#define FLOOR_SCENE_END_Y (Nibbler::getWindowHeight() - FLOOR_SCENE_START_Y * 1)

#define FLOOR_SIZE_X (FLOOR_SCENE_END_X - FLOOR_SCENE_START_X)
#define FLOOR_SIZE_Y (FLOOR_SCENE_END_Y - FLOOR_SCENE_START_Y)

#define SECTOR_DEFAULT_SIZE 40

#define SIZE_FONT_GAMEOVER 2

#define SPEED_DEFAULT 8
#define SPEED_INCR (12 * 42)    // Multiple de 42 car on utilise le % 42 dans le code
#define DIFFICULTY_INCR 0.5

enum ePageGame {
	PAGE_GAME,
	PAGE_PAUSE,
	PAGE_GAMEOVER,
	NB_PAGE_GAME
};

enum ePause {
    PAUSE_TITLE,
	RESUME,
	QUIT,
	NB_INPUT_PAUSE
};

typedef struct {
	std::vector<t_coordd> body;
	t_coordd vec;
	eTexture headSkin;
	eTexture bodySkin;
	double speed;
} t_snake;

typedef struct {
	t_coordi pos;
	eTexture skin;
} t_food;

class SceneGame : public AScene {

public:
	static eTexture _selectedHeadSkin;
	static eTexture _selectedBodySkin;
	static int _speed;
	SceneGame(AGraphics **aGraphics);
	~SceneGame(); // Canonical

	void eventHandler(std::vector<eEvent> eventList);

	void drawScene();

private:
	SceneGame(); // Canonical
	SceneGame(SceneGame const &copy); // Canonical
	SceneGame &operator=(SceneGame const &copy); // Canonical

	void drawInfoOverlay();
    void drawGameOverOverlay();
    void drawPauseOverlay();
	void moveSnake();
	void resetSceneGame();
	void drawSector(eTexture t, int sectorX, int sectorY);
	void drawFullSnake();
	void drawFood();
	void initNewSnake();
	void initNewFood();
	bool checkCollision(t_coordi pos);

	bool _gameInstanced;
	t_coordi _floorSceneStart;
	t_coordi _floorSize;
	t_coordi _sectorStart;
	t_coordi _sectorSize;
	t_coordi _sectorCount;

    double                          _difficulty;
    double                          _timestamp;
    double                          _deltaTimeCount;
	ePageGame                       _page;
	size_t                          _cursor;
    std::map<ePause, t_coordi>      _input;
    std::map<ePause, std::string>   _inputName;

	int _score;
	std::vector<t_coordd> vectorPool;   // TODO il manque l'underscore ! Tu m'emmerdes avec tes accolades pour des if de une ligne, et tu met pas l'underscore ici ?? OH ! mais tes un fou
	t_snake _snake;
	t_coordd _headPos;
	t_coordd _lastHeadPos;
	t_food _food;
};


#endif //PROJECT_SCENEGAME_HPP



















