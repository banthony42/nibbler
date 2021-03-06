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

std::map<int, eEvent> Graphics::_eventLibMap;

Graphics::Graphics() {
	this->_windowTerminated = true;
	Graphics::_eventLibMap[GLFW_KEY_ESCAPE] = ECHAP;
	Graphics::_eventLibMap[GLFW_KEY_UP] = UP;
	Graphics::_eventLibMap[GLFW_KEY_DOWN] = DOWN;
	Graphics::_eventLibMap[GLFW_KEY_LEFT] = LEFT;
	Graphics::_eventLibMap[GLFW_KEY_RIGHT] = RIGHT;
	Graphics::_eventLibMap[GLFW_KEY_ENTER] = ENTER;
	Graphics::_eventLibMap[GLFW_KEY_F1] = F1;
	Graphics::_eventLibMap[GLFW_KEY_F2] = F2;
	Graphics::_eventLibMap[GLFW_KEY_F3] = F3;
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
	if (action == GLFW_PRESS) {
		AGraphics::addEvent(((Graphics::_eventLibMap[key])));
	}
	static_cast<void>(window);
	static_cast<void>(scancode);
	static_cast<void>(mods);

}

std::vector<eEvent> &Graphics::getEvent() {
	if (this->_windowTerminated) {
		return AGraphics::getEventList();
	}
	AGraphics::clearEvent();
	glfwPollEvents();
	return AGraphics::getEventList();
}

unsigned char Graphics::getChar() {
	if (this->_windowTerminated) {
		return 0;
	}
	return 0;
}

void Graphics::init(int windowWidth, int windowHeight, std::string windowName) {
	if (!glfwInit()) {
		throw std::runtime_error(std::string("error: failed to init glfw"));
	}
	// On s'assure d'etre en context OPENGL pour pouvoir utiliser les fonction openGL (Useless si val par defaut)
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	if (!(_window = glfwCreateWindow(windowWidth, windowHeight, std::string(windowName + ": OpenGL").c_str(), nullptr,
									 nullptr))) {
		glfwTerminate();
		throw std::runtime_error(std::string("error: create window glfw"));
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
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
}

void Graphics::loadTexture(std::string path, int key) {
	GLuint texture;
	GLenum internFormat(0);
	GLenum format(0);
	unsigned char *data = nullptr;
	int width, height, bpp;

	glGenTextures(1, &texture);                                        // Generation de l'iD
	glBindTexture(GL_TEXTURE_2D,
				  texture);                                // Verouillage, obligatoire pour modification du GLuint
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // Les textures proche sont lissées
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // Les textures éloignées sont lissées
	stbi_set_flip_vertically_on_load(
			true);                                // Flipping the image, because openGL need it for .png
	if (!(data = stbi_load(path.c_str(), &width, &height, &bpp, 0))) {
		throw std::runtime_error(std::string("error: Failed to load texture : ") + path);
	}
	if (bpp == 3)                                                        // Setting the nb of channel
		internFormat = GL_RGB;
	else if (bpp == 4)
		internFormat = GL_RGBA;
	else {
		throw std::runtime_error(std::string("error: Internal format image is unknown : ") + path);
	}
	format = internFormat;                                                // The format order is always RGB or RGBA - stbi always convert BGR to RGB
	glTexImage2D(GL_TEXTURE_2D, 0, internFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);                                                // Liberation memoire
	glBindTexture(GL_TEXTURE_2D, 0);                                    // Deverouillage
	this->_textureList[key] = texture;                                    // Association de la texture a la key
}

void Graphics::loadFontTexture(std::string path) {
	GLuint texture;
	GLenum internFormat(0);
	GLenum format(0);
	unsigned char *data = nullptr;
	int width, height, bpp;

	glGenTextures(1, &texture);                                        // Generation de l'iD
	glBindTexture(GL_TEXTURE_2D,
				  texture);                                // Verouillage, obligatoire pour modification du GLuint
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // Les textures proche sont lissées
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // Les textures éloignées sont lissées
	stbi_set_flip_vertically_on_load(false);                                // No need to flip for .tga
	if (!(data = stbi_load(path.c_str(), &width, &height, &bpp, 0))) {
		throw std::runtime_error("error: failed to load texture");
	}
	if (bpp == 3)                                                        // Setting the nb of channel
		internFormat = GL_RGB;
	else if (bpp == 4)
		internFormat = GL_RGBA;
	else {
		throw std::runtime_error("error: internal format image is unknown");
	}
	format = internFormat;                                                // The format order is always RGB or RGBA - stbi always convert BGR to RGB
	glTexImage2D(GL_TEXTURE_2D, 0, internFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);                                                // Liberation memoire
	glBindTexture(GL_TEXTURE_2D, 0);                                    // Deverouillage
	this->_fontTexture = texture;                                    // Association de la texture font
}

int Graphics::loopUpdate() {
	return !this->_windowTerminated && !glfwWindowShouldClose(_window);
}

void Graphics::putTexture(int key, int posX, int posY, int sizeX, int sizeY) {
	if (this->_windowTerminated) {
		return;
	}
	glBindTexture(GL_TEXTURE_2D, this->_textureList[key]);    // Verrouillage

	if (!key)
		return;
	t_coordd start = {};
	start.x = ((posX * 2.0) / this->windowWidth) - 1.0;
	start.y = ((posY * 2.0) / this->windowHeight) - 1.0;

	t_coordd end = {};
	end.x = (((posX + sizeX) * 2.0) / this->windowWidth) - 1.0;
	end.y = (((posY + sizeY) * 2.0) / this->windowHeight) - 1.0;

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex2d(start.x, -end.y);    // bottom Left Corner
	glTexCoord2d(0, 1);
	glVertex2d(start.x, -start.y);    // upper Left Corner
	glTexCoord2d(1, 1);
	glVertex2d(end.x, -start.y);    // upper Right Corner
	glTexCoord2d(1, 0);
	glVertex2d(end.x, -end.y);        // bottom Right Corner
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);                    // Deverrouillage
}

