/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graphics.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:50:50 by banthony          #+#    #+#             */
/*   Updated: 2018/04/26 17:50:50 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Graphics.hpp"
#include "../incl/Nibbler.hpp"

/*
 * Declaration de la variable static
 * Permet la modification de l'_eventList dans la fonction
 * de callback et donc en dehors de l'instance de la Lib
 */
std::vector<eEvent> AGraphics::_eventList;

Graphics::Graphics() {
}

Graphics::Graphics(Graphics const &copy) {
	*this = copy;
}

Graphics::~Graphics() {

}

Graphics &Graphics::operator=(Graphics const &copy) {
	if (this != &copy) {
		// copy
	}
	return *this;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	std::cout << "event : " << key << std::endl;

	AGraphics::clearEvent();
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) // TODO mettre des else if
		AGraphics::addEvent(ECHAP);
	else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		AGraphics::addEvent(UP);
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		AGraphics::addEvent(DOWN);
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		AGraphics::addEvent(LEFT);
	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		AGraphics::addEvent(RIGHT);
	else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		AGraphics::addEvent(ENTER);
}

std::vector<eEvent> &Graphics::getEvent() {
	glfwPollEvents();	// best choice when rendering continually
	return Graphics::_eventList;
}

unsigned char Graphics::getChar() {
	return 0;
}

int Graphics::init(int windowWidth, int windowHeight) {
	if (!glfwInit()) {
		std::cout << "error: init glfw!" << std::endl;
		// TODO throw exception
		return -1;
	}
	// On s'assure d'etre en context OPENGL pour pouvoir utiliser les fonction openGL (Useless si val par defaut)
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	if (!(_window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL", nullptr, nullptr))) {
		std::cout << "error: create window glfw!" << std::endl;
		// TODO throw exception
		glfwTerminate();
		return -1;
	}
	//Before you can make OpenGL or OpenGL ES calls, you need to have a current context of the correct type
	glfwMakeContextCurrent(_window);

	// Set callback
	glfwSetKeyCallback(_window, key_callback);
    this->_windowTerminated = false;

	glEnable(GL_TEXTURE_2D);
	return 0;
}

int Graphics::loopUpdate() {
	return !glfwWindowShouldClose(_window) && !this->_windowTerminated;
}

void Graphics::putStrScreen(std::string str) {

}

void Graphics::loadTexture(std::string path, int key) {
	GLuint texture;
	GLenum internFormat(0);
	GLenum format(0);
	unsigned char *data = nullptr;
	int width, height, bpp;

	//Generation de l'iD
	glGenTextures(1, &texture);

	//Verouillage, obligatoire pour modification du GLuint
	glBindTexture(GL_TEXTURE_2D, texture);

	//Gestion des filtres sur la texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// load the texture with the image loader stbi
	 if (!(data = stbi_load(path.c_str(), &width, &height, &bpp, 0))) {
		 std::cout << "error: Failed to load texture" << std::endl; //TODO throw exception
		 return ;
	 }
	if (bpp == 3)
		internFormat = GL_RGB;
	else if (bpp == 4)
		internFormat = GL_RGBA;
	else {
		std::cout << "error: internal format image is unknown" << std::endl; 	//TODO throw exception
		return ;
	}
	// The format order is always RGB or RGBA - stbi always convert BGR to RGB
	format = internFormat;
	glTexImage2D(GL_TEXTURE_2D, 0, internFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	//Deverouillage
	glBindTexture(GL_TEXTURE_2D, 0);
	this->_textureList[key] = texture;
}

void Graphics::putTexture(int key, int posX, int posY, int sizeX, int sizeY) {

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	glBindTexture(GL_TEXTURE_2D, this->_textureList[key]);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);  glVertex2d(-1,-1);
	glTexCoord2d(0,1);  glVertex2d(-1,1);
	glTexCoord2d(1,1);  glVertex2d(1,1);
	glTexCoord2d(1,0);  glVertex2d(1,-1);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Graphics::display() {
	glFlush();
	glfwSwapBuffers(this->_window);
}

void Graphics::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::closeWindow() {
	glfwDestroyWindow(this->_window);
	this->cleanUp();
}

void Graphics::cleanUp() {
    if (!this->_windowTerminated) {
        std::cout << "terminate" << std::endl;
        glfwTerminate();
        this->_windowTerminated = true;
    }
}

Graphics *createGraphics() {
	return new Graphics();
}

void deleteGraphics(Graphics *graphics) {
	delete graphics;
}
