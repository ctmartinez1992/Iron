#ifndef IRON_THREAD_THREAD_POOL_H_
#define IRON_THREAD_THREAD_POOL_H_

#include "Task.h"
#include "TwoLockQueue.h"
#include <vector>

namespace iron {

	namespace thread {

		/*! \brief The thread pool is responsible for holding the threads and the jobs.
		*
		*  Basically, the pool controls que queue of jobs and manages the threads vector.
		*  Tasks can be added via the function addTask and when no longer necessary, it can be
		*  closed. If needed again, it can be initialized with the init function.
		*/
		class ThreadPool {

			//Direct access to threads
			friend class Thread;
			
			/****************************** Variables ******************************/
		private:
			static ThreadPool*		_s;				/*!< Pointer to the unique ThreadPool (Singleton). */

			TwoLockQueue<Task*>		taskList;		/*!< The queue that stores the tasks. */

			std::vector<Thread*>	threads;		/*!< The available threads. */

			unsigned int			active;			/*!< The number of threads in the vector. */
			
			volatile bool			process;		/*!< The value tells if the pool has working thread or not. */

		protected:

		public:

			/****************************** Contructors & Destructors ******************************/
		public:

		private:
			/**
			* No access to the default constructor.
			*/
			ThreadPool();

			/**
			* No access to the copy constructor.
			*/
			ThreadPool(const ThreadPool& tp);

			/**
			* No access to the virtual destructor.
			*/
			virtual ~ThreadPool();

			/****************************** Methods ******************************/
		private:

		protected:

		public:
			/**
			* Returns the singleton object.
			*
			* @return The unique singleton object.
			*/
			static ThreadPool* s();

			/**
			* Initializes the pool by creating the necessary threads.
			*
			* @param min The minimum amount of threads desired.
			* @param max The maximum amount of threads desired.
			* @return True if it was successful, false if some error happened.
			*/
			void init(unsigned short min, unsigned short max);

			/**
			* Destroys both the threads and the jobs of the thread pool.
			*/
			void close();

			/**
			* Adds a new task to the task list with the given parameters.
			*
			* @param t The job to perform.
			* @param d The data to be sent to the job.
			*/
			void addTask(TaskJob t, TaskData* d);

			/**
			* Flags the process variable to start the thread pool work.
			*/
			void start();

			/**
			* Flags the process variable to stop the thread pool work.
			*/
			void stop();

			/**
			* Returns the number of active threads currently working.
			*
			* @return The number of active threads currently working.
			*/
			unsigned int getActiveThreads();

			/**
			* Returns the number of slacking threads (no work).
			*
			* @return The number of slacking threads (no work).
			*/
			unsigned int getSlackingThreads();

			/**
			* Returns true if the task list is not empty (there are jobs), false if not.
			*
			* @return True if the task list is not empty, false if not.
			*/
			bool hasWaitingTasks();

			/**
			* Returns true if the process flag is true (the thread pool is working), false if not.
			*
			* @return True if the process flag is true, false if not.
			*/
			bool isProcessing();
			
			/****************************** Operators Overloading ******************************/
		private:
			/**
			* No access to the equals operator.
			*
			* @param tp The supposed thread pool object to copy.
			*/
			ThreadPool& operator=(const ThreadPool& tp);

		protected:

		public:

		};
	}
}

#endif