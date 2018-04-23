#ifndef NIBBLER_GRAPHICS_HPP
#define NIBBLER_GRAPHICS_HPP

#include <iostream>


class Graphics {

public:
    Graphics(); // Canonical
    Graphics(Graphics const &copy); // Canonical
    ~Graphics(); // Canonical

    Graphics &operator=(Graphics const &copy); // Canonical

	void	helloWorld();

private:

};


#endif //NIBBLER_GRAPHICS_HPP
