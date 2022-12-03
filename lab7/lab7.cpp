#include <iostream>

using namespace std;
class Node {
public:
	Node* pnext;
	int data;
	Node(int data, Node* pNext = nullptr) {
		this->data = data;
		this->pnext = pNext;
	}
};
//Список
class List {
protected:
	Node* head;
	int Size;
public:
	List();
	~List();

	static int countpopfront;
	void AddFront(int data);
	void AddEnd(int data);
	int GetSize() { return Size; }
	int operator[](const int index);
	void clear();
	void pop_front();
};

int List::countpopfront = 0;

List::List() {
	Size = 0;
	head = nullptr;
}

List::~List() {
	clear();
}

void List::AddFront(int data) {
	head = new Node(data, head);
	Size++;
}

void List::AddEnd(int data) {
	if (head == nullptr) {
		head = new Node(data);
	}
	else {
		Node* cur = this->head;

		while (cur->pnext != nullptr)
		{
			cur = cur->pnext;
		}
		cur->pnext = new Node(data);
	}
	Size++;
}

int List::operator[](const int index)
{
	if (index < 0 || index > Size) {
		throw index;
	}
	int counter = 0;
	Node* cur = this->head;
	while (cur != nullptr) {
		if (counter == index) {
			return cur->data;
		}
		cur = cur->pnext;
		counter++;
	}
	return 0;
}

void List::pop_front() {
	Node* temp = head;
	head = head->pnext;
	delete(temp);
	Size--;
	countpopfront++;
}

void List::clear() {
	while (Size) {
		pop_front();
	}
}

//Стек
class Stack :public List {
public:
	Stack();
	Stack(int data, Node* pnext);
	~Stack();
};

Stack::Stack(int data, Node* pnext) {
	Size = 1;
	head = new Node(data, head);
}

Stack::Stack() {
	Size = 0;
	head = nullptr;
}


Stack::~Stack() {
	clear();
}

//Очередь
class Queue :public List {
public:
	Queue();
	~Queue();
};

Queue::Queue() {
	Size = 0;
	head = nullptr;
}

Queue::~Queue() {
	clear();
}

int main() {

	List list;
	Stack stack, stack1(11, nullptr), stack2;
	Queue queue, queue1, queue2;

	int choose = 0, index = 0;
	cout << "1 - List ; 2 - Stack ; 3 - Queue\n";
	cin >> choose;

	switch (choose)
	{
	case 1:
		cout << "====List====\n";
		list.AddEnd(10);
		list.AddEnd(15);
		list.AddEnd(20);
		list.AddEnd(25);
		list.AddEnd(30);
		list.AddEnd(35);
		list.AddFront(0);
		for (int i = 0; i < list.GetSize(); i++) {
			cout << "[" << i << "] - ";
			cout << list[i] << " ";
		}
		cout << "\nSize - " << list.GetSize() << "\n";
		cout << "Input index of element ";
		cin >> index;
		try {
			cout << "Value - " << list[index] << "\n";
		}
		catch (const int ex) {
			cout << "\nThere is no element under this index!\n";
		}
		break;
	case 2:
		cout << "====Stack====\n";
		stack2.AddFront(2);
		stack2.AddFront(3);
		stack2.AddFront(4);
		stack1.AddFront(5);
		stack1.AddFront(6);
		stack1.AddFront(7);
		stack1.AddFront(8);
		stack1.AddFront(9);
		stack1.AddFront(10);
		stack2.AddFront(11);
		stack2.AddFront(12);
		stack2.AddFront(13);
		stack2.AddFront(14);
		stack2.AddFront(15);

		cout << "====First stack====\n";
		for (int i = 0; i < stack1.GetSize(); i++) {
			cout << stack1[i] << "\n";
		}
		cout << "====Second stack====\n";
		for (int i = 0; i < stack2.GetSize(); i++) {
			cout << stack2[i] << "\n";
		}

		for (int i = stack1.GetSize() - 1; i >= 0; i--) {
			stack.AddFront(stack1[i]);
		}
		for (int i = stack2.GetSize() - 1; i >= 0; i--) {
			stack.AddFront(stack2[i]);
		}
		cout << "====Final stack====\n";
		for (int i = 0; i < stack.GetSize(); i++) {
			cout << stack[i] << "\n";
		}
		break;

	case 3:
		cout << "====Queue====\n";
		queue1.AddEnd(10);
		queue1.AddEnd(15);
		queue1.AddEnd(20);
		queue1.AddEnd(25);
		queue1.AddEnd(30);
		queue1.AddEnd(0);
		queue2.AddEnd(50);
		queue2.AddEnd(55);
		queue2.AddEnd(60);
		queue2.AddEnd(65);
		queue2.AddEnd(70);
		queue2.AddEnd(1);
		for (int i = 0; i < queue1.GetSize(); i++) {
			queue.AddFront(queue1[i]);
		}
		for (int i = 0; i < queue2.GetSize(); i++) {
			queue.AddEnd(queue2[i]);
		}
		for (int i = 0; i < queue.GetSize(); i++) {
			cout << queue[i] << " ";
		}
		cout << "\nAfter first pop\n";
		queue.pop_front();
		for (int i = 0; i < queue.GetSize(); i++) {
			cout << queue[i] << " ";
		}
		cout << "\nAfter second pop\n";
		queue.pop_front();
		for (int i = 0; i < queue.GetSize(); i++) {
			cout << queue[i] << " ";
		}
		cout << "\n";
		cout << "\nNumber of extracted elements - " << list.countpopfront << "\n";
		break;
	default:
		break;
	}

	return 0;
}