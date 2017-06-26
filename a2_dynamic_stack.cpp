#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "a2_dynamic_stack.hpp"

typedef DynamicStack::StackItem StackItem;  // for simplicity
const StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack() : size_(0), capacity_(16), init_capacity_(16)
{
	items_ = new StackItem[16];
}

DynamicStack::DynamicStack(unsigned int capacity) : size_(0), capacity_(capacity), init_capacity_(capacity)
{
	items_ = new StackItem[capacity];	
}

DynamicStack::~DynamicStack()
{
	delete [] items_;
}

bool DynamicStack::empty() const
{
	return size_ == 0;
}

int DynamicStack::size() const
{
	return size_;
}

void DynamicStack::push(StackItem value)
{
	//If stack capacity is exceeded, create a new stack with twice the capacity,
	//Copy all values into it, delete the old stack and set items_ to the new stack
	if (size_ == capacity_)
	{
		capacity_ *= 2;
		StackItem* new_stack = new StackItem[capacity_];
		for (int i = 0; i < size_; i++)
			new_stack[i] = items_[i];
		delete [] items_;
		items_ = new_stack;
	}
	//Insert item
	items_[size_] = value;
	size_++;
}

StackItem DynamicStack::pop()
{
	//Handle empty stack
	if (this->empty())
		return EMPTY_STACK;
	//Decrement stack. If new size is less than or equal to one quarter of the current capacity AND 
	//The capacity is greater than the initial capacity, create a new stack with on half the current stack's capacity,
	//copy all values into it, delete the old stack and set items_ to the new stack
	size_--;
	if (capacity_ > init_capacity_ && size_ <= capacity_ * 0.25)
	{
		capacity_ /= 2;
		StackItem* new_stack = new StackItem[capacity_];
		for (int i = 0; i < size_ + 1; i++)
			new_stack[i] = items_[i];
		delete [] items_;
		items_ = new_stack;
	}
	//Return item popped from stack
	//(It does not need to be deleted, it will be overwritten if push() is called)
	return items_[size_];
}

StackItem DynamicStack::peek() const
{
	return (this->empty() ? EMPTY_STACK : items_[size_ - 1]);
}

void DynamicStack::print() const
{
	std::ofstream fout("data.js");
	fout << "var type = 'stack'";
	fout.close();
	
	ShellExecute(NULL, "open", "visualizer.html", NULL, NULL, SW_SHOWNORMAL);
	std::cout << "{ ";
	//Print from top of stack to bottom
	for (int i = size_ - 1; i > 0; i--)
		std::cout << items_[i] << " ";
	std::cout << "}\n";
}

