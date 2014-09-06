#ifndef IRON_PHYSICS_PARTICLE_FORCE_GENERATOR_H_
#define IRON_PHYSICS_PARTICLE_FORCE_GENERATOR_H_

#include "Base.h"
#include "Vector3.h"

namespace iron {

	class Particle;
	class ForceGenerator;

	/****************************************************************************/
	/********************************* ForceList ********************************/
	/****************************************************************************/

	/*! \brief Holds all the force generators.
	*
	*  Holds all the force generators and the particles they apply to.
	*/
	class ForceList {

		/****************************** Variables ******************************/
	private:

	protected:
		/**
		* Holds a force generator and the particle affected.
		*/
		struct ForceParticle {
			Particle*				particle;			/*!< The particle. */
			ForceGenerator*			forceGenerator;		/*!< The force generator. */
		};

		std::vector<ForceParticle>	list;				/*!< The list of ForceParticle objects. */

	public:

		/****************************** Methods ******************************/
	private:

	protected:

	public:
		/**
		* Stores the given force generator that will apply to the given particle in the list.
		*
		* @param p The particle.
		* @param fg The force generator.
		*/
		void add(Particle* p, ForceGenerator* fg);

		/**
		* Removes the given pair from the list.
		*
		* @param p The particle.
		* @param fg The force generator.
		*/
		void remove(Particle* p, ForceGenerator* fg);

		/**
		* Clears the list content, only removes the link between particle and force.
		*/
		void clear();

		/**
		* Updates all the pairs in the list. All forces are appied to the respective pairs.
		*
		* @param d The duration value, only used sometimes.
		*/
		void update(const float d);

	};

	/****************************************************************************/
	/****************************** ForceGenerator ******************************/
	/****************************************************************************/

	/*! \brief An interface for force updating.
	*
	*  Provides one method to allow particles to request a force.
	*/
	class ForceGenerator {

		/****************************** Methods ******************************/
	private:

	protected:

	public:
		/**
		* Interface function, used to calculate and update a force applied to the given particle.
		*
		* @param p The particle that is going to be submitted to the force.
		* @param d The duration of the force.
		*/
		virtual void update(Particle* p, const float d) = 0;

	};

	/****************************************************************************/
	/******************************* ForceGravity *******************************/
	/****************************************************************************/

	/*! \brief A Force that applies a gravitational type force to a particle.
	*
	*  A Force that applies a gravitational type force to a particle. This instance can be applied to
	*  multiple particles.
	 *
	 * If the traditional value of gravity suffices, the acceleration variable in Particle can be set
	 * to operate in that way, if a more complex system of gravity must be used, this class should be
	 * used instead and the acceleration of the gravity should be set to 0.
	*/
	class ForceGravity : public ForceGenerator {

		/****************************** Variables ******************************/
	private:
		Vector3			gravity;		/*!< Vector representation of gravity. */

	protected:

	public:

		/****************************** Contructors & Destructors ******************************/
	public:
		/**
		* Creates a gravity force generator with the given values.
		*
		* @param g The gravity value.
		*/
		ForceGravity(const Vector3& g);

		/**
		* Destructor.
		*/
		~ForceGravity();

	private:

		/****************************** Methods ******************************/
	private:

	protected:

	public:
		/**
		* Applies the generated gravity force to the given particle.
		*
		* @param p The particle to update.
		* @param d The duration value, only used sometimes.
		*/
		virtual void update(Particle* p, const float d);
	};

	/****************************************************************************/
	/********************************* ForceDrag ********************************/
	/****************************************************************************/

	/*! \brief A Force that applies a drag-like force to a particle.
	*
	*  A Force that applies a drag-like force to a particle. This instance can be applied to
	*  multiple particles.
	*
	* This form of drag is pretty much how damp works, if a more complex form of damping is
	* necessary, the damp variable in Particle can be set to a value close to 1 and use this force
	* instead. However, the variable damp is faster because it's simple, fast and it's only 1 variable.
	*/
	class ForceDrag : public ForceGenerator {

		/****************************** Variables ******************************/
	private:
		float		coefficient;			/*!< Holds the velocity drag coeffificent. */

		float		squaredCoefficient;		/*!< Holds the velocity squared drag coeffificent. */

	protected:

	public:

