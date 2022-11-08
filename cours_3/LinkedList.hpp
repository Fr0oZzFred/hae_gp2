using namespace std;

template<typename T>
struct Node {
	Node(T val) {
		key = val;
	};
	~Node() {
		cout << "Removed" << "\n";
	};
public:
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
	int remove(T val);
	int remove(Node<T>* n);
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
inline int LinkedList<T>::remove(T val) {
	Node<T>* n = get(val);
	if(n)	return remove(get(val));
	return -1;
};

template<typename T>
inline int LinkedList<T>::remove(Node<T>* n) {
	if (n == head) {
		Node <T>* next = head->next;
		head = next;
		delete n;
		return 1;
	}

	//Node<T>* cur = head;
	//while (cur->next) {
	//	if (cur == n) {
	//
	//	}
	//}


	return -1;
};