#include "../incl/nibbler.hpp"

Nibbler *Nibbler::_singleton = nullptr;
AGraphics *Nibbler::aGraphics = nullptr;

Nibbler::Nibbler() {

}

Nibbler::Nibbler(Nibbler const &copy) {
    *this = copy;
}

Nibbler::~Nibbler() {

}

Nibbler &Nibbler::operator=(Nibbler const &copy) {
    if (this != &copy) {
        // copy 
    }
    return *this;
}

Nibbler *Nibbler::getInstance() {
    if (!Nibbler::_singleton)
        Nibbler::_singleton = new Nibbler();
    return Nibbler::_singleton;
}

void Nibbler::run() {
    Nibbler::aGraphics->init();
    while (Nibbler::aGraphics->loopUpdate()) {

        // update
        // event
        // update nibbler
    }
    Nibbler::aGraphics->cleanUp();
}