		/****************************** Contructors & Destructors ******************************/
	public:
		/**
		* Creates a drag-like force generator with the given values.
		*
		* @param c The damp coefficient value.
		* @param sc The squared damp coefficient value.
		*/
		ForceDrag(const float c, const float sc);

		/**
		* Destructor.
		*/
		~ForceDrag();

	private:

		/****************************** Methods ******************************/
	private:

	protected:

	public:
		/**
		* Applies the generated drag force to the given particle.
		*
		* @param p The particle to update.
		* @param d The duration value, only used sometimes.
		*/
		virtual void update(Particle* p, const float d);
	};

	/****************************************************************************/
	/******************************** ForceSpring *******************************/
	/****************************************************************************/

	/*! \brief A Force that applies a spring force to a particle.
	*
	*  A Force that applies a spring force to 2 particles, each one positioned at each end of the
	*  spring. This instance can be applied to multiple particles.
	*/
	class ForceSpring : public ForceGenerator {

		/****************************** Variables ******************************/
	private:

	protected:
		Particle*		end;					/*!< The particle at the other end of the spring. */

		float			rest;					/*!< The rest length. */

		float			constant;				/*!< The spring constant. */

	public:

		/****************************** Contructors & Destructors ******************************/
	public:
		/**
		* Creates a spring force generator with the given values.
		*
		* @param e The particle at the other end of the spring.
		* @param r The rest length.
		* @param c The spring constant.
		*/
		ForceSpring(Particle* e, const float r, const float c);

		/**
		* Destructor.
		*/
		virtual ~ForceSpring();

	private:

		/****************************** Methods ******************************/
	private:

	protected:

	public:
		/**
		* Applies the generated spring force to the given particle.
		*
		* @param p The particle to update.
		* @param d The duration value, only used sometimes.
		*/
		virtual void update(Particle* p, const float d);
	};

	/****************************************************************************/
	/***************************** ForceAnchorSpring ****************************/
	/****************************************************************************/

	/*! \brief A Force that applies a spring force to a fixed position and a particle.
	*
	*  A Force that applies a spring force to a fixed position and a particle, the particle is at
	*  one end of the spring and at the other end we have a "anchor". This instance can be applied
	*  to multiple particles.
	*/
	class ForceAnchorSpring : public ForceGenerator {

		/****************************** Variables ******************************/
	private:

	protected:
		Vector3*		anchor;					/*!< The position of the anchor. */

		float			rest;					/*!< The rest length. */

		float			constant;				/*!< The spring constant. */

	public:

		/****************************** Contructors & Destructors ******************************/
	public:
		/**
		* Creates a spring force generator with the given values.
		*
		* @param a The position of the anchor.
		* @param r The rest length.
		* @param c The spring constant.
		*/
		ForceAnchorSpring(Vector3* a, const float r, const float c);

		/**
		* Destructor.
		*/
		~ForceAnchorSpring();

	private:

		/****************************** Methods ******************************/
	private:

	protected:

	public:
		/**
		* Applies the generated spring force to the given particle.
		*
		* @param p The particle to update.
		* @param d The duration value, only used sometimes.
		*/
		virtual void update(Particle* p, const float d);
	};

	/****************************************************************************/
	/******************************** ForceElastic ******************************/
	/****************************************************************************/

	/*! \brief A Force that applies an elastic force to a particle.
	*
	*  A Force that applies an elastic force to 2 particles, each one positioned at each end of the
	*  spring. This instance can be applied to multiple particles. This class derives from ForceSpring.
	*/
	class ForceElastic : public ForceSpring {

		/****************************** Variables ******************************/
	private:

	protected:

	public:

		/****************************** Contructors & Destructors ******************************/
	public:
		/**
		* Creates an elastic force generator with the given values.
		*
		* @param e The particle at the other end of the spring
		* @param r The rest length.
		* @param c The spring constant.
		*/
		ForceElastic(Particle* e, const float r, const float c);

		/**
		* Destructor.
		*/
		virtual ~ForceElastic();

	private:

		/****************************** Methods ******************************/
	private:

	protected:

	public:
		/**
		* Applies the generated spring force to the given particle.
		*
		* @param p The particle to update.
		* @param d The duration value, only used sometimes.
		*/
		virtual void update(Particle* p, const float d);
	};

