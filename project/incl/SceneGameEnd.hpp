/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneGameEnd.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:46:43 by banthony          #+#    #+#             */
/*   Updated: 2018/04/30 16:46:43 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENEGAMEEND_HPP
#define SCENEGAMEEND_HPP

#include "AScene.hpp"
#include "Nibbler.hpp"

enum eEndGame {
    BEST_SCORE,
	REPLAY,
	BACK_TO_MENU,
	NB_INPUT_ENDGAME
};

class SceneGameEnd : public AScene {

public:
    SceneGameEnd(AGraphics **aGraphics);
    ~SceneGameEnd(); // Canonical

	void eventHandler(std::vector<eEvent> eventList);
	void drawScene();

private:
    SceneGameEnd(); // Canonical
    SceneGameEnd(SceneGameEnd const &copy); // Canonical
    SceneGameEnd &operator=(SceneGameEnd const &copy);// Canonical

	void eventEchap();
	void eventUp();
	void eventDown();
	void eventLeft();
	void eventRight();
	void eventEnter();
	void eventF1();
	void eventF2();
	void eventF3();

	size_t                          _cursor;
	std::map<eEndGame, t_coordi>      _input;
	std::map<eEndGame, std::string>   _inputName;
};


#endif //PROJECT_SCENEGAMEEND_HPP