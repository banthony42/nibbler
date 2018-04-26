
#include "Graphics.hpp"

Graphics::Graphics() {

}

Graphics::Graphics(Graphics const &copy) {
    *this = copy;
}

Graphics::~Graphics() {

}

Graphics &Graphics::operator=(Graphics const &copy) {
    if (this != &copy) {
        // copy 
    }
    return *this;
}
void display(void) {

    //clear white, draw with black
    glClearColor(255, 255, 255, 0);
    glColor3d(0, 0, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //this draws a square using vertices
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(0, 128);
    glVertex2i(128, 128);
    glVertex2i(128, 0);
    glEnd();

    //a more useful helper
    glRecti(200, 200, 250, 250);

    glutSwapBuffers();

}

void reshape(int width, int height) {

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //set the coordinate system, with the origin in the top left
    gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW);

}

void idle(void) {

    glutPostRedisplay();
}

void    Graphics::helloWorld() {
    int argc = 1;
    char *argv[1] = {(char*)"Something"};
    //a basic set up...
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);

    //create the window, the argument is the title
    glutCreateWindow("GLUT program");

    //pass the callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();

    //we never get here because glutMainLoop() is an infinite loop
}

int Graphics::init() {
    return 0;
}

void Graphics::refreshScreen() {

}

void Graphics::updateScreen() {

}

void Graphics::putStrScreen(std::string str) {

}

void Graphics::loadTexture(std::string path) {

}

Graphics *createGraphics() {
    return new Graphics();
}

void deleteGraphics(Graphics *graphics) {
    delete graphics;
}

void externHelloWorld(Graphics &graphics) {
    graphics.helloWorld();
}
