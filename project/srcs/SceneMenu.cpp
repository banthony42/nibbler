#include "../incl/SceneMenu.hpp"

SceneMenu::SceneMenu() {

}

SceneMenu::SceneMenu(SceneMenu const &copy) {
    *this = copy;
}

SceneMenu::~SceneMenu() {

}

SceneMenu::SceneMenu(AGraphics *aGraphics) {
    this->aGraphics = aGraphics;
}

SceneMenu &SceneMenu::operator=(SceneMenu const &copy) {
    if (this != &copy) {
        // copy 
    }
    return *this;
}

void SceneMenu::eventHandler(std::vector<eEvent> eventList) {
    (void)eventList;
}

void SceneMenu::drawScene() {

}
