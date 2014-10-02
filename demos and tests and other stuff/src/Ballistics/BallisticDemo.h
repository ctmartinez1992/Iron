#ifndef IRON_DEMO_BALLISTIC_DEMO_
#define IRON_DEMO_BALLISTIC_DEMO_

#include "App.h"
#include "AppClock.h"

/*! \brief Demo for ballistic experimentation.
*
*/
class BallisticDemo : public App {

	/**
	* Available types of bullets.
	*/
	enum BulletType {
		NOTHING = 0,
		BULLET,
		CANNON,
		FIRE
	};

	/**
	* Holds information about 1 bullet.
	*/
	struct Bullet {
		iron::Particle		particle;		/*!< Physics representation. */

		BulletType			type;			/*!< The type of bullet. */

		unsigned long		shotTime;		/*!< Bullets is fired at this time. */

		/**
		* Renders the bullet to the screen.
		*/
		void render() {
			iron::Vector3 position;
			particle.getPosition(&position);

			glColor3f(0, 0, 0);
			glPushMatrix();
			glTranslatef(position.x, position.y, position.z);
			glutSolidSphere(0.3f, 5, 4);
			glPopMatrix();

			glColor3f(0.75, 0.75, 0.75);
			glPushMatrix();
			glTranslatef(position.x, 0, position.z);
			glScalef(1.0f, 0.1f, 1.0f);
			glutSolidSphere(0.6f, 5, 4);
			glPopMatrix();
		}
	};

	/****************************** Variables ******************************/
private:

protected:

public:
	const static unsigned short		nBullets = 10;			/*!< The amount of bullets. */

	Bullet							bullets[nBullets];		/*!< Array to store all bullets. */

	BulletType						selectedBullet;			/*!< Selected bullet type. */


	/****************************** Contructors & Destructors ******************************/
public:
	/**
	* Default contructor.
	*/
	BallisticDemo();

	/**
	* Destructor.
	*/
	~BallisticDemo();

private:

	/****************************** Virtual Methods ******************************/
private:

protected:

public:
	/**
	* Update the bullets (particles) position.
	*/
	virtual void update();

	/**
	* Render the bullets.
	*/
	virtual void render();

	/**
	* Handles the mouse clicking behaviour.
	*
	* @param state The current state of the mouse button.
	* @param button The pressed mouse button
	* @param x The x position of the mouse at which the state happened.
	* @param y The y position of the mouse at which the state happened.
	*/
	virtual void mouseClick(const int button, const int state, const int x, const int y);

	/**
	* Handles the keyboard behaviour.
	*
	* @param key The pressed key.
	*/
	virtual void keys(const unsigned char key);

	/** 
	* Returns the title of this demo.
	*
	* @return The title of this demo.
	*/
	virtual const std::string title();

	/****************************** Methods ******************************/
private:
	/** 
	* Fires 1 bullet.
	*/
	void fire();

protected:

public:

	/****************************** Operators Overloading ******************************/
private:

protected:

public:

};

#endif