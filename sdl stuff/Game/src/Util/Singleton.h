#ifndef SINGLETON_H
#define SINGLETON_H

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

//SDL

//C++

//OWN

template<typename T>
class Singleton {
	/*************** Variables ***************/
private:
	static T*			s;

protected:

public:

	/*************** Contructors & Destructors ***************/
public:
	Singleton() {
		assert(!s);

		//Point it to the start of the whole class
		int offset = (int) (T*) 1 - (int) (Singleton <T>*) (T*) 1;
		s = (T*) ((int) this + offset);
	}

	~Singleton() {
		assert(s);
		s = 0;
	}

	/*************** Methods ***************/
private:

protected:

public:
	static T&			_s() {
		assert(s);
		return *s;
	}

	static T*			_sPtr() {
		assert(s);
		return s;
	}
};

template <typename T> T* Singleton <T>::s = 0;

#endif