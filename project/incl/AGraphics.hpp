#ifndef NIBBLER_IGRAPHICS_HPP
#define NIBBLER_IGRAPHICS_HPP

#include <string>
#include <vector>

enum eEvent {
    ECHAP,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER,
    NB_EVENT
};

class AGraphics {

public:
    virtual void helloWorld() = 0;
    virtual int init() = 0;
    virtual int loopUpdate() = 0;
    virtual void updateScreen() = 0;
    virtual void putStrScreen(std::string str) = 0;
    virtual void loadTexture(std::string path) = 0;
    virtual void cleanUp() = 0;
    virtual void getEvent() = 0;
    virtual unsigned char getChar() = 0;

//    virtual void putPixel() = 0;

    /***** Méthodes Abstraite *****/
//    + init (void) = 0 : return (int)
//    + refreshScreen (void) = 0 : return (void)
//    + updateScreen (void) = 0 : return (void)
//    + putstrScreen (std::string) = 0 : return (void)
//    + loadTexture (std::string) = 0 : return (void)
//    + putPixel ( ... ) = 0 : return (void)    // Ou equivalent, fonction de dessin
//    + getEvent ( ... ) = 0 : return ( ... )    // Ou equivalent, fonction de recuperation des event

protected:
    std::vector<eEvent> _eventList;


};

#endif //NIBBLER_IGRAPHICS_HPP
