#include "Graphics.hpp"

/*
 * Declaration de la variable static
 * Permet la modification de l'_eventList dans la fonction
 * de callback et donc en dehors de l'instance de la Lib
 */
std::vector<eEvent> AGraphics::_eventList;

Graphics::Graphics() {
    this->_window = nullptr;
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

int Graphics::init(int windowWidth, int windowHeight) {
    this->_window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "SFML works!");
    this->_window->setKeyRepeatEnabled(false);
    return 1;
}

int Graphics::loopUpdate() {
//    this->getEvent();
    this->_window->clear();
    this->_window->display();
    return this->_window->isOpen();
}

void Graphics::updateScreen() {

}

void Graphics::putStrScreen(std::string str) {

}

void Graphics::loadTexture(std::string path, int key) {

}

void Graphics::closeWindow() {
//    std::cout << "Should close and terminate" << std::endl;
	this->_window->close();
    this->cleanUp();
}

void Graphics::cleanUp() {
//    if (this->_window) // TODO THE DELETE MAKE A SEGFAULT
//        delete this->_window;	//TODO verifier utilite, un simple _window->close() suffit a terminer le prog
}

std::vector<eEvent>& Graphics::getEvent() {
    AGraphics::clearEvent();
    sf::Event event;
    while (this->_window->pollEvent(event))
    {
        if (event.type != sf::Event::KeyPressed)
            continue ;
        std::cout << "event : " << event.key.code << std::endl;
        if (event.key.code == sf::Keyboard::Escape)
            AGraphics::addEvent(ECHAP);
        else if (event.key.code == sf::Keyboard::Up)
            AGraphics::addEvent(UP);
        else if (event.key.code == sf::Keyboard::Down)
            AGraphics::addEvent(DOWN);
        else if (event.key.code == sf::Keyboard::Left)
            AGraphics::addEvent(LEFT);
        else if (event.key.code == sf::Keyboard::Right)
            AGraphics::addEvent(RIGHT);
        else if (event.key.code == sf::Keyboard::Return)
            AGraphics::addEvent(ENTER);
    }
    return this->_eventList;
}

unsigned char Graphics::getChar() {
    return 0;
}

Graphics *createGraphics() {
    return new Graphics();
}

void deleteGraphics(Graphics *graphics) {
    delete graphics;
}
