#ifndef NIBBLER_GRAPHICS_HPP
#define NIBBLER_GRAPHICS_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <vulkan/vulkan.h>

#include <iostream>
#include "../incl/IGraphics.hpp"


class Graphics : public IGraphics {

public:
    Graphics(); // Canonical
    Graphics(Graphics const &copy); // Canonical
    ~Graphics(); // Canonical

    Graphics &operator=(Graphics const &copy); // Canonical

	void	helloWorld();

private:

};

extern "C" {
    Graphics    *createGraphics();
    void        deleteGraphics(Graphics *graphics);

    void externHelloWorld(Graphics &graphics);
}


#endif //NIBBLER_GRAPHICS_HPP
