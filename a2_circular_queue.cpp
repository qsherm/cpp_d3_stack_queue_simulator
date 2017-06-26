#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "a2_circular_queue.hpp"


typedef CircularQueue::QueueItem QueueItem;
const QueueItem CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue() : size_(0), head_(0), tail_(0), capacity_(16)
{
	//Allocate memory, initialize head and tail to 0 since queue is empty
	items_ = new QueueItem[16];
}

CircularQueue::CircularQueue(unsigned int capacity) : size_(0), head_(0), tail_(0), capacity_(capacity)
{
	items_ = new QueueItem[capacity];
}

CircularQueue::~CircularQueue()
{
	delete [] items_;
}

bool CircularQueue::empty() const
{
	return size_ == 0;    
}

bool CircularQueue::full() const
{
	return size_ == capacity_;
}

int CircularQueue::size() const
{ 
	return size_; 
}

bool CircularQueue::enqueue(QueueItem value)
{
	//Do not enqueue to full queue
	if (this->full())
		return false;
	//Queue value, increment tail & mod by capacity in case array bounds are exceeded
	items_[tail_] = value;
	tail_ = (tail_ + 1) % capacity_;
	size_++;
	return true;
}

QueueItem CircularQueue::dequeue()
{
	//Handle empty queue
	if (this->empty())
		return EMPTY_QUEUE;
	//Increment head, mod by capacity in case array bounds are exceeded
	head_ = (head_ + 1) % capacity_;
	size_--;
	//Return item before new head, mod in case value is negative
	return items_[((head_ - 1) + capacity_) % capacity_];
}

QueueItem CircularQueue::peek() const
{
	return (this->empty() ? EMPTY_QUEUE : items_[head_]);
}

void CircularQueue::print() const
{
	std::ofstream fout("data.js");
	fout << "var type = 'queue';\nvar head = " << head_ << ";\nvar tail = " << tail_ << ";\nvar size = " << size_ << ";\nvar data = [";
	for (int i = 0; i < capacity_; i++)
		fout << items_[i] << (i == capacity_ - 1 ? "" : ",");
	fout << "];";
	fout.close();
	
	ShellExecute(NULL, "open", "visualizer.html", NULL, NULL, SW_SHOWNORMAL);
	
	std::cout << "{ ";
	//Print for the number of items in queue, starting from head
	//Mod by capacity in case array bounds are exceeded
	for (int i = 0; i < size_; i++)
		std::cout << (head_ + i) % capacity_ << ":" << items_[(head_ + i) % capacity_] << " ";
	std::cout << "}\n";	
}

