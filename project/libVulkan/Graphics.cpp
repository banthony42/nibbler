#include "Graphics.hpp"

/*
 * Declaration de la variable static
 * Permet la modification de l'_eventList dans la fonction
 * de callback et donc en dehors de l'instance de la Lib
 */
std::vector<eEvent> AGraphics::_eventList;

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

 int Graphics::loopUpdate() {
//     std::cout << "test" << std::endl;
//     this->getEvent(); // useless
     return !glfwWindowShouldClose(this->_window) && !this->_windowTerminated;
}

void Graphics::updateScreen() {
//    std::cout << "test" << std::endl;
}

void Graphics::putStrScreen(std::string str) {

}

void Graphics::loadTexture(std::string path) {

}

void Graphics::closeWindow() { // TODO soit on garde closeWindow ET cleanUp soit on garde que cleanUp (->UML)
//	std::cout << "Should close and terminate" << std::endl;
    this->cleanUp();
}

void Graphics::cleanUp() {
    if (!this->_windowTerminated) {
        std::cout << "terminate" << std::endl;
        glfwTerminate();    //All windows remaining when glfwTerminate is called are destroyed as well.
        this->_windowTerminated = true;
    }
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	std::cout << "key callback : " << key << std::endl;

	AGraphics::clearEvent();
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		AGraphics::addEvent(ECHAP);
	else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		AGraphics::addEvent(UP);
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		AGraphics::addEvent(DOWN);
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		AGraphics::addEvent(LEFT);
	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		AGraphics::addEvent(RIGHT);
	else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		AGraphics::addEvent(ENTER);
}

std::vector<eEvent> &Graphics::getEvent() {
	glfwPollEvents();
	return Graphics::_eventList;
}

unsigned char Graphics::getChar() {
	return 0;
}

/*
 *  Hint = allusion (litteralement)
 *  Ce sont des options que l'on peut activer ou pas pour la prochaine fenetre qui sera creer
 *  Exemple:
 *  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);	// Desactive l'option resize de la fenetre
 */

int Graphics::init(int windowWidth, int windowHeight) {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);	// Desactive la creation de context, Vulkan dispose de son propre API
	_window = glfwCreateWindow(windowWidth, windowHeight, "Vulkan", nullptr, nullptr);
	glfwSetKeyCallback(_window, key_callback);
    this->_windowTerminated = false;
	return (1);
}

/********* EXTERN "C" DEFINITION *********/

Graphics    *createGraphics() {
    return new Graphics();
}


















