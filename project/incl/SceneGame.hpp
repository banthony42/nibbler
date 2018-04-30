/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SceneGame.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:46:35 by banthony          #+#    #+#             */
/*   Updated: 2018/04/30 16:46:35 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENEGAME_HPP
#define SCENEGAME_HPP

#include "AScene.hpp"
#include "Entity.hpp"

class SceneGame : public AScene {

public:
    SceneGame(AGraphics *aGraphics);
    ~SceneGame(); // Canonical

	void eventHandler(std::vector<eEvent> eventList) override;

	void drawScene() override;

private:
    SceneGame(); // Canonical
    SceneGame(SceneGame const &copy); // Canonical
    SceneGame &operator=(SceneGame const &copy); // Canonical

    void moveSnake();

	static const int	_N_SECTX = 16;	//TODO Voir si on calcul ces valeurs en fonctions de la taille de la fenetre
	static const int	_N_SECTY = 16;
	Snake				_snake;
	Food				_food;			//TODO: Definir le nb de food max sur scene, dans ce cas: _food[MAX_FOOD]
};


#endif //PROJECT_SCENEGAME_HPP