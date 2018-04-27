#ifndef NIBBLER_GRAPHICS_HPP
#define NIBBLER_GRAPHICS_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../incl/AGraphics.hpp"

class Graphics : public AGraphics {

public:
    Graphics(); // Canonical
    Graphics(Graphics const &copy); // Canonical
    ~Graphics(); // Canonical

    Graphics &operator=(Graphics const &copy); // Canonical

    void helloWorld();

    int init();

    int loopUpdate();

    void updateScreen();

    void putStrScreen(std::string str);

    void loadTexture(std::string path);

    void cleanUp();

	std::vector<eEvent>& getEvent();

    unsigned char getChar();

private:
    sf::RenderWindow *_window;

};

extern "C" {
Graphics    *createGraphics();
void        deleteGraphics(Graphics *graphics);

void        externHelloWorld(Graphics &graphics);
}



#endif //NIBBLER_GRAPHICS_HPP