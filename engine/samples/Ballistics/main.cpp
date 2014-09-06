/**************************************************************************************/
/************************************** Graphics **************************************/
/**************************************************************************************/

#include "BallisticDemo.h"

App* app;

/**
* Window creation.
*/
void createWindow(const char* title) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(title);
}

/**
* Game update.
*/
void update() {
	AppClock::s()->update();
	app->update();
}

/**
* Game render.
*/
void render() {
	app->render();
	glFlush();
	glutSwapBuffers();
}

/**
* Mouse click behaviour.
*/
void mouseClick(int button, int state, int x, int y) {
	app->mouseClick(button, state, x, y);
}

/**
* Window resize.
*/
void resize(int width, int height) {
	app->resize(width, height);
}

/**
* Keyboard behaviour.
*/
void keys(unsigned char key, int x, int y) {
	app->keys(key);
}

/**
* Mouse drag behaviour.
*/
void mouseDrag(int x, int y) {
	app->mouseDrag(x, y);
}


int main(int argc, char** argv) {
	/**************************************************************************************/
	/************************************** Graphics **************************************/
	/**************************************************************************************/

	glutInit(&argc, argv);
	AppClock::init();

	app = new BallisticDemo();
	createWindow(app->title().c_str());

	//GLUT handler stuff.
	glutReshapeFunc(resize);
	glutKeyboardFunc(keys);
	glutDisplayFunc(render);
	glutIdleFunc(update);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseDrag);

	app->init();
	glutMainLoop();

	app->destroy();
	delete app;
	AppClock::destroy();

	return 0;
}
