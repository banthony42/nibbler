#ifndef NIBBLER_GRAPHICS_HPP
#define NIBBLER_GRAPHICS_HPP

#include <GLUT/glut.h>


class Graphics {

public:
    Graphics(); // Canonical
    Graphics(Graphics const &copy); // Canonical
    ~Graphics(); // Canonical

    Graphics &operator=(Graphics const &copy); // Canonical

    void helloworld(int argc, char **argv);

private:

};


#endif //NIBBLER_GRAPHICS_HPP