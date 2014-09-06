#include "Thread.h"

namespace iron {

	namespace thread {

		Thread::Thread() 
			: tLock(), threadHandle(nullptr), exitCode(0), id(0), running(false), noWork(true)
		{
		}

		Thread::~Thread() {
			if (threadHandle != nullptr) {
				close();
			}
		}

		void Thread::clearTask() {
			delete task;
			task = nullptr;
		}

		void Thread::setTask(Task* ptr) {
			if (ptr == nullptr) {
				iron::Log::s()->logWarning("NULL ptr was passed.", __LINE__, std::string(__FUNCTION__),
					std::string(__FILE__));
				return;
			}

			task = ptr;
			noWork = false;
		}
		
		DWORD Thread::proc() {
			task = nullptr;

			//Akin to a game loop, if the thread is inside this loop, it's still alive.
			while (running) {
				Sleep(1);

				//Thread pauses when a job is finished and is resumed when it gets another job.
				if (task != nullptr) {
					tLock.lock();
					{
						TaskJob job = task->getJob();
						TaskData* data = task->getData();

						//Work it!
						if (job != nullptr && data != nullptr) {
							job(data);
						}

						//Done.
						clearTask();
					}
					tLock.unlock();
				}

				//If no task is assigned, get the next one.
				if (task == nullptr && pool->isProcessing() && pool->hasWaitingTasks()) {
					task = pool->taskList.pop();
					noWork = false;
				}

				//Check if there is work at all.
				if (!pool->hasWaitingTasks()) {
					noWork = true;
				}
			}

			return 0;
		}

		DWORD Thread::getExitCode()	{
			return exitCode; 
		}

		unsigned int Thread::getThreadID() {
			return id;
		}

		bool Thread::init() {
			pool = ThreadPool::s();

			#ifdef WIN32
				//Start the thread. The following link is a good summary on Windows thread creation:
				//http://www.tenouk.com/ModuleS.html
				threadHandle = (HANDLE)_beginthreadex(nullptr, 0, &cThreadProc, (void*)this, 0, &id);
				running = true;

				//Check for errors on creation.
				if (threadHandle == nullptr) {
					iron::Log::s()->logError("There was an unknown problem creating a thread. Probably "
						"there's no more space for thread creation.", __LINE__,
						std::string(__FUNCTION__), std::string(__FILE__));
					running = false;
					return false;
				}
				if (threadHandle == 0) {
					int error = errno;
					int errorDOS = _doserrno;
					iron::Log::s()->logError("There was an error creating a thread. Error nº " +
						std::to_string(errno) + " - DOS Error nº " + std::to_string(errorDOS), __LINE__,
						std::string(__FUNCTION__), std::string(__FILE__));
					running = false;
					return false;
				}
			#endif
				
			iron::Log::s()->logInfo("A new thread[" + std::to_string(id) + "] was created.", __LINE__,
				std::string(__FUNCTION__), std::string(__FILE__));
				
			return true;
		}

		bool Thread::close() {
			bool closed = true;

			#ifdef WIN32
				if (threadHandle != nullptr) {
					running = false;

					//Wait for a signaled state.
					DWORD waitReturn = WaitForSingleObject(threadHandle, INFINITE);
					if (waitReturn == WAIT_ABANDONED) {
						iron::Log::s()->logDebug("The thread[id:" + std::to_string(id) + "] has "
							"waited for signal successfully because of the following: The specified object "
							"was a mutex object that was not released by the thread that owned the mutex "
							"object before the owning thread terminated.", __LINE__,
							std::string(__FUNCTION__), std::string(__FILE__));
					}
					if (waitReturn == WAIT_TIMEOUT) {
						iron::Log::s()->logDebug("The thread[id:" + std::to_string(id) + "] has "
							"waited for signal successfully because of the following: The time-out interval "
							"elapsed. A time-out should never happen, this might be problematic", __LINE__, 
							std::string(__FUNCTION__), std::string(__FILE__));
					}
					if (waitReturn == WAIT_FAILED) {
						iron::Log::s()->logError("The thread[id:" + std::to_string(id) + "] has "
							"waited for signal UNsuccessfully with the following error: " + 
							std::to_string(GetLastError()) + ".", __LINE__, std::string(__FUNCTION__), 
							std::string(__FILE__));
						closed = false;
					}

					//Obtain the thread exit status.
					if (GetExitCodeThread(threadHandle, &exitCode)) {
						iron::Log::s()->logDebug("The thread[id:" + std::to_string(id) + "] retrieved "
							"the thread status successfully.", __LINE__, std::string(__FUNCTION__), 
							std::string(__FILE__));
					} else {
						iron::Log::s()->logError("The thread[id:" + std::to_string(id) + "] retrieved "
							"the thread status UNsuccessfully with the following error: " +
							std::to_string(GetLastError()) + ".", __LINE__, std::string(__FUNCTION__),
							std::string(__FILE__));
						closed = false;
					}

					//Close the open thread object handle.
					if (CloseHandle(threadHandle)) {
						iron::Log::s()->logDebug("The thread[id:" + std::to_string(id) + "] handle was "
							"closed successfully.", __LINE__, std::string(__FUNCTION__), 
							std::string(__FILE__));
					} else {
						iron::Log::s()->logError("The thread[id:" + std::to_string(id) + "] retrieved "
							"the thread status UNsuccessfully with the following error: " +
							std::to_string(GetLastError()) + ".", __LINE__, std::string(__FUNCTION__),
							std::string(__FILE__));
						closed = false;
					}

					threadHandle = nullptr;
				}
			#endif


			if (closed) {
				iron::Log::s()->logInfo("The thread[id:" + std::to_string(id) + "] was stopped and "
					"closed successfully.", __LINE__, std::string(__FUNCTION__), std::string(__FILE__));
				return true;
			}

			iron::Log::s()->logInfo("The thread[id:" + std::to_string(id) + "] was stopped and "
				"closed but there were some problems, see previous log messages.", __LINE__, 
				std::string(__FUNCTION__), std::string(__FILE__));
			return false;
		}
		
		void Thread::lock() {
			tLock.lock();
		}

		void Thread::unlock() {
			tLock.unlock();
		}

		bool Thread::isRunning() {
			return running;
		}

		bool Thread::isSlacking() {
			return noWork;
		}
	}
}