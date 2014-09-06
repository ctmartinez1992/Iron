#include "ParticleForceGenerator.h"
#include "Particle.h"

namespace iron {

	/****************************************************************************/
	/********************************* ForceList ********************************/
	/****************************************************************************/

	void ForceList::add(Particle* p, ForceGenerator* fg) {
		ForceList::ForceParticle fp;
		fp.particle = p;
		fp.forceGenerator = fg;
		list.push_back(fp);
	}

	void ForceList::update(const float d) {
		for (std::vector<ForceParticle>::iterator i = list.begin(); i != list.end(); i++) {
			i->forceGenerator->update(i->particle, d);
		}
	}

	/****************************************************************************/
	/******************************* ForceGravity *******************************/
	/****************************************************************************/

	ForceGravity::ForceGravity(const Vector3& g) :
		gravity(g)
	{
	}

	ForceGravity::~ForceGravity() {
	}

	void ForceGravity::update(Particle* p, const float d) {
		if (!p->hasFiniteMass()) {
			return;
		}

		p->addForce(gravity * p->getMass());
	}

	/****************************************************************************/
	/********************************* ForceDrag ********************************/
	/****************************************************************************/

	ForceDrag::ForceDrag(const float c, const float sc) :
		coefficient(c), squaredCoefficient(sc)
	{
	}

	ForceDrag::~ForceDrag() {
	}

	void ForceDrag::update(Particle* p, const float d) {
		Vector3 force;
		force.set(p->velocity);

		float dragC = force.length();
		dragC = ((coefficient * dragC) + (squaredCoefficient * dragC * dragC));

		force.normalize();
		force *= -dragC;
		p->addForce(force);
	}

	/****************************************************************************/
	/******************************** ForceSpring *******************************/
	/****************************************************************************/

	ForceSpring::ForceSpring(Particle* e, const float r, const float c) :
		rest(r), constant(c)
	{
		if (e == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		end = e;
	}

	ForceSpring::~ForceSpring() {
		//The particle can not be destroyed, it may be used on other parts of the physics system.
		//Let's simply nullify it.
		end = nullptr;
	}

	void ForceSpring::update(Particle* p, const float d) {
		//The vector representative of the spring.
		Vector3 force;
		force.set(p->position);
		force -= end->position;

		//Calculate the magnitude of the force and apply to particle.
		float magnitude = (float)((fabsf(force.length() - rest)) * constant);
		force.normalize();
		force *= -magnitude;
		p->addForce(force);
	}

	/****************************************************************************/
	/***************************** ForceAnchorSpring ****************************/
	/****************************************************************************/

	ForceAnchorSpring::ForceAnchorSpring(Vector3* a, const float r, const float c) :
		rest(r), constant(c)
	{
		if (a == nullptr) {
			iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
				std::string(__FILE__));
			return;
		}

		anchor = a;
	}

	ForceAnchorSpring::~ForceAnchorSpring() {
		//The particle can not be destroyed, it may be used on other parts of the physics system.
		//Let's simply nullify it.
		anchor = nullptr;
	}

	void ForceAnchorSpring::update(Particle* p, const float d) {
		//The vector representative of the spring.
		Vector3 force;
		force.set(p->position);
		force -= *anchor;

		//Calculate the magnitude of the force and apply to particle.
		float magnitude = ((rest - force.length()) * constant);
		force.normalize();
		force *= magnitude;
		p->addForce(force);
	}

	/****************************************************************************/
	/******************************* ForceElastic *******************************/
	/****************************************************************************/

	ForceElastic::ForceElastic(Particle* e, const float r, const float c) :
		ForceSpring(e, r, c)
	{
	}

	ForceElastic::~ForceElastic() {
	}

	void ForceElastic::update(Particle* p, const float d) {
		//The vector representative of the spring.
		Vector3 force;
		force.set(p->position);
		force -= end->position;

		//Check elastic compression.
		float magnitude = force.length();
		if (magnitude <= rest) {
			return;
		}

		//Calculate the magnitude of the force and apply to particle.
		magnitude = (constant * (rest - magnitude));
		force.normalize();
		force *= -magnitude;
		p->addForce(force);
	}

	/****************************************************************************/
	/**************************** ForceAnchorElastic ****************************/
	/****************************************************************************/

	ForceAnchorElastic::ForceAnchorElastic(Vector3* a, const float r, const float c) :
		ForceAnchorSpring(a, r, c)
	{
	}

	ForceAnchorElastic::~ForceAnchorElastic() {
	}

	void ForceAnchorElastic::update(Particle* p, const float d) {
		//The vector representative of the spring.
		Vector3 force;
		force.set(p->position);
		force -= *anchor;

		//Check elastic compression.
		float magnitude = force.length();
		if (magnitude < rest) {
			return;
		}

		//Calculate the magnitude of the force and apply to particle.
		magnitude = (magnitude - rest) * constant;
		force.normalize();
		force *= -magnitude;
		p->addForce(force);
	}

	/****************************************************************************/
	/****************************** ForceStiffSpring ****************************/
	/****************************************************************************/

	ForceStiffSpring::ForceStiffSpring(Vector3* a, const float d, const float c) :
		anchor(a), damp(d), constant(c)
	{
	}

	ForceStiffSpring::~ForceStiffSpring() {
	}

	void ForceStiffSpring::update(Particle* p, const float d) {
		if (!p->hasFiniteMass()) {
			return;
		}

		//Relative position between anchor and particle.
		Vector3 position;
		position.set(p->position);
		position -= *anchor;

		//Calculate the constants and check they are in bounds.
		float springConstant = (0.5f * sqrt((4.0f * constant) - (damp * damp)));
		if (springConstant == 0.0f) {
			return;
		}

		Vector3 c = ((position * (damp / (2.0f * springConstant))) + 
			(p->velocity * (1.0f / springConstant)));

		//The target position.
		Vector3 target = ((position * cos(springConstant * d)) + (c * sin(springConstant * d)));
		target *= exp((-0.5f * d * damp));

		//The acceleration force.
		Vector3 force = (target - position) * (1.0f / (d * d)) - p->velocity * (1.0f / d);
		p->addForce(force * p->getMass());
	}

	/****************************************************************************/
	/******************************* ForceBuoyancy ******************************/
	/****************************************************************************/

	ForceBuoyancy::ForceBuoyancy(const float v, const float dl, const float lh, const float ld) :
		volume(v), depthLimit(dl), liquidHeight(lh), liquidDensity(ld)
	{
	}

	ForceBuoyancy::~ForceBuoyancy() {
	}

	void ForceBuoyancy::update(Particle* p, const float d) {
		//Get current y position (depth).
		float depth = p->position.y;
		if (depth >= (liquidHeight + depthLimit)) {
			//Not inside the liquid.
			return;
		}
		else if (depth <= (liquidHeight - depthLimit)) {
			//This is maximum depth.
			Vector3 force(0, (liquidDensity * volume), 0);
			p->addForce(force);
			return;
		}
		else {
			//Between outer edge and depth limit.
			Vector3 force(0, (liquidDensity * volume * ((depth - depthLimit - liquidHeight) / 2) * depthLimit), 0);
			p->addForce(force);
		}
	}
}