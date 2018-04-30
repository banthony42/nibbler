#ifndef PROJECT_SCENESKIN_HPP
#define PROJECT_SCENESKIN_HPP

#include "AScene.hpp"

class SceneSkin : public AScene {

public:
    SceneSkin(AGraphics *aGraphics);
    ~SceneSkin(); // Canonical

private:
    SceneSkin(); // Canonical
    SceneSkin(SceneSkin const &copy); // Canonical
    SceneSkin &operator=(SceneSkin const &copy);

//    void selectSkinScreen(snakeData *snakeData); // TODO implement this

public:
    void eventHandler(std::vector<eEvent> eventList) override;
    void drawScene() override;
    // Canonical

};


#endif //PROJECT_SCENESKIN_HPP