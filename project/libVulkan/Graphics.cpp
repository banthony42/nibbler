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
	std::cout << "Hello Vulkan" << std::endl;

	//Init
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	this->_window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::cout << extensionCount << " extensions supported" << std::endl;

	glm::mat4 matrix;
	glm::vec4 vec;
	auto test = matrix * vec;

	//Mainloop
    while(!glfwWindowShouldClose(this->_window)) {
		glfwPollEvents();
	}

	//Cleanup
	glfwDestroyWindow(this->_window);
	glfwTerminate();
}

/*
 *  Hint = allusion (litteralement)
 *  Ce sont des options que l'on peut activer ou pas pour la prochaine fenetre qui sera creer
 *  Exemple:
 *  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);	// Desactive l'option resize de la fenetre
 */

int Graphics::init() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);	// Desactive la creation de context, Vulkan dispose de son propre API
    _window = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);
    return (1);
}

 int Graphics::loopUpdate() {
     this->getEvent();
     return !glfwWindowShouldClose(_window);
}

void Graphics::updateScreen() {
    std::cout << "test" << std::endl;
}

void Graphics::putStrScreen(std::string str) {

}

void Graphics::loadTexture(std::string path) {

}

void Graphics::cleanUp() {
//    glfwDestroyWindow(_window);
    glfwTerminate();	//All windows remaining when glfwTerminate is called are destroyed as well.
}

void Graphics::getEvent() {
    glfwPollEvents();
    // TODO add the values in the vector
}

unsigned char Graphics::getChar() {
    return 0;
}

/********* EXTERN "C" DEFINITION *********/

Graphics    *createGraphics() {
    return new Graphics();
}


















