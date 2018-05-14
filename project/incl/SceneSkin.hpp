/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneSkin.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:46:59 by banthony          #+#    #+#             */
/*   Updated: 2018/04/30 16:46:59 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENESKIN_HPP
#define SCENESKIN_HPP

#include <map>
#include "AScene.hpp"

enum eSelectSkin {
	NO_SKIN,
	SKIN_1,
	SKIN_2,
	SKIN_3,
	NB_SKIN
};

#define MARGIN_X 25
#define MARGIN_Y 10
#define FRAME_START_X PERCENTAGE((MARGIN_X / 2), Nibbler::getWindowWidth())
#define FRAME_START_Y PERCENTAGE((MARGIN_Y / 2), Nibbler::getWindowHeight())
#define FRAME_WIDTH PERCENTAGE((100 - MARGIN_X), Nibbler::getWindowWidth())
#define FRAME_HEIGHT PERCENTAGE((100 - MARGIN_Y), Nibbler::getWindowHeight())

class SceneSkin : public AScene {

public:
	SceneSkin(AGraphics **aGraphics);
	~SceneSkin(); // Canonical

	void eventHandler(std::vector<eEvent> eventList);
	void drawScene();

private:
	SceneSkin(); // Canonical
	SceneSkin(SceneSkin const &copy); // Canonical
	SceneSkin &operator=(SceneSkin const &copy);    // Canonical

	size_t								_cursor;
	std::map<eTexture, t_coordi>		_input;
};


#endif //PROJECT_SCENESKIN_HPP