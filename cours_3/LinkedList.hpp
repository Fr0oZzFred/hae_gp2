using namespace std;

template<typename T>
struct Node {

public:

	Node(T val) {
		key = val;
	};
	~Node() {
		cout << "Removed" << "\n";
	};

	T		key = {};
	Node*	next = nullptr;
};

template<typename T>
class LinkedList {
public:
	void print();
	void push_front(T val);
	void push_front(Node<T> * n);
	void push_back(T val);
	void push_back(Node<T> * n);
	Node<T> * get(T val);
	int removeOne(T val);
	int removeOne(Node<T>* n);
	int removeAll(T val);
	int removeAll(Node<T>* n);
protected:
	Node<T> *	head = nullptr;
};

typedef LinkedList<int> IntList;
typedef LinkedList<float> FloatList;


template<typename T>
inline void LinkedList<T>::print() {
	Node<T>* cur = head;
	cout << "[ ";
	while (cur) {
		cout << cur->key << " ";
		cur = cur->next;
	}
	cout << "]" << "\n";
}
template<typename T>
inline void LinkedList<T>::push_front(T val) {
	Node<T>* nuNode = new Node<T>(val);
	push_front(nuNode);
};

template<typename T>
inline void LinkedList<T>::push_front(Node<T> * n) {
	if (!head) {
		head = n;
		return;
	}

	n->next = head;
	head = n;
};

template<typename T>
inline void LinkedList<T>::push_back(T val) {
	Node<T>* nuNode = new Node<T>(val);
	push_back(nuNode);
};

template<typename T>
inline void LinkedList<T>::push_back(Node<T> * n) {
	if (!head) {
		head = n;
		return;
	}

	Node<T> * cur = head;
	while (cur->next) cur = cur->next;
	cur->next = n;
}

template<typename T>
inline Node<T>* LinkedList<T>::get(T val) {
	Node<T>* cur = head;
	while (cur) {
		if (cur->key == val)	return cur;
		cur = cur->next;
	}
								return nullptr;
};

template<typename T>
inline int LinkedList<T>::removeOne(T val) {
	Node<T>* n = get(val);
	if(n)	return removeOne(get(val));
	return -1;
};

template<typename T>
inline int LinkedList<T>::removeOne(Node<T>* n) {
	if (n == head) {
		Node <T>* next = head->next;
		head = next;
		delete n;
		return 1;
	}

	Node<T>* cur = head->next;
	Node<T>* prev = head;
	while (cur) {
		if (cur == n) {
			if (cur->next) prev->next = cur->next;
			else prev->next = nullptr;
			delete cur;
			return 1;
		}
		prev = cur;
		cur = cur->next;
	}
	return -1;
}
template<typename T>
inline int LinkedList<T>::removeAll(T val) {
	Node<T>* n = get(val);
	if (n)	return removeAll(get(val));
	return -1;
};
template<typename T>
inline int LinkedList<T>::removeAll(Node<T>* n) {
	if (n == head) {
		while (head->next) {
			Node <T>* next = head->next;
			delete head;
			head = next;
		}
		head = nullptr;
		return 1;
	}

	Node <T>* cur = head->next;
	Node <T>* prev = head;
	while (cur) {
		if (cur == n) {
			while (cur->next) {
				Node <T>* next = cur->next;
				delete cur;
				cur = next;
			}
			prev->next = nullptr;
			return 1;
		}
		prev = cur;
		cur = cur->next;
	}
	return -1;
};