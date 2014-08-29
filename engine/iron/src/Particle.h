#ifndef IRON_PHYSICS_PARTICLE_H_
#define IRON_PHYSICS_PARTICLE_H_

#include "Vector3.h"

namespace iron {

	/*! \brief A simple object with some properties that is simulated in this physics system.
	*
	*  A particle is composed by a position, velocity and acceleration variables mainly;
	*  forces and impulses can be applied to the particle.
	*/
	class Particle {

		//We want this classes to have access to particles protected variables.
		friend class ForceGravity;
		friend class ForceDrag;
		friend class ForceSpring;
		friend class ForceAnchorSpring;
		friend class ForceElastic;
		friend class ForceAnchorElastic;

		/****************************** Variables ******************************/
	private:

	protected:
		Vector3			position;		/*!< The linear position of the particle in the world. */
		
		Vector3			velocity;		/*!< The linear velocity of the particle in the world. */

		Vector3			acceleration;	/*!< The acceleration of the particle. */

		Vector3			force;			/*!< The force is always applied and zeroed each integration. */

		/**
		* The amount of damping applied to the linear motion. This variable controls how much
		* velocity is left after each update. If it's 0, velocity is reduced to 0 (no motion with 
		* no force applied); If it's 1, velocity is not reduced at all (no damping). Values near 1
		* are optimal for no drag simulation.
		*/
		float			damp;

		/**
		* //TODO Fix the formula in this cooment, it's not showing right.
		*
		* The inverse of the mass of this particle. This variable is mostly used in the calculation of
		* the acceleration represented by the formula: \f[a=\frac{1}{m)}f\f] Since the inverse of the
		* mass is used more than the "regular" form, we'll store the inverse instead. this also allows
		* to control immovable particles (infinite mass) instead of void particles (zero mass).
		*/
		float			inverseMass;

	public:

		/****************************** Contructors & Destructors ******************************/
	public:
		/**
		* Constructs a new particle with all values set to 0.
		*/
		Particle();

		/**
		* Destructor.
		*/
		~Particle();

	private:

		/****************************** Methods ******************************/
	private:

	protected:

	public:
		/**
		* Integrates this particle forward in time by the given duration. Basically, this function
		* updates the particle's linear position, calculates the acceleration and velocity, "adds" the 
		* damp value and zeros the forces.
		*/
		void integration(float duration);

		/**
		* Applies the given force to this particle in the next integration.
		*
		* @param force The force to be applied.
		*/
		void addForce(const Vector3& force);

		/**
		* Zeroes the force variable.
		*/
		void clearForce();

		/**
		* Sets the position of this particle with the given Vector3 object values.
		*
		* @param position The new position of this particle.
		*/
		void setPosition(const Vector3& position);

		/**
		* Sets the position of this particle with the given float variables.
		*
		* @param x The new x coordinate.
		* @param y The new y coordinate.
		* @param z The new z coordinate.
		*/
		void setPosition(const float x, const float y, const float z);

		/**
		* Returns the position of this particle.
		*
		* @param dst The vector that stores the position.
		*/
		const void getPosition(Vector3* dst) const;

		/**
		* Sets the velocity of this particle with the given Vector3 object values.
		*
		* @param velocity The new velocity of this particle.
		*/
		void setVelocity(const Vector3& velocity);

		/**
		* Sets the velocity of this particle with the given float variables.
		*
		* @param x The new x coordinate.
		* @param y The new y coordinate.
		* @param z The new z coordinate.
		*/
		void setVelocity(const float x, const float y, const float z);

		/**
		* Returns the velocity of this particle.
		*
		* @param dst The vector that stores the velocity.
		*/
		const void getVelocity(Vector3* dst) const;

		/**
		* Sets the acceleration of this particle with the given Vector3 object values.
		*
		* @param acceleration The new acceleration of this particle.
		*/
		void setAcceleration(const Vector3& acceleration);

		/**
		* Sets the acceleration of this particle with the given float variables.
		*
		* @param x The new x coordinate.
		* @param y The new y coordinate.
		* @param z The new z coordinate.
		*/
		void setAcceleration(const float x, const float y, const float z);

		/**
		* Returns the acceleration of this particle.
		*
		* @param dst The vector that stores the acceleration.
		*/
		const void getAcceleration(Vector3* dst) const;
		
		/**
		* Sets the damp of this particle.
		*
		* @param damp The new damp value.
		*/
		void setDamp(const float damp);

		/**
		* Returns the damp value of this particle.
		*
		* @return The damp value of this particle.
		*/
		float getDamp() const;

		/**
		* Sets the mass of this particle. Since this particle only stores inverseMass,
		* the mass is inverted and stored accordingly.
		*
		* @param mass The new mass of this particle. Can't be zero.
		* 
		* @warning Should call calculateInternals to revalidate this particle values.
		* @see calculateInternals, setInverseMass
		*/
		void setMass(const float mass);

		/**
		* Returns the mass of the particle. Not the inverted mass.
		*
		* @return The mass of this particle.
		* @see getInverseMass
		*/
		float getMass() const;

		/**
		* Sets the inverse mass of this particle.
		*
		* @param inverseMass The new inverse mass of this particle. Can be zero (immovable particle)
		*
		* @warning Should call calculateInternals to revalidate this particle values.
		* @see calculateInternals, setMass
		*/
		void setInverseMass(const float inverseMass);

		/**
		* Returns the inverse mass of this particle.
		*
		* @return The inverse mass of this particle.
		* @see getMass
		*/
		float getInverseMass() const;
		
		/**
		* Returns true if the mass of the particle is not-infinite. False if not.

		* @return true if the mass of the particle is not-infinite. False if not.
		*/
		bool hasFiniteMass() const;

		/****************************** Operators Overloading ******************************/
	private:

	protected:

	public:

	};
}

#endif