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

typedef struct {
	t_coordd headPos;
	t_coordd tailPos;
	t_coordd vec;
	int size;
	eTexture headSkin;
	eTexture bodySkin;
} t_snake;

typedef struct {
	t_coordd pos;
	int energy;    // TODO définir l'utilité
	eTexture skin;
} t_food;

#define BORDER_GAME_HEIGHT 630.f
#define BORDER_GAME_WIDTH 900.f
#define BORDER_GAME_SIDE 74.f

#define FLOOR_SCENE_START_X (int)(PERCENTAGE(((BORDER_GAME_SIDE / BORDER_GAME_WIDTH) * 100.f), Nibbler::getWindowWidth()) / 2)
#define FLOOR_SCENE_START_Y (int)(PERCENTAGE(((BORDER_GAME_SIDE / BORDER_GAME_HEIGHT) * 100.f), Nibbler::getWindowHeight()) / 2)

#define FLOOR_SCENE_END_X (Nibbler::getWindowWidth() - FLOOR_SCENE_START_X * 1)
#define FLOOR_SCENE_END_Y (Nibbler::getWindowHeight() - FLOOR_SCENE_START_Y * 1)

#define FLOOR_SIZE_X (FLOOR_SCENE_END_X - FLOOR_SCENE_START_X)
#define FLOOR_SIZE_Y (FLOOR_SCENE_END_Y - FLOOR_SCENE_START_Y)

#define SECTOR_START_X (FLOOR_SCENE_START_X * 2)
#define SECTOR_START_Y (FLOOR_SCENE_START_Y * 2)
#define SECTOR_DEFAULT_SIZE_X 40
#define SECTOR_DEFAULT_SIZE_Y 40

#define SECTOR_MINI_SIZE 16

class SceneGame : public AScene {

public:
	static eTexture _selectedHeadSkin;
	static eTexture _selectedBodySkin;
	SceneGame(AGraphics **aGraphics);
	~SceneGame(); // Canonical

	void eventHandler(std::vector<eEvent> eventList);

	void drawScene();

private:
	SceneGame(); // Canonical
	SceneGame(SceneGame const &copy); // Canonical
	SceneGame &operator=(SceneGame const &copy); // Canonical

	void moveSnake();

	bool _gameInstanced;
	t_coordi _floorSceneStart;
	t_coordi _floorSceneEnd;
    t_coordi _sectorStart;
	int _sectorSize;
	int _sectorCount;

	static const int _N_SECTX = 16;    //TODO Voir si on calcul ces valeurs en fonctions de la taille de la fenetre
	static const int _N_SECTY = 16;
	t_snake _snake;
	t_food _food;            //TODO: Definir le nb de food max sur scene, dans ce cas: _food[MAX_FOOD]
	void initSceneGame();
};


#endif //PROJECT_SCENEGAME_HPP



















