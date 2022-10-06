#pragma once
struct EntryInt {
	int			value = 0;

	EntryInt*	prev = nullptr;
	EntryInt*	next = nullptr;

	~EntryInt();
};

class LinkedListInt
{
public:
	void insert(int val);
	void remove(int val);
	void print(); //prints the list with printf
protected:
	EntryInt* root = nullptr;
};
