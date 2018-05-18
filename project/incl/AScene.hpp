/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AScene.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:46:23 by banthony          #+#    #+#             */
/*   Updated: 2018/04/30 16:46:23 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASCENE_HPP
#define ASCENE_HPP

#include "AGraphics.hpp"
#include <map>

enum eTexture {
	TEXTURE_VOID,
	MENU_BCKG,
	GAME_GRASS,
	GAME_BORDER,
	GAME_BRICK,
	GAME_BORDER_GRASS,
	GAMEOVER_BORDER,
	FOG_OVERLAY,
	SKIN_FRAME,
	SCORE_BCKG,
	SNAKE_H_PCM,    // Order of the skin texture is important
	SNAKE_H_SMB,
	SNAKE_H_HK,
	SNAKE_B_PCM,
	SNAKE_B_SMB,
	SNAKE_B_HK,
	FOOD,
	SHADOW_BOMB1,
	SHADOW_BOMB2,
	BOMB1,
	BOMB2,
	BOMB3,
	EXPLOSION1,
	EXPLOSION2,
	EXPLOSION3,
	EXPLOSION4,
	NB_TEXTURE
};

class AScene {

public:
	virtual void eventHandler(std::vector<eEvent> eventList) = 0;
	virtual void drawScene() = 0;

	virtual void eventEchap() = 0;
	virtual void eventUp() = 0;
	virtual void eventDown() = 0;
	virtual void eventLeft() = 0;
	virtual void eventRight() = 0;
	virtual void eventEnter() = 0;
	virtual void eventF1() = 0;
	virtual void eventF2() = 0;
	virtual void eventF3() = 0;


protected:
	typedef void(AScene::*eventFuncPtr)();
	typedef std::map<eEvent, eventFuncPtr> mapEventFuncPtr;

	AGraphics **_aGraphics;
	mapEventFuncPtr _eventMap;
};

#endif //PROJECT_ASCENE_HPP
