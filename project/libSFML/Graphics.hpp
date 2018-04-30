
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

    void updateScreen();

    void putStrScreen(std::string str);

    void loadTexture(std::string path);

	void closeWindow();

    void cleanUp();

	std::vector<eEvent>& getEvent();

    unsigned char getChar();

private:
    sf::RenderWindow *_window;

};

extern "C" {
Graphics    *createGraphics();
void        deleteGraphics(Graphics *graphics);
}



#endif //NIBBLER_GRAPHICS_HPP