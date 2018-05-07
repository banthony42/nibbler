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
	return AGraphics::_eventList;
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
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return 0;
}

int Graphics::loopUpdate() {
	return !glfwWindowShouldClose(_window) && !this->_windowTerminated;
}

void Graphics::loadTexture(std::string path, int key) {
	GLuint texture;
	GLenum internFormat(0);
	GLenum format(0);
	unsigned char *data = nullptr;
	int width, height, bpp;

	glGenTextures(1, &texture); 										// Generation de l'iD
	glBindTexture(GL_TEXTURE_2D, texture);								// Verouillage, obligatoire pour modification du GLuint
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Les textures proche sont lissées
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Les textures éloignées sont lissées
	stbi_set_flip_vertically_on_load(true);								// Flipping the image, because openGL need it for .png
	if (key == FONT)													// Exception for flipping the image (because font = .tga)
		stbi_set_flip_vertically_on_load(false);						// Loading the image using stbi function
	 if (!(data = stbi_load(path.c_str(), &width, &height, &bpp, 0))) {
		 std::cout << "error: Failed to load texture" << std::endl; 	//TODO throw exception
		 return ;
	 }
	if (bpp == 3)														// Setting the nb of channel
		internFormat = GL_RGB;
	else if (bpp == 4)
		internFormat = GL_RGBA;
	else {
		std::cout << "error: internal format image is unknown" << std::endl; 	//TODO throw exception
		return ;
	}
	format = internFormat;												// The format order is always RGB or RGBA - stbi always convert BGR to RGB
	glTexImage2D(GL_TEXTURE_2D, 0, internFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);												// Liberation memoire
	glBindTexture(GL_TEXTURE_2D, 0);									// Deverouillage
	this->_textureList[key] = texture;									// Association de la texture a la key
}

void Graphics::putTexture(int key, int posX, int posY, int sizeX, int sizeY) {
	glBindTexture(GL_TEXTURE_2D, this->_textureList[key]);	// Verrouillage

	t_coord start;
	start.x = (((double)posX * (double)2) / (double)Nibbler::WINDOW_WIDTH) - 1.0;
	start.y = (((double)posY * (double)2) / (double)Nibbler::WINDOW_HEIGHT) - 1.0;

	t_coord end;
	end.x =  ((((double)posX + (double)sizeX) * (double)2) / (double)Nibbler::WINDOW_WIDTH) - 1.0;
	end.y =  ((((double)posY + (double)sizeY) * (double)2) / (double)Nibbler::WINDOW_HEIGHT) - 1.0;

	glBegin(GL_QUADS);
	glTexCoord2d(0,0);  glVertex2d(start.x, -end.y);	// bottom Left Corner
	glTexCoord2d(0,1);  glVertex2d(start.x, -start.y);	// upper Left Corner
	glTexCoord2d(1,1);  glVertex2d(end.x, -start.y);	// upper Right Corner
	glTexCoord2d(1,0);  glVertex2d(end.x, -end.y);		// bottom Right Corner
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);					// Deverrouillage
}

void Graphics::glPutChar(char const c, t_coord pos, t_coord sizeText, t_coord sizeFont) {
	t_coord c_start;
	t_coord c_end;

	t_coord start;
	t_coord end;

	if (c < '!' || c > '~')
		return ;

	// Calcul points d'affichage sur l'écran
	start.x = ((pos.x * (double)2) / (double)Nibbler::WINDOW_WIDTH) - 1.0;
	start.y = ((pos.y * (double)2) / (double)Nibbler::WINDOW_HEIGHT) - 1.0;
	end.x =  (((pos.x + sizeFont.x) * (double)2) / (double)Nibbler::WINDOW_WIDTH) - 1.0;
	end.y =  (((pos.y + sizeFont.y) * (double)2) / (double)Nibbler::WINDOW_HEIGHT) - 1.0;

	// Calcul points d'affichage de la texture
	c_start.x = ((double)FONT_START_X(c)) / sizeText.x;
	c_start.y =  1 - (((double)FONT_START_Y(c) / sizeText.y));
	c_end.x = c_start.x + ((double)CHAR_SIZE_X / sizeText.x);
	c_end.y = c_start.y - ((double)CHAR_SIZE_Y / sizeText.y);

	//Association des points de la texture avec ceux de l'écran
	glBindTexture(GL_TEXTURE_2D, this->_textureList[FONT]);
	glBegin(GL_QUADS);
	glTexCoord2d(c_start.x, c_start.y);	glVertex2d(start.x, -end.y);	// bottom Left Corner
	glTexCoord2d(c_start.x, c_end.y);	glVertex2d(start.x, -start.y);	// upper Left Corner
	glTexCoord2d(c_end.x, c_end.y);		glVertex2d(end.x, -start.y);	// upper Right Corner
	glTexCoord2d(c_end.x,c_start.y);	glVertex2d(end.x, -end.y);		// bottom Right Corner
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Graphics::putStrScreen(std::string str, int posX, int posY, float size) {
	GLint textSize[2]= {0};
	char const *tmp = str.c_str();
	t_coord pos;
	t_coord sizeText;

	if (!tmp || !str.size() || posX > Nibbler::WINDOW_WIDTH || posY > Nibbler::WINDOW_HEIGHT || posX < 0 || posY < 0)
		return ;
	if (size <= 0)
		size = 1;

	t_coord sizeFont;
	sizeFont.x = (CHAR_SIZE_X / 2.5) * size;
	sizeFont.y = (CHAR_SIZE_Y / 2.5) * size;

	pos.x = (double)posX;
	pos.y = (double)posY;
	glBindTexture(GL_TEXTURE_2D, this->_textureList[FONT]);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textSize[0]);	// Recuperation taille texture widht
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT,&textSize[1]);	// Recuperation taille texture height
	glBindTexture(GL_TEXTURE_2D, 0);
	sizeText.x = (double)textSize[0];
	sizeText.y = (double)textSize[1];

	while(*tmp) {
		if (*tmp != ' ')
			glPutChar(*tmp, pos, sizeText, sizeFont);
		pos.x += sizeFont.x;
		if (*tmp == '\n' || (pos.x + sizeFont.x) >= Nibbler::WINDOW_WIDTH) {
			pos.x = 0;
			if ((pos.y + sizeFont.y) < Nibbler::WINDOW_HEIGHT)
			pos.y += sizeFont.y;
		}
		tmp++;
	}
}

void Graphics::display() {
	glFlush();
	glfwSwapBuffers(this->_window);
}

void Graphics::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
