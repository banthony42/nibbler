
#ifndef NIBBLER_GRAPHICS_HPP
#define NIBBLER_GRAPHICS_HPP

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../incl/AGraphics.hpp"

class Graphics : public AGraphics {

public:
    Graphics(); // Canonical
    Graphics(Graphics const &copy); // Canonical
    ~Graphics(); // Canonical

    Graphics &operator=(Graphics const &copy); // Canonical

    int init(int windowWidth, int windowHeight);

    int loopUpdate();

    void display();

    void clear();

    void putStrScreen(std::string str, int posX, int posY);

    void loadTexture(std::string path, int key);

	void closeWindow();

    void cleanUp();

	std::vector<eEvent>& getEvent();

    unsigned char getChar();

    void putTexture(int key, int posX, int posY, int sizeX, int sizeY);


private:
    sf::RenderWindow *_window;
    std::map<int, sf::Texture> _textureList;
    std::vector<sf::Sprite> _spriteList;

};

extern "C" {
Graphics    *createGraphics();
void        deleteGraphics(Graphics *graphics);
}



#endif //NIBBLER_GRAPHICS_HPP