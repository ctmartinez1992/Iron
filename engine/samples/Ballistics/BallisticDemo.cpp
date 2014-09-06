#include "BallisticDemo.h"

BallisticDemo::BallisticDemo() 
	: bullets(), selectedBullet(BULLET)
{
	Bullet* forSize = (bullets + nBullets);
    for (Bullet* b = bullets; b < forSize; b++) {
        b->type = NOTHING;
    }
}

BallisticDemo::~BallisticDemo() {
}

App* getApplication() {
	return new BallisticDemo();
}

void BallisticDemo::update() {
	float duration = (float)AppClock::s()->lastFSpan * 0.001f;
	if (duration <= 0.0f) {
		return;
	}

	//Update physics for all bullets.
	Bullet* forSize = (bullets + nBullets);
	for (Bullet* b = bullets; b < forSize; b++) {
		if (b->type != NOTHING) {
			b->particle.integration(duration);

			iron::Vector3 position;
			b->particle.getPosition(&position);
			if (position.y < 0.0f 
				|| position.z > 200.0f
				|| b->shotTime + 4000 < AppClock::s()->lastFTS)
			{
				b->type = NOTHING;
			}
		}
	}

	App::update();
}

void BallisticDemo::render() {
	//TODO Work out a better camera angle
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(-25.0, 8.0, 5.0, 0.0, 5.0, 22.0, 0.0, 1.0, 0.0);

	glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(0.0f, 1.5f, 0.0f);
		glutSolidSphere(0.1f, 5, 5);
		glTranslatef(0.0f, -1.5f, 0.0f);
		glColor3f(0.75f, 0.75f, 0.75f);
		glScalef(1.0f, 0.1f, 1.0f);
		glutSolidSphere(0.1f, 5, 5);
	glPopMatrix();

	//Some lines
	glColor3f(0.75f, 0.75f, 0.75f);
	glBegin(GL_LINES);
		for (unsigned i = 0; i < 200; i += 10) {
			glVertex3f(-5.0f, 0.0f, i);
			glVertex3f(5.0f, 0.0f, i);
		}
	glEnd();

	//Render bullets
	Bullet* forSize = (bullets + nBullets);
	for (Bullet* b = bullets; b < forSize; b++) {
		if (b->type != NOTHING) {
			b->render();
		}
	}

	//Text
	glColor3f(0.0f, 0.0f, 0.0f);
	renderText(10.0f, 10.0f, "Mouse Click: Fire!!\n1 to 3: Select Bullet Type");
	switch (selectedBullet) {
		case BULLET: 
			renderText(10.0f, 40.0f, "Current Ammo: Pistol Bullet"); 
			break;

		case CANNON: 
			renderText(10.0f, 40.0f, "Current Ammo: Cannon Ball"); 
			break;

		case FIRE:
			renderText(10.0f, 40.0f, "Current Ammo: Fire Ball");
			break;

		case NOTHING:
			renderText(10.0f, 40.0f, "Current Ammo: Nothing");
			break;

		default:
			renderText(10.0f, 40.0f, "Current Ammo: ERROR");
			break;
	}
}

void BallisticDemo::mouseClick(const int button, const int state, const int x, const int y) {
	if (state == GLUT_DOWN) {
		fire();
	}
}

void BallisticDemo::keys(const unsigned char key) {
	switch (key) {
		case '1': 
			selectedBullet = BULLET; 
			break;

		case '2': 
			selectedBullet = CANNON; 
			break;

		case '3':
			selectedBullet = FIRE;
			break;

		default:
			selectedBullet = NOTHING;
			break;
	}
}

const std::string BallisticDemo::title() {
    return "Iron Demo 01 - Basic Ballistics";
}

void BallisticDemo::fire() {
	Bullet* b;
	Bullet* forSize = (bullets + nBullets);
	for (b = bullets; b < forSize; b++) {
		if (b->type == NOTHING) {
			break;
		}
    }

	if (b >= (bullets + nBullets)) {
		return;
	}

    // Set the properties of the particle
    switch(selectedBullet) {
		case BULLET:
			b->particle.setMass(2.0f);							//2.0kg.
			b->particle.setVelocity(0.0f, 0.0f, 60.0f);			//60m/s.
			b->particle.setAcceleration(0.0f, -0.5f, 0.0f);		//Low Gravity.
			b->particle.setDamp(0.99f);							//Almost no resistance.
			break;

		case CANNON:
			b->particle.setMass(150.0f);						//250.0kg.
			b->particle.setVelocity(0.0f, 30.0f, 40.0f);		//50m/s.
			b->particle.setAcceleration(0.0f, -20.0f, 0.0f);	//Heavy graivity.
			b->particle.setDamp(0.99f);							//Almost no resistance.
			break;

		case FIRE:
			b->particle.setMass(1.0f);							//1.0kg.
			b->particle.setVelocity(0.0f, 0.0f, 10.0f);			//10m/s.
			b->particle.setAcceleration(0.0f, 0.5f, 0.0f);		//Negative gravity.
			b->particle.setDamp(0.9f);							//Some resistance.
			break;
    }

    b->particle.setPosition(0.0f, 1.5f, 0.0f);
    b->shotTime = AppClock::s()->lastFTS;
    b->type = selectedBullet;
	b->particle.clearForce();
}