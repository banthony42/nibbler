#ifndef PROJECT_SCENEMENU_HPP
#define PROJECT_SCENEMENU_HPP

#include "AScene.hpp"

class SceneMenu : public AScene {

public:
    SceneMenu(AGraphics *aGraphics);
    ~SceneMenu(); // Canonical

private:
    SceneMenu(); // Canonical
    SceneMenu(SceneMenu const &copy); // Canonical

    SceneMenu &operator=(SceneMenu const &copy); // Canonical

public:
    void eventHandler(std::vector<eEvent> eventList) override;

    void drawScene() override;

};


#endif //PROJECT_SCENEMENU_HPP