	/****************************************************************************/
	/***************************** ForceAnchorElastic ***************************/
	/****************************************************************************/

	/*! \brief A Force that applies an elastic force to a fixed position and a particle.
	*
	*  A Force that applies an elastic force to a fixed position and a particle, the particle is at
	*  one end of the spring and at the other end we have a "anchor". This instance can be applied
	*  to multiple particles. This class derives from ForceAnchorSpring.
	*/
	class ForceAnchorElastic : public ForceAnchorSpring {

		/****************************** Variables ******************************/
	private:

	protected:

	public:

		/****************************** Contructors & Destructors ******************************/
	public:
		/**
		* Creates an elastic force generator with the given values.
		*
		* @param a The position of the anchor.
		* @param r The rest length.
		* @param c The spring constant.
		*/
		ForceAnchorElastic(Vector3* a, const float r, const float c);

		/**
		* Destructor.
		*/
		virtual ~ForceAnchorElastic();

	private:

		/****************************** Methods ******************************/
	private:

	protected:

	public:
		/**
		* Applies the generated elastic force to the given particle.
		*
		* @param p The particle to update.
		* @param d The duration value, only used sometimes.
		*/
		virtual void update(Particle* p, const float d);
	};

	/****************************************************************************/
	/****************************** ForceStiffSpring ****************************/
	/****************************************************************************/

	/*! \brief A Force that applies a spring force to a particle.
	*
	*  A Force that applies a spring force to 2 particles, each one positioned at each end of the
	*  spring. This instance can be applied to multiple particles.
	*/
	class ForceStiffSpring : public ForceGenerator {

		/****************************** Variables ******************************/
	private:

	protected:
		Vector3*		anchor;					/*!< The position of the anchor. */

		float			damp;					/*!< The damp of the spring. */

		float			constant;				/*!< The spring constant. */

	public:

		/****************************** Contructors & Destructors ******************************/
	public:
		/**
		* Creates a spring force generator with the given values.
		*
		* @param a The position of the anchor.
		* @param d The damp.
		* @param c The spring constant.
		*/
		ForceStiffSpring(Vector3* a, const float d, const float c);

		/**
		* Destructor.
		*/
		virtual ~ForceStiffSpring();

	private:

		/****************************** Methods ******************************/
	private:

	protected:

	public:
		/**
		* Applies the generated spring force to the given particle.
		*
		* @param p The particle to update.
		* @param d The duration value, only used sometimes.
		*/
		virtual void update(Particle* p, const float d);
	};

	/****************************************************************************/
	/***************************** ForceBuoyancy ***************************/
	/****************************************************************************/

	/*! \brief A Force that applies a buoyancy force (impulsion) to a fixed position and a particle.
	*
	*  Buoyancy force is equal to the weight of the water that an object displaces. Having that in mind.
	*  This force applies, in most cases, to objects dropped in a liquid which are then pushed  upwards
	*  by buoyancy force. Applied to only one object. This instance can be applied to multiple particles. 
	*/
	class ForceBuoyancy : public ForceGenerator {

		/****************************** Variables ******************************/
	private:
		/**
		* The volume of the object.
		*/
		float		volume;

		/**
		* The depth limit. Upon reaching this limit, the maximum buoyancy force kicks in.
		*/
		float		depthLimit;

		/**
		* The height of the liquid plane. Y coordinate must be above 0. The plane must be parrallel to 
		* the XZ plane.
		*/
		float		liquidHeight;

		/**
		* The density of the liquid.
		*/
		float		liquidDensity;

	protected:

	public:

		/****************************** Contructors & Destructors ******************************/
	public:
		/**
		* Creates a buoyancy force generator with the given values.
		*
		* @param v The volume.
		* @param dl The depth limit.
		* @param lh The liquid height. Y coordinate must be above 0. The plane must be parrallel to the 
		* XZ plane.
		* @param ld The liquid density.
		*/
		ForceBuoyancy(const float v, const float dl, const float lh, const float ld);

		/**
		* Destructor.
		*/
		virtual ~ForceBuoyancy();

	private:

		/****************************** Methods ******************************/
	private:

	protected:

	public:
		/**
		* Applies the generated buoyancy force to the given particle.
		*
		* @param p The particle to update.
		* @param d The duration value, only used sometimes.
		*/
		virtual void update(Particle* p, const float d);
	};
}

#endif