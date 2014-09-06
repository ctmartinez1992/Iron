#ifndef IRON_THREAD_TASK_H_
#define IRON_THREAD_TASK_H_

#include "TaskData.h"

namespace iron {

	namespace thread {

		/*! \brief Holds the necessary task data to execute the job.
		*
		*  Simple class with the aspect that once the Task is constructed, it can no longer be changed.
		*/
		class Task {

			/****************************** Variables ******************************/
		private:
			TaskJob			job;		/*!< The work to do. */

			TaskData*		data;		/*!< The TaskData object. */

		protected:

		public:

			/****************************** Contructors & Destructors ******************************/
		public:
			/**
			* Constructs a new task with the given job and the task data.
			*
			* @param j The job to do.
			* @param d The task data.
			*/
			Task(TaskJob j, TaskData* d) {
				job = j;
				data = d;
			}

			/**
			* Destructor.
			*/
			~Task() {
				if (data != nullptr) {
					delete data;
				}

				job = nullptr;
				data = nullptr;
			}

		private:

			/****************************** Methods ******************************/
		private:

		protected:

		public:
			/**
			* Returns the task job.
			*
			* @return The task job.
			*/
			TaskJob	getJob() {
				return job; 
			}

			/**
			* Returns the task data.
			*
			* @return The task data.
			*/
			TaskData* getData()	{
				return data; 
			}

		};
	}
}
#endif