void Graphics::putCharScreen(char const c, t_coordd pos, t_coordd sizeFont) {
	if (this->_windowTerminated) {
		return;
	}
	GLint textSize[2] = {0};
	t_coordd sizeText = {};
	t_coordd c_start = {};
	t_coordd c_end = {};

	t_coordd start = {};
	t_coordd end = {};

	if (c < '!' || c > '~')
		return;

	glBindTexture(GL_TEXTURE_2D, this->_fontTexture);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textSize[0]);    // Recuperation taille texture widht
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT,
							 &textSize[1]);    // Recuperation taille texture height
	glBindTexture(GL_TEXTURE_2D, 0);
	sizeText.x = static_cast<double>(textSize[0]);
	sizeText.y = static_cast<double>(textSize[1]);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Calcul points d'affichage sur l'écran
	start.x = ((pos.x * 2.0) / static_cast<double>(this->windowWidth)) - 1.0;
	start.y = ((pos.y * 2.0) / static_cast<double>(this->windowHeight)) - 1.0;
	end.x = (((pos.x + sizeFont.x) * 2.0) / static_cast<double>(this->windowWidth)) - 1.0;
	end.y = (((pos.y + sizeFont.y) * 2.0) / static_cast<double>(this->windowHeight)) - 1.0;

	// Calcul points d'affichage de la texture
	c_start.x = static_cast<double>(FONT_START_X(c)) / sizeText.x;
	c_start.y = 1 - (static_cast<double>(FONT_START_Y(c)) / sizeText.y);
	c_end.x = c_start.x + (static_cast<double>(CHAR_SIZE_X) / sizeText.x);
	c_end.y = c_start.y - (static_cast<double>(CHAR_SIZE_Y) / sizeText.y);

	//Association des points de la texture avec ceux de l'écran
	glBindTexture(GL_TEXTURE_2D, this->_fontTexture);
	glBegin(GL_QUADS);
	glTexCoord2d(c_start.x, c_start.y);
	glVertex2d(start.x, -end.y);    // bottom Left Corner
	glTexCoord2d(c_start.x, c_end.y);
	glVertex2d(start.x, -start.y);    // upper Left Corner
	glTexCoord2d(c_end.x, c_end.y);
	glVertex2d(end.x, -start.y);    // upper Right Corner
	glTexCoord2d(c_end.x, c_start.y);
	glVertex2d(end.x, -end.y);        // bottom Right Corner
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Graphics::putStrScreen(std::string str, int posX, int posY, float size) {
	if (this->_windowTerminated) {
		return;
	}
	char const *tmp = str.c_str();
	t_coordd pos{};

	if (!tmp || !str.size() || posX > this->windowWidth || posY > this->windowHeight || posX < 0 || posY < 0)
		return;
	if (size <= 0)
		size = 1;

	t_coordd sizeFont{};
	sizeFont.x = round(GET_SIZEFONT_X(size));
	sizeFont.y = round(GET_SIZEFONT_Y(size));

	pos.x = static_cast<double>(posX);
	pos.y = static_cast<double>(posY);

	while (*tmp) {
		if (*tmp != ' ')
			putCharScreen(*tmp, pos, sizeFont);
		pos.x += sizeFont.x;
		if (*tmp == '\n' || (pos.x + sizeFont.x) >= this->windowWidth) {
			pos.x = static_cast<double>(posX);
			if ((pos.y + sizeFont.y) < this->windowHeight)
				pos.y += sizeFont.y;
		}
		tmp++;
	}
}

void Graphics::display() {
	if (this->_windowTerminated) {
		return;
	}
	glFlush();
	glfwSwapBuffers(this->_window);
}

void Graphics::clear() {
	if (this->_windowTerminated) {
		return;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::cleanUp() {
	if (!this->_windowTerminated) {
		glfwDestroyWindow(this->_window);
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