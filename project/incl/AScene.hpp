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

enum eTexture {
	TEXTURE_VOID,
	MENU_BCKG,
	GAME_GRASS,
	GAME_BORDER,
	GAME_BRICK,
	GAME_BORDER_GRASS,
	SKIN_BCKG, // TODO utile ?
	SKIN_FRAME,
	SCORE_BCKG,
	SNAKE_H_PCM,
	SNAKE_B_PCM,
	SNAKE_H_SMB,
	SNAKE_B_SMB,
	SNAKE_H_HK,
	SNAKE_B_HK,
	FOOD,
	NB_TEXTURE
};

class AScene {

public:
	virtual void eventHandler(std::vector<eEvent> eventList) = 0;
	virtual void drawScene() = 0;

protected:
	AGraphics **_aGraphics;

};


#endif //PROJECT_ASCENE_HPP
