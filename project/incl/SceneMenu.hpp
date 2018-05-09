/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneMenu.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:46:51 by banthony          #+#    #+#             */
/*   Updated: 2018/04/30 16:46:51 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENEMENU_HPP
#define SCENEMENU_HPP

#include "AScene.hpp"
#include "Nibbler.hpp"

#define SIZE_FONT_MENU 3.5	// TODO Size font have to be proportional to the window size
#define FONT_NEWLINE SIZE_FONT_MENU * 20

enum ePage {
	PAGE_MENU,
	PAGE_OPTION,
	NB_PAGE
};

enum eMenu {
	MENU_GAME,
	MENU_OPTION,
	MENU_EXIT,
	END_MENU_INPUT,
	OPTION_SDL,
	OPTION_SFML,
	OPTION_GL,
	END_OPTION_INPUT
};

class SceneMenu : public AScene {

public:
	SceneMenu(AGraphics **aGraphics);

	~SceneMenu(); // Canonical

	void eventHandler(std::vector<eEvent> eventList);

	void drawScene();

private:
	SceneMenu(); // Canonical
	SceneMenu(SceneMenu const &copy); // Canonical
	SceneMenu &operator=(SceneMenu const &copy); // Canonical

	ePage _page;
	size_t _cursor;
	std::map<eMenu, t_coordi> _input;
	std::map<eMenu, std::string> _inputName;
};


#endif //PROJECT_SCENEMENU_HPP