#ifndef IRON_THREAD_THREAD_LOCK_H_
#define IRON_THREAD_THREAD_LOCK_H_

#include "Base.h"

namespace iron {

	namespace thread {

		/*! \brief Lock is the used synchronization mechanism for enforcing limits on access to a resource
		* in an environment where there are many threads executing.
		*
		*  The threads of one process can use a critical section object (mutex) for mutual-exclusion 
		*  synchronization. This class does not guarantee order in which threads will obtain ownership of the critical 
		*  section.
		*
		*  After a critical section object has been initialized, the threads of the process can specify 
		*  the object in the EnterCriticalSection or LeaveCriticalSection function to provide mutually 
		*  exclusive access to a shared resource. The critical section object cannot be moved, copied or modified. Use
		*  only the critical section functions to manage critical section objects.
		*/
		class ThreadLock {

			/****************************** Variables ******************************/
		private:

		protected:

		public:
			/**
			* A critical section object provides synchronization similar to that provided by a 
			* mutex object.
			*/
			CRITICAL_SECTION		cs;

			/****************************** Contructors & Destructors ******************************/
		public:
			/**
			* Initializes the critical section object.
			*/
			ThreadLock() { InitializeCriticalSection(&cs); }

			/**
			* Destroys the critical section object.
			*/
			~ThreadLock() { DeleteCriticalSection(&cs); }

		private:
			
			/****************************** Methods ******************************/
		private:

		protected:

		public:
			/**
			* Waits for ownership of the given critical section object. 
			* The function returns when the calling thread is granted ownership.
			*/
			void lock() { EnterCriticalSection(&cs); }

			/**
			* Unlocks the given critical section object.
			*/
			void unlock() { LeaveCriticalSection(&cs); }

		};
	}
}

#endif