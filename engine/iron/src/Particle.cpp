#include "Base.h"
#include "Particle.h"

namespace iron {

	Particle::Particle()
		: position(Vector3()), velocity(Vector3()), acceleration(Vector3()), force(Vector3()), 
		damp(0.0f), inverseMass(0.0f)
	{}

	Particle::~Particle() {
	}

	void Particle::integration(float duration) {
		if (inverseMass <= 0.0f) {
			return;
		}

		if (duration <= 0.0f) {
			iron::Log::s()->logError("The duration value must be superior to 0.", __LINE__, 
				std::string(__FUNCTION__), std::string(__FILE__));
		}

		position.addScaledVector(velocity, duration);
		Vector3 resultingAcc = acceleration;
		resultingAcc.addScaledVector(force, inverseMass);
		velocity.addScaledVector(resultingAcc, duration);
		velocity *= powf(damp, duration);
		clearForce();
	}

	void Particle::addForce(const Vector3& force) {
		this->force.add(force);
	}

	void Particle::clearForce() {
		force.set(0, 0, 0);
	}
	
	void Particle::setPosition(const Vector3& position)	{
		this->position = position;
	}

	void Particle::setPosition(const float x, const float y, const float z) {
		position.set(x, y, z);
	}

	const Vector3& Particle::getPosition() const {
		return position;
	}
	
	void Particle::setVelocity(const Vector3& velocity)	{
		this->velocity = velocity;
	}

	void Particle::setVelocity(const float x, const float y, const float z) {
		velocity.set(x, y, z);
	}

	const Vector3& Particle::getVelocity() const {
		return velocity;
	}

	void Particle::setAcceleration(const Vector3& acceleration) {
		this->acceleration = acceleration;
	}

	void Particle::setAcceleration(const float x, const float y, const float z)	{
		acceleration.set(x, y, z);
	}

	const Vector3& Particle::getAcceleration() const {
		return acceleration;
	}

	void Particle::setDamp(const float damp) {
		this->damp = damp;
	}

	float Particle::getDamp() const {
		return damp;
	}

	void Particle::setMass(const float mass) {
		if (mass == 0) {
			iron::Log::s()->logError("When setting the mass, it can never be 0. Otherwise, the universe will explode.", 
				__LINE__, std::string(__FUNCTION__), std::string(__FILE__));
		}

		inverseMass = ((float)1.0) / mass;
	}

	float Particle::getMass() const {
		if (inverseMass == 0) {
			return FLT_MAX;
		} else {
			return ((float)1.0) / inverseMass;
		}
	}

	void Particle::setInverseMass(const float inverseMass) {
		this->inverseMass = inverseMass;
	}

	float Particle::getInverseMass() const {
		return inverseMass;
	}

	bool Particle::hasFiniteMass() const {
		return (inverseMass >= 0.0f);
	}
}