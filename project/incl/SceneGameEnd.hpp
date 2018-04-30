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

class SceneGameEnd : public AScene {

public:
    SceneGameEnd(AGraphics *aGraphics);
    ~SceneGameEnd(); // Canonical

	void eventHandler(std::vector<eEvent> eventList) override;
	void drawScene() override;

private:
    SceneGameEnd(); // Canonical
    SceneGameEnd(SceneGameEnd const &copy); // Canonical
    SceneGameEnd &operator=(SceneGameEnd const &copy);// Canonical
};


#endif //PROJECT_SCENEGAMEEND_HPP