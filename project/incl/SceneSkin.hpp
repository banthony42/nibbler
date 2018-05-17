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

#define NB_SKIN 3

#define MARGIN_X 25
#define MARGIN_Y 10

#define FRAME_START_X PERCENTAGE((MARGIN_X / 2), Nibbler::getWindowWidth())
#define FRAME_START_Y PERCENTAGE((MARGIN_Y / 2), Nibbler::getWindowHeight())

#define FRAME_WIDTH PERCENTAGE((100 - MARGIN_X), Nibbler::getWindowWidth())
#define FRAME_HEIGHT PERCENTAGE((100 - MARGIN_Y), Nibbler::getWindowHeight())

#define SKIN_START_X(x) (PERCENTAGE(x, Nibbler::getWindowWidth()) + (1 * SECTOR_DEFAULT_SIZE))
#define SKIN_START_Y(x) static_cast<int>(PERCENTAGE(x, Nibbler::getWindowHeight()) - (SECTOR_DEFAULT_SIZE / 2))
#define SKIN_B_START_X(x, offset) (x - (offset * SECTOR_DEFAULT_SIZE))

#define SELECTOR_SIZE (10 * GET_SIZEFONT_X(SIZE_FONT_MENU))

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

    void eventEchap();
    void eventUp();
    void eventDown();
    void eventLeft();
    void eventRight();
    void eventEnter();
    void eventF1();
    void eventF2();
    void eventF3();

	size_t _cursor;
	std::map<eTexture, t_coordi> _input;
};


#endif //PROJECT_SCENESKIN_HPP