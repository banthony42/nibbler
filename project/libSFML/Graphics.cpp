/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graphics.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 16:51:09 by banthony          #+#    #+#             */
/*   Updated: 2018/05/07 16:51:09 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Graphics.hpp"
#include "SFML/include/SFML/Graphics/Rect.hpp"

/*
 * Declaration de la variable static
 * Permet la modification de l'_eventList dans la fonction
 * de callback et donc en dehors de l'instance de la Lib
 */
std::vector<eEvent> AGraphics::_eventList;

Graphics::Graphics() {
	this->_window = nullptr;
	this->_windowTerminated = true;
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

int Graphics::init(int windowWidth, int windowHeight, std::string windowName) {
	this->_window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), windowName + ": SFML");
	this->_window->setKeyRepeatEnabled(false);
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->_windowTerminated = false;
	return 1;
}

void Graphics::cleanUp() {
	if (!this->_windowTerminated) {
		if (this->_window) {
			this->_window->close();
			delete this->_window;
		}
		this->_windowTerminated = true;
	}
}

void Graphics::loadTexture(std::string path, int key) {
	sf::Texture texture;

	if (!texture.loadFromFile(path)) {
		std::cout << "error loading" << std::endl; // TODO exception here
		return;
	}
	texture.setSmooth(true);
	this->_textureList[key] = texture;
}

void Graphics::loadFontTexture(std::string path) {
	sf::Texture texture;

	if (!texture.loadFromFile(path)) {
		std::cout << "error loading" << std::endl; // TODO exception here
		return;
	}
	texture.setSmooth(true);
	this->_fontTexture = texture;
}


int Graphics::loopUpdate() {
	return  !this->_windowTerminated && this->_window->isOpen();
}

void Graphics::display() {
	for (int i = 0; i < this->_spriteList.size(); ++i) {
		this->_window->draw(this->_spriteList.at(i));
	}
	this->_spriteList.clear();
	this->_window->display();
}

void Graphics::clear() {
	this->_window->clear();    //TODO dont work properly
}

void Graphics::putCharScreen(char const c, t_coordd pos, t_coordd sizeFont) {
	sf::Sprite sprite;
	sf::Vector2i position;
	sf::Vector2i size;

	if (c < '!' || c > '~')
		return;

	// Il faut definir la zone de la texture que l'on souhaite afficher (rectangle)

	position.x = FONT_START_X(c);            // Position x du rectangle
	position.y = FONT_START_Y(c);            // Position y du rectangle
	size.x = CHAR_SIZE_X;                    // Taille x du rectangle
	size.y = CHAR_SIZE_Y;                    // Taille y du rectangle
	sf::IntRect textArea(position, size);    // Definition du rectangle

	sprite.setTexture(this->_fontTexture);                            // Selection de la texture a utiliser
	sprite.setPosition(sf::Vector2f(pos.x, pos.y));                            // Position d'affichage sur l'ecran
	sprite.setTextureRect(
			textArea);                                        // Definition de la zone de la texture a utiliser
	sprite.setScale(static_cast<float>(sizeFont.x / CHAR_SIZE_X),
					static_cast<double>(sizeFont.y / CHAR_SIZE_Y));    // Gestion de la taille de l'affichage
	this->_spriteList.push_back(sprite);                                    // Ajout du sprite a la liste pour affichage
}

void Graphics::putStrScreen(std::string str, int posX, int posY, float size) {
	char const *tmp = str.c_str();
	t_coordd pos = {};

	if (!tmp || !str.size() || posX > this->windowWidth || posY > this->windowHeight || posX < 0 || posY < 0)
		return;
	if (size <= 0)
		size = 1;

	t_coordd sizeFont = {};
	sizeFont.x = round(GET_SIZEFONT_X(size));
	sizeFont.y = round(GET_SIZEFONT_Y(size));

	pos.x = static_cast<double>(posX);
	pos.y = static_cast<double>(posY);

	while (*tmp) {
		if (*tmp != ' ')
			putCharScreen(*tmp, pos, sizeFont);
		pos.x += sizeFont.x;
		if (*tmp == '\n' || (pos.x + sizeFont.x) >= this->windowWidth) {
			pos.x = 0;
			if ((pos.y + sizeFont.y) < this->windowHeight)
				pos.y += sizeFont.y;
		}
		tmp++;
	}
}

void Graphics::putTexture(int key, int posX, int posY, int sizeX, int sizeY) {
	sf::Sprite sprite;
	sf::Vector2u vec;

	if (!key) {
		this->_window->clear(sf::Color(0, 0, 0));
		return;
	}
	vec = this->_textureList[key].getSize();
	sprite.setTexture(this->_textureList[key]);
	sprite.setPosition(sf::Vector2f(posX, posY));
	sprite.setScale(static_cast<double>(sizeX) / static_cast<double>(vec.x),
					static_cast<double>(sizeY) / static_cast<double>(vec.y));
	this->_spriteList.push_back(sprite);
}

std::vector<eEvent> &Graphics::getEvent() {
	AGraphics::clearEvent();
	sf::Event event;
	while (this->_window->pollEvent(event)) {
		if (event.type != sf::Event::KeyPressed)
			continue;
		std::cout << "event : " << event.key.code << std::endl;
		if (event.key.code == sf::Keyboard::Escape)
			AGraphics::addEvent(ECHAP);
		else if (event.key.code == sf::Keyboard::Up)
			AGraphics::addEvent(UP);
		else if (event.key.code == sf::Keyboard::Down)
			AGraphics::addEvent(DOWN);
		else if (event.key.code == sf::Keyboard::Left)
			AGraphics::addEvent(LEFT);
		else if (event.key.code == sf::Keyboard::Right)
			AGraphics::addEvent(RIGHT);
		else if (event.key.code == sf::Keyboard::Return)
			AGraphics::addEvent(ENTER);
	}
	return AGraphics::_eventList;
}

unsigned char Graphics::getChar() {
	return 0;
}


Graphics *createGraphics() {
	return new Graphics();
}

void deleteGraphics(Graphics *graphics) {
	delete graphics;
}
