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

#ifndef PROJECT_NIBBLER_HPP
#define PROJECT_NIBBLER_HPP

#include <iostream>
#include <map>
#include <dlfcn.h>
#include "AGraphics.hpp"

enum eTexture {
    TEXTURE_VOID,
    MENU_BCKG,
    GAME_BCKG,
    SCORE_BCKG,
    ITEM1,
    ITEM2,
    NB_TEXTURE
};

enum eStateGame {
    STATE_VOID,
    MENU,
    GAME,
    SKIN,
    GAME_END,
    NB_STATE
};


class Nibbler {

typedef void (*t_displayer)(void);
typedef void (*t_event)(void);

public:
    static AGraphics *aGraphics;

    static Nibbler *getInstance();
    void run();

private:
    static Nibbler *_singleton;
    std::map<eStateGame, t_displayer> _dislpayer;
    std::map<eStateGame, t_event> _eventHandler;

//    t_displayer _displayer[NB_STATE];

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