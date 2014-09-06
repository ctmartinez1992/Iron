#ifndef IRON_THREAD_THREAD_H_
#define IRON_THREAD_THREAD_H_

#include "Base.h"

#include "ThreadPool.h"
#include "Task.h"
#include "ThreadLock.h"
#include "TaskData.h"

namespace iron {

	namespace thread {

		/*! \brief Represents a thread that will be created by the thread pool to do work.
		*
		*  The basic behaviour of the thread class is to look for jobs and execute them until the queue
		*  is empty or something kills the thread.
		*/
		class Thread {

			/****************************** Variables ******************************/
		private:
			/**
			* The thread pool.
			*/
			ThreadPool*			pool;
			
			/**
			* The current task.
			*/
			Task*				task;

			/**
			* The lock controls the tasks ownership.
			*/
			ThreadLock			tLock;

			/**
			* The thread handle is used to store the result of the function responsible for creating the
			* thread. If the thread is created correctly, the handle for the thread is returned and stored
			* in this variable. 
			*
			* If something wrong happens while creating the thread, the returned value is 
			* 0 or -1 (both these situations are tested).
			*/
			HANDLE				threadHandle;
			
			/**
			* The exit code receives the thread termination status.
			*/
			DWORD				exitCode;

			/**
			* The thread identifier.
			*/
			unsigned int		id;

			/**
			* If running is true, it means the thread was initialized successfully, false if not or if it
			* was destroyed.
			*/
			bool				running;
			
			/**
			* If noWork is true, it means there are no more jobs on the thread pool, false if there are.
			*/
			bool				noWork;

		protected:

		public:

			/****************************** Contructors & Destructors ******************************/
		public:
			/**
			* Default constructor, initializes all variables.
			*/
			Thread();

			/**
			* Destructor, calls the stop method.
			*/
			~Thread();

		private:

			/****************************** Methods ******************************/
		private:
			/**
			* Clears the current task. The task is deleted.
			*/
			void clearTask();

		protected:
			/**
			* This function is called by the Windows API when the thread is created. This function simply 
			* calls the proc method of the thread.
			*/
			static unsigned __stdcall cThreadProc(LPVOID _pThis) {
				return ((Thread*)_pThis)->proc();
			}

		public:
			/**
			* Sets the task to the given task pointer.
			*
			* @param ptr The pointer to a task.
			*/
			void setTask(Task* ptr);

			/**
			* Function responsible to search for jobs and execute them.
			*/
			DWORD proc();

			/**
			* Creates the thread.
			*/
			bool init();

			/**
			* Kills the thread.
			*/
			bool close();

			/**
			* Obtains the thread pool lock to assure thread safety.
			*/
			void lock();

			/**
			* Releases the thread pool lock.
			*/
			void unlock();

			/**
			* Returns true if the thread was initialized successfully, false if not or if it
			* was destroyed.
			*
			* @return True if the thread was initialized successfully, false if not or if it
			* was destroyed.
			*/
			bool isRunning();

			/**
			* Returns true if the thread has no work, false if not.
			*
			* @return True if the thread has no work, false if not.
			*/
			bool isSlacking();

			/**
			* Returns the exit code.
			*
			* @return The exit code.
			*/
			DWORD getExitCode();

			/**
			* Returns the thread id.
			*
			* @return The thread id.
			*/
			unsigned int getThreadID();


			/****************************** Operators Overloading ******************************/
		private:

		protected:

		public:

		};
	}
}

#endif