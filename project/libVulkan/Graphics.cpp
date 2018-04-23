#include "Graphics.hpp"

Graphics::Graphics() {

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

void	Graphics::helloWorld(void) {
// vulkan
	std::cout << "Hello Vulkan" << std::endl;
}
