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

#define SIZE_FONT_MENU 3.5
#define FONT_NEWLINE SIZE_FONT_MENU * 20

enum ePage	{
	PAGE_VOID,
	PAGE_MENU,
	PAGE_OPTION,
	NB_PAGE
};

enum eMenu {
	MENU_VOID,
	MENU_GAME,
	MENU_OPTION,
	MENU_EXIT,
	NB_ENTRY
};

enum eOption {
	OPTION_VOID,
	OPTION_SDL,
	OPTION_SFML,
	OPTION_GL,
	NB_OPTION
};

class SceneMenu : public AScene {

public:
	SceneMenu(AGraphics *aGraphics);
	~SceneMenu(); // Canonical

	void eventHandler(std::vector<eEvent> eventList);

	void drawScene();

private:
	SceneMenu(); // Canonical
	SceneMenu(SceneMenu const &copy); // Canonical
	SceneMenu &operator=(SceneMenu const &copy); // Canonical

	int 							_page;
	size_t							_cursor;
	std::map<std::string, t_coordi>	_input;
};


#endif //PROJECT_SCENEMENU_HPP