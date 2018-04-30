#ifndef PROJECT_SCENEGAME_HPP
#define PROJECT_SCENEGAME_HPP

#include "AScene.hpp"

class SceneGame : public AScene {

public:
    SceneGame(AGraphics *aGraphics);
    ~SceneGame(); // Canonical


private:
    SceneGame(); // Canonical
    SceneGame(SceneGame const &copy); // Canonical
    SceneGame &operator=(SceneGame const &copy); // Canonical

public:
    void eventHandler(std::vector<eEvent> eventList) override;
    void drawScene() override;


};


#endif //PROJECT_SCENEGAME_HPP