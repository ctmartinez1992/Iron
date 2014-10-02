#include "App.h"

void App::init() {
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    view();
}

void App::destroy() {
}

void App::update() {
	glutPostRedisplay();
}

void App::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
		glVertex2i(20, 20);
		glVertex2i(500, 500);
    glEnd();
}

void App::mouseClick(const int state, const int button, const int x, const int y) {
	//Don't do anything here.
}

void App::mouseDrag(const int x, const int y) {
	//Don't do anything here.
}

void App::keys(const unsigned char key) {
	//Don't do anything here.
}

void App::resize(const int width, const int height) {
	if (width <= 0) {
		this->width = 1024;		//Default value
	}

	if (height <= 0) {
		this->height = 768;		//Default value
	}

    this->width = width;
    this->height = height;
	glViewport(0, 0, this->width, this->height);
    view();
}

void App::view() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
		gluPerspective(70.0, (double)width / (double)height, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

const std::string App::title() {
	return std::string("Iron Demo 00 - Early Graphical Test Appliction");
}

void App::renderText(float x, float y, const char* text, void* font) {
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
		glOrtho(0.0, (double)width, 0.0, (double)height, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    if (font == NULL) {
        font = GLUT_BITMAP_TIMES_ROMAN_24;
    }

    size_t len = strlen(text);
    glRasterPos2f(x, y);
    for (const char* letter = text; letter < (text + len); letter++) {
        if (*letter == '\n') {
            y -= 12.0f;
            glRasterPos2f(x, y);
        }

        glutBitmapCharacter(font, *letter);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}