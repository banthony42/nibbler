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

#include "AScene.hpp"

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

};


#endif //PROJECT_SCENESKIN_HPP