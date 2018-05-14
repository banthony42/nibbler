/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneMenu.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:48:59 by banthony          #+#    #+#             */
/*   Updated: 2018/04/30 16:48:59 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/SceneMenu.hpp"

SceneMenu::SceneMenu() {

}

SceneMenu::SceneMenu(SceneMenu const &copy) {
    *this = copy;
}

SceneMenu::~SceneMenu() {

}

SceneMenu &SceneMenu::operator=(SceneMenu const &copy) {
    if (this != &copy) {
        // copy
    }
    return *this;
}

SceneMenu::SceneMenu(AGraphics **aGraphics) {
    this->_aGraphics = aGraphics;

    this->_page = PAGE_MENU;
    this->_cursor = MENU_GAME;

    this->_inputName[MENU_GAME] = "Game";
    this->_inputName[MENU_OPTION] = "Options";
    this->_inputName[MENU_EXIT] = "Exit";
    this->_inputName[OPTION_SDL] = "SDL";
    this->_inputName[OPTION_SFML] = "SFML";
    this->_inputName[OPTION_GL] = "OPEN_GL";

    t_coordi pos = {};
    pos.x = (*this->_aGraphics)->centerTextX(_inputName[MENU_GAME], SIZE_FONT_MENU, Nibbler::getWindowWidth());
    pos.y = PERCENTAGE(38, Nibbler::getWindowHeight());
    this->_input[MENU_GAME] = pos;
    pos.x = (*this->_aGraphics)->centerTextX(_inputName[OPTION_GL], SIZE_FONT_MENU, Nibbler::getWindowWidth());
    this->_input[OPTION_SDL] = pos;

    pos.x = (*this->_aGraphics)->centerTextX(_inputName[MENU_OPTION], SIZE_FONT_MENU, Nibbler::getWindowWidth());
    pos.y += FONT_NEWLINE;
    this->_input[MENU_OPTION] = pos;
    pos.x = (*this->_aGraphics)->centerTextX(_inputName[OPTION_GL], SIZE_FONT_MENU, Nibbler::getWindowWidth());
    this->_input[OPTION_SFML] = pos;

    pos.x = (*this->_aGraphics)->centerTextX(_inputName[MENU_EXIT], SIZE_FONT_MENU, Nibbler::getWindowWidth());
    pos.y += FONT_NEWLINE;
    this->_input[MENU_EXIT] = pos;
    pos.x = (*this->_aGraphics)->centerTextX(_inputName[OPTION_GL], SIZE_FONT_MENU, Nibbler::getWindowWidth());
    this->_input[OPTION_GL] = pos;
}

void SceneMenu::eventHandler(std::vector<eEvent> eventList) {
    eEvent event = EVENT_VOID;
    if (this->_page == PAGE_MENU) {
        for (auto &event : eventList) {
            if (event == ECHAP) {
                Nibbler::_aGraphics->cleanUp();
            } else if (event == UP) {
                if (this->_cursor > MENU_GAME) {
                    this->_cursor--;
                }
            } else if (event == DOWN) {
                if (this->_cursor < MENU_EXIT) {
                    this->_cursor++;
                }
            } else if (event == ENTER) {
                if (this->_cursor == MENU_GAME) {
                    Nibbler::setCurrentScene(SKIN);
                } else if (this->_cursor == MENU_OPTION) {
                    this->_cursor = OPTION_SDL;
                    this->_page = PAGE_OPTION;
                } else if (this->_cursor == MENU_EXIT) {
                    Nibbler::_aGraphics->cleanUp();
                }
            }
        }
    } else if (this->_page == PAGE_OPTION) {
        for (auto &event : eventList) {
            if (event == ECHAP) {
                this->_page = PAGE_MENU;
                this->_cursor = MENU_GAME;
            } else if (event == UP) {
                if (this->_cursor > OPTION_SDL) {
                    this->_cursor--;
                }
            } else if (event == DOWN) {
                if (this->_cursor < OPTION_GL) {
                    this->_cursor++;
                }
            } else if (event == ENTER) {
                if (this->_cursor == OPTION_SDL) {
                    Nibbler::loadLibrary(LIB_SDL_PATH);
                } else if (this->_cursor == OPTION_SFML) {
                    Nibbler::loadLibrary(LIB_SFML_PATH);
                } else if (this->_cursor == OPTION_GL) {
                    Nibbler::loadLibrary(LIB_OPENGL_PATH);
                }
                this->_page = PAGE_MENU;
                this->_cursor = MENU_GAME;
            }
        }
    }
}

void SceneMenu::drawScene() {
    (*this->_aGraphics)->clear();

    // Page du Menu
    if (this->_page == PAGE_MENU) {

        (*this->_aGraphics)->putTexture(MENU_BCKG, 0, 0, Nibbler::getWindowWidth(), Nibbler::getWindowHeight());
        (*this->_aGraphics)->putStrScreen(this->_inputName[MENU_GAME], this->_input[MENU_GAME].x,
                                          this->_input[MENU_GAME].y, SIZE_FONT_MENU);
        (*this->_aGraphics)->putStrScreen(this->_inputName[MENU_OPTION], this->_input[MENU_OPTION].x,
                                          this->_input[MENU_OPTION].y, SIZE_FONT_MENU);
        (*this->_aGraphics)->putStrScreen(this->_inputName[MENU_EXIT], this->_input[MENU_EXIT].x,
                                          this->_input[MENU_EXIT].y, SIZE_FONT_MENU);
    }


    // Page d'options
    if (this->_page == PAGE_OPTION) {

        (*this->_aGraphics)->putTexture(MENU_BCKG, 0, 0, Nibbler::getWindowWidth(), Nibbler::getWindowHeight());
        (*this->_aGraphics)->putStrScreen("Choose a library to run:",
                                          (*this->_aGraphics)->centerTextX("Choose a library to run:", SIZE_FONT_MENU,
                                                                           Nibbler::getWindowWidth()),
                                          PERCENTAGE(20, Nibbler::getWindowHeight()),
                                          SIZE_FONT_MENU);
        (*this->_aGraphics)->putStrScreen(this->_inputName[OPTION_SDL], this->_input[OPTION_SDL].x,
                                          this->_input[OPTION_SDL].y, SIZE_FONT_MENU);
        (*this->_aGraphics)->putStrScreen(this->_inputName[OPTION_SFML], this->_input[OPTION_SFML].x,
                                          this->_input[OPTION_SFML].y, SIZE_FONT_MENU);
        (*this->_aGraphics)->putStrScreen(this->_inputName[OPTION_GL], this->_input[OPTION_GL].x,
                                          this->_input[OPTION_GL].y, SIZE_FONT_MENU);
    }

    // Draw Cursor
    eMenu curs = static_cast<eMenu>(this->_cursor);
    t_coordi posCurs = {};

    posCurs.x = static_cast<int>(this->_input[curs].x - GET_SIZEFONT_X(SIZE_FONT_MENU));
    posCurs.y = this->_input[curs].y;
    (*this->_aGraphics)->putStrScreen("<", posCurs.x, posCurs.y, SIZE_FONT_MENU);

    posCurs.x = static_cast<int>(this->_input[curs].x +
                                 ((this->_inputName[curs].length()) * GET_SIZEFONT_X(SIZE_FONT_MENU)));
    posCurs.y = this->_input[curs].y;
    (*this->_aGraphics)->putStrScreen(">", posCurs.x, posCurs.y, SIZE_FONT_MENU);

    (*this->_aGraphics)->display();
}




















