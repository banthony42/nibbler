#include "../incl/SceneGame.hpp"

SceneGame::SceneGame() {

}

SceneGame::SceneGame(SceneGame const &copy) {
    *this = copy;
}

SceneGame::~SceneGame() {

}

SceneGame &SceneGame::operator=(SceneGame const &copy) {
    if (this != &copy) {
        // copy 
    }
    return *this;
}

void SceneGame::eventHandler(std::vector<eEvent> eventList) {
    (void)eventList;
}

void SceneGame::drawScene() {

}

SceneGame::SceneGame(AGraphics *aGraphics) {
    this->aGraphics = aGraphics;
}
