/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nibbler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:51:29 by banthony          #+#    #+#             */
/*   Updated: 2018/04/26 17:51:29 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_HPP
#define NIBBLER_HPP

#include <iostream>
#include <map>
#include <dlfcn.h>
#include "AGraphics.hpp"
#include "AScene.hpp"
#include "SceneMenu.hpp"
#include "SceneSkin.hpp"
#include "SceneGame.hpp"
#include "SceneGameEnd.hpp"

enum eScene {
    STATE_VOID,
    MENU,
    GAME,
    SKIN,
    GAME_END,
    NB_STATE
};

class Nibbler {

public:
    typedef std::map<eScene, AScene *> MapScene;
    static AGraphics *_aGraphics;
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;

    static Nibbler *getInstance();
    void run();

private:
    static Nibbler *_singleton;
    MapScene _callScene;
    eScene _currentScene;

    void initRun();

    Nibbler(); // Canonical
    Nibbler(Nibbler const &copy); // Canonical
    ~Nibbler(); // Canonical
    Nibbler &operator=(Nibbler const &copy); // Canonical
};

/*

+ enum eStateGame { MENU, GAME, SKIN, GAME_END, NB_STATE } // Définit les différent états du jeux
+ enum eTexture { MENU_BCKG, GAME_BCKG, SCORE_BCKG, ITEM1, ITEM2, NB_TEXTURE } // Définit les différentes textures du jeux
+ typedef void (*t_displayer)(void *data)
+ typedef void (*t_event)(void *data)

+ AGraphics                *aGraphics;
+ Nibbler                     *singleton;
+ std::vector<char>     _map
+ int                             _skin[SIZE_INIT];
+ t_displayer               _displayer[NB_STATE]             // Tableau de fonction d'affichage, une pour chaque état du jeu
+ t_event                     _eventManager[NB_STATE]    // Tableau de fonction d'event, une pour chaque état du jeu

*/


#endif //PROJECT_NIBBLER_HPP