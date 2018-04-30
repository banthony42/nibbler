#include "../incl/SceneSkin.hpp"

SceneSkin::SceneSkin() {

}

SceneSkin::SceneSkin(SceneSkin const &copy) {
    *this = copy;
}

SceneSkin::~SceneSkin() {

}

SceneSkin &SceneSkin::operator=(SceneSkin const &copy) {
    if (this != &copy) {
        // copy 
    }
    return *this;
}

SceneSkin::SceneSkin(AGraphics *aGraphics) {
    this->aGraphics = aGraphics;
}

void SceneSkin::eventHandler(std::vector<eEvent> eventList) {
    (void)eventList;
}

void SceneSkin::drawScene() {

}

