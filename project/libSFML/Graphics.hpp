#ifndef NIBBLER_GRAPHICS_HPP
#define NIBBLER_GRAPHICS_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../incl/IGraphics.hpp"

class Graphics : public IGraphics {

public:
    Graphics(); // Canonical
    Graphics(Graphics const &copy); // Canonical
    ~Graphics(); // Canonical

    Graphics &operator=(Graphics const &copy); // Canonical

    void helloWorld();

private:

};

extern "C" {
Graphics    *createGraphics();
void        deleteGraphics(Graphics *graphics);

void        externHelloWorld(Graphics &graphics);
}



#endif //NIBBLER_GRAPHICS_HPP