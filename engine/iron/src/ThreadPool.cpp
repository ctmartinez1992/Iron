#include "ThreadPool.h"
#include "Thread.h"
#include <iostream>
#include <string>

//TODO Arrange this mess.

namespace iron {

	namespace thread {

		ThreadPool*			ThreadPool::_s = nullptr;

		ThreadPool::ThreadPool() 
			: taskList(), threads(), active(false), process(false)
		{
		}

		ThreadPool::ThreadPool(const ThreadPool& tp) {
		}

		ThreadPool::~ThreadPool() {
			close();
		}
		
		ThreadPool* ThreadPool::s() {
			if (_s == nullptr) {
				_s = new ThreadPool();
			}

			return _s;
		}

		void ThreadPool::init(unsigned short min, unsigned short max) {
			//Create the threads.
			threads.assign(min, nullptr);

			//Initialize the minimum number of threads desired.
			for (int i = 0; i < min; ++i) {
				threads[i] = new Thread();
				threads[i]->init();
				if (threads[i]->isRunning()) {
					++active;
				}
			}

			//Try to initialize thread until it hits the maximum number.
			for (int i = min; i < max; ++i) {
				Thread* t = new Thread();
				t->init();
				if (t->isRunning()) {
					threads.push_back(t);
					++active;
				} else {
					delete t;
					break;
				}
			}

			iron::Log::s()->logInfo("The Thread Pool was initialized with " + 
				std::to_string(getActiveThreads()) + " threads.", __LINE__, 
				std::string(__FUNCTION__), std::string(__FILE__));
		}

		void ThreadPool::close() {
			process = false;

			Task* task;
			Thread* thread;

			//Kill threads.
			while (!threads.empty()) {
				thread = threads.back();
				threads.pop_back();
				thread->close();
				delete thread;
			}

			//Kill jobs.
			while (!taskList.empty()) {
				task = taskList.pop();
				delete task;
			}

			active = 0;

			iron::Log::s()->logInfo("The Thread Pool was killed.", __LINE__,
				std::string(__FUNCTION__), std::string(__FILE__));
		}

		void ThreadPool::addTask(TaskJob t, TaskData* d) {
			Task* task = new Task(t, d);
			taskList.push(task);

			iron::Log::s()->logDebug("A new job was added to the thread pool.", __LINE__,
				std::string(__FUNCTION__), std::string(__FILE__));
		}

		void ThreadPool::start() {
			process = true;
		}

		void ThreadPool::stop() {
			process = false;
		}

		unsigned int ThreadPool::getActiveThreads() {
			return active;
		}

		unsigned int ThreadPool::getSlackingThreads() {
			unsigned int slack = 0;
			for (unsigned int i = 0; i < threads.size(); ++i) {
				if (threads[i]->isSlacking()) {
					++slack;
				}
			}

			return slack;
		}

		bool ThreadPool::hasWaitingTasks() {
			return !taskList.empty();
		}

		bool ThreadPool::isProcessing() {
			return process;
		}
	}
}