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

#ifndef PROJECT_ASCENE_HPP
#define PROJECT_ASCENE_HPP


#include "AGraphics.hpp"

enum eTexture {
    TEXTURE_VOID,
    MENU_BCKG,
    GAME_BCKG,
    SCORE_BCKG,
	SNAKE,
	FOOD,
	FONT,
    NB_TEXTURE
};

class AScene {

public:
    virtual void eventHandler(std::vector<eEvent> eventList) = 0;
    virtual void drawScene() = 0;

protected:
    AGraphics *aGraphics;

};


#endif //PROJECT_ASCENE_HPP
