#include "../incl/SceneGameEnd.hpp"

SceneGameEnd::SceneGameEnd() {

}

SceneGameEnd::SceneGameEnd(SceneGameEnd const &copy) {
    *this = copy;
}

SceneGameEnd::~SceneGameEnd() {

}

SceneGameEnd::SceneGameEnd(AGraphics *aGraphics) {
    this->aGraphics = aGraphics;
}

SceneGameEnd &SceneGameEnd::operator=(SceneGameEnd const &copy) {
    if (this != &copy) {
        // copy 
    }
    return *this;
}

void SceneGameEnd::eventHandler(std::vector<eEvent> eventList) {
    (void)eventList;
}

void SceneGameEnd::drawScene() {

}

