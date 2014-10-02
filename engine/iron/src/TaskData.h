#ifndef IRON_THREAD_TASK_DATA_H_
#define IRON_THREAD_TASK_DATA_H_

namespace iron {

	namespace thread {

		/*! \brief Contains a function pointer (typedef) and the abstract base class. Basically,
		*  it's a namespace to hold smaller data structures.
		*
		*  TaskJob is a function pointer and represents the job we want to run on another thread.
		*  The job can be defined anywhere on the program. The job (function pointer) returns void for 
		*  simplicity sake. The function sent to the function pointer must be static for it to work correctly.
		*  Here is an example of the basic functionality:
		*
		*  Create a task derived from TaskData:
		*
		*      class ThreadTask : TaskData {
		*      public:
		*          Foo* f;
		*          void* something;
		*          //stuff
		*      }
		*
		*  Create a class with the work and the task to be called:
		*
		*      class Foo {
		*      public:
		*	       void workTask(void* something) {
		*              //stuff
		*          }
		*  
		*          static void TASK_RUN(ThreadWork* task) {
		*              task->f->workTask(task->something);
		*          }
		*      }
		*
		*  Inside class Foo, when needed, call:
		*
		*      threadpool->AddTask(TASK_RUN, new ThreadWork(this, "something"));
		*
		*  TaskData exists to allow the passage of data safely. Derive classes from this one, add the
		*  variables you want to pass to other threads.
		*/
		class TaskData {

			/****************************** Contructors & Destructors ******************************/
		public:
			/**
			* Default constructor.
			*/
			TaskData() {}

			/**
			* Copy constructor.
			*
			* @param c The object to copy.
			*/
			TaskData(const TaskData& c) {}

			/**
			* Virtual destructor.
			*/
			virtual ~TaskData() = 0 {};

		private:

			/****************************** Operators Overloading ******************************/
		private:

		protected:

		public:
			/**
			* The equals operator.
			*
			* @param c The object to copy.
			*/
			TaskData& operator=(const TaskData& c) {}

		};

		/**
		* The type definition that makes the following function call possible: job(data).
		*/
		typedef void (*TaskJob)(TaskData*);
	}
}

#endif