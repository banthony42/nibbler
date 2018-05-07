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

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

// TODO Changer la maniere de compiler pour pouvoir inclure directement "AGraphics.hpp"

#include <iostream>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLUT/glut.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../incl/stb_image.h"
#include "../incl/Nibbler.hpp"
#include "../incl/SceneGame.hpp"
#include "../incl/AGraphics.hpp"

#define NB_CHAR 16

#define FONT_START_X(c) (512 - (CHAR_SIZE_X * (NB_CHAR - ((c - '!') % NB_CHAR))))
#define FONT_START_Y(c) (512 - (CHAR_SIZE_Y * (1 + ((c - '!') / NB_CHAR))))

class Graphics : public AGraphics {

public:
    Graphics(); // Canonical
    Graphics(Graphics const &copy); // Canonical
    ~Graphics(); // Canonical

    Graphics &operator=(Graphics const &copy); // Canonical

    int init(int windowWidth, int windowHeight);

    int loopUpdate();

    void updateScreen();

    void putStrScreen(std::string str, int posX, int poxY, float size);

    void loadTexture(std::string path, int key);

	void closeWindow();

    void cleanUp();

    std::vector<eEvent>& getEvent();

    unsigned char getChar();

	void putTexture(int key, int posX, int posY, int sizeX, int sizeY);

	void display();

	void clear();

private:
	std::map<int, GLuint>	_textureList;
	bool					_windowTerminated;
	GLFWwindow*				_window;

	void glputChar(char const c, t_coord pos, t_coord sizeText, t_coord sizeFont);
};

extern "C" {
    Graphics    *createGraphics();
    void        deleteGraphics(Graphics *graphics);
}



#endif //NIBBLER_GRAPHICS_HPP