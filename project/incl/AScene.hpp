#ifndef PROJECT_ASCENE_HPP
#define PROJECT_ASCENE_HPP


#include "AGraphics.hpp"

class AScene {


public:
    virtual void eventHandler(std::vector<eEvent> eventList) = 0;
    virtual void drawScene() = 0;

protected:
    AGraphics *aGraphics;

};


#endif //PROJECT_ASCENE_HPP
