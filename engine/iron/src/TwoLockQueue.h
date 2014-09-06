//Thread-Safe Two-Lock Queue.
//Based on the algorithm done by Maged M. Michael & Michael L. Scott, in 1996. Worth the reading!
//http://www.cs.rochester.edu/u/scott/papers/1996_PODC_queues.pdf

#ifndef IRON_THREAD_TWO_LOCK_QUEUE_H_
#define IRON_THREAD_TWO_LOCK_QUEUE_H_

#include "ThreadLock.h"

namespace iron {

	namespace thread {

		/*! \brief Two-lock queue that is thread-safe, simple and fast.
		*
		*  This class is based on queue presente din 1996 and it's perfect for what is necessary.
		*  The queue is based on nodes/linked lists and two locks that ensure thread-safety. Standard
		*  behaviour is to simply use the push and pop function to add the tasks and the queue will
		*  handle everything else and will make sure there are no problem of nullptrs or empty queue.
		*
		*  This queue was created to be used in a concurrent environment and store jobs. However, it's also
		*  a template, which means it can be used for anything.
		*
		* (Following text based on the paper described at the top of this file (page 3))
		*
		* Linked list that provides some safety in the following aspects.
		*
		* 1- The list is always connected because when a node is inserted, the next pointer 
		* is not set to nullptr before it's freed and no node is freed until it's deleted.
		*
		* 2- Nodes are inserted after the last node in the list because they are inserted after
		* the node pointed to by the tail and tail always points to the last node unless it's
		* protected by the tail lock.
		*
		* 3- Nodes are deleted from the beginning of the list because they are deleted only when
		* they are pointed by head and head always points to the beginning of the list.
		*
		* 4- Head always points to the first node in the list because it only changes its value
		* to the next node atomically.
		*
		* 5- Tail always points to a node in the list because it never falls behind head.
		*
		*  For commentaries regarding the code/algorithms, check the link to the paper in this comment.
		*
		*  the paper from which the queue was based:
		*  http://www.cs.rochester.edu/u/scott/papers/1996_PODC_queues.pdf
		*/
		template<typename DataType>
		class TwoLockQueue {

			/****************************** Variables ******************************/
		private:
			/**
			*/
			struct QueueNode {
				DataType		element;	/*!< The stored element. */
				QueueNode*		next;		/*!< The element following the stored element. */

				/**
				* Contructor that stores the given element and a pointer to the next node.
				*
				* @param e The element to be stored.
				* @param n The next element.
				*/
				QueueNode(DataType e, QueueNode* n)
					: element(e), next(n)
				{
				}
				
				/**
				* Contructor that stores the given element and the next pointer is assigned to nullptr.
				*
				* @param e The element to be stored.
				*/
				QueueNode(DataType e)
					: element(e), next(nullptr)
				{
				}
			};

			QueueNode*		head;			/*!< The head (first) node of the list. */

			QueueNode*		tail;			/*!< The tail node of the list. */

			ThreadLock		headLock;		/*!< Ensure proper concurrency on the pop function. */

			ThreadLock		tailLock;		/*!< Ensure proper concurrency on the push function. */

		protected:

		public:

			/****************************** Contructors & Destructors ******************************/
		public:
			/**
			* Initializes the queue.
			*/
			TwoLockQueue() {
				QueueNode* dummy = new QueueNode(nullptr, nullptr);
				head = tail = dummy;
			}

			/**
			* Destroys queue and its contents.
			*/
			~TwoLockQueue() {
				while (pop());
				delete head;
			}

		private:
			/**
			* Don't allow constructor copies.
			*
			* @param c The supposed TwoLockQueue object to be copied.
			*/
			TwoLockQueue(TwoLockQueue& c) {}

			/****************************** Methods ******************************/
		private:

		protected:

		public:
			/**
			* Safely pushes the given element into the bottom of the list.
			*
			* @param e The element to store.
			*/
			void push(DataType e) {
				QueueNode* n = new QueueNode(e);
				
				tailLock.lock();
				{
					tail->next = n;
					tail = n;
				}
				tailLock.unlock();
			}

			/**
			* Safely pops the first element of the list.
			*
			* @return The popped element.
			*/
			DataType pop() {
				QueueNode* n;
				DataType v;

				headLock.lock();
				{
					n = head;
					QueueNode* newHead = n->next;
					if (newHead == nullptr) {
						headLock.unlock();
						return nullptr;
					}

					v = newHead->element;
					head = newHead;
				}
				headLock.unlock();

				delete n;
				return v;

			}

			/**
			* Returns true if the list is empty, false if not.
			*
			* @return True if the list is empty, false if not.
			*/
			bool empty() {
				return head->next == nullptr;
			}

			/****************************** Operators Overloading ******************************/
		private:
			/**
			* Don't allow operator copies.
			*
			* @param c The supposed TwoLockQueue object to be copied.
			*/
			TwoLockQueue& operator=(TwoLockQueue& c) {}

		protected:

		public:

		};
	}
}

#endif