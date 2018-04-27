/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graphics.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:50:50 by banthony          #+#    #+#             */
/*   Updated: 2018/04/26 17:50:50 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Graphics.hpp"

/*
 * Declaration de la variable static
 * Permet la modification de l'_eventList dans la fonction
 * de callback et donc en dehors de l'instance de la Lib
 */
std::vector<eEvent> AGraphics::_eventList;

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

//    glutSwapBuffers();

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

void Graphics::helloWorld(void) {
	int argc = 1;
	char *argv[1] = {(char *) "Something"};
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

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	std::cout << "event : " << key << std::endl;

	AGraphics::clearEvent();
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) // TODO mettre des else if
		AGraphics::addEvent(ECHAP);
	else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		AGraphics::addEvent(UP);
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		AGraphics::addEvent(DOWN);
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		AGraphics::addEvent(LEFT);
	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		AGraphics::addEvent(RIGHT);
	else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		AGraphics::addEvent(ENTER);
}

std::vector<eEvent> &Graphics::getEvent() {
	glfwPollEvents();
	return Graphics::_eventList;
}

unsigned char Graphics::getChar() {
	return 0;
}

int Graphics::init() {
	if (!glfwInit()) {
		// throw exception ? erreur init glfw!
		return -1;
	}
	/* On s'assure d'etre en context OPENGL pour pouvoir utiliser les fonction openGL (Useless si val par defaut)*/
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	if (!(_window = glfwCreateWindow(640, 480, "OpenGL", nullptr, nullptr))) {
		// throw exception ? erreur creation fenetre
		glfwTerminate();
		return -1;
	}
	/*Before you can make OpenGL or OpenGL ES calls, you need to have a current context of the correct type*/
	glfwMakeContextCurrent(_window);

	// Set callback
	glfwSetKeyCallback(_window, key_callback);

	return 0;
}

int Graphics::loopUpdate() {
	this->getEvent();
	return !glfwWindowShouldClose(_window);
}

void Graphics::updateScreen() {

}

void Graphics::putStrScreen(std::string str) {

}

void Graphics::loadTexture(std::string path) {

}

void Graphics::cleanUp() {
	glfwTerminate();
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
