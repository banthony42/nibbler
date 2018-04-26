#ifndef NIBBLER_GRAPHICS_HPP
#define NIBBLER_GRAPHICS_HPP

#include <GLUT/glut.h>
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

    void getEvent();

    unsigned char getChar();

private:

};

extern "C" {
Graphics    *createGraphics();
void        deleteGraphics(Graphics *graphics);

void        externHelloWorld(Graphics &graphics);
}



#endif //NIBBLER_GRAPHICS_HPP