/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graphics.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:52:09 by banthony          #+#    #+#             */
/*   Updated: 2018/04/26 17:52:09 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_GRAPHICS_HPP
#define NIBBLER_GRAPHICS_HPP

// TODO Changer la maniere de compiler pour pouvoir inclure directement "AGraphics.hpp"

#include <iostream>
#include <GLUT/glut.h>
#include <GLFW/glfw3.h>
#include "../incl/AGraphics.hpp"

class Graphics : public AGraphics {

public:
    Graphics(); // Canonical
    Graphics(Graphics const &copy); // Canonical
    ~Graphics(); // Canonical

    Graphics &operator=(Graphics const &copy); // Canonical

    void helloWorld(void);

    int init();

    int loopUpdate();

    void updateScreen();

    void putStrScreen(std::string str);

    void loadTexture(std::string path);

    void cleanUp();

    void getEvent();

    unsigned char getChar();

private:
	GLFWwindow* _window;
};

extern "C" {
Graphics    *createGraphics();
void        deleteGraphics(Graphics *graphics);
}



#endif //NIBBLER_GRAPHICS_HPP