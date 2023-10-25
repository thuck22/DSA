#include "main.h"

class Queue {
public:
	class customer {
			public:	
				string name;
				int energy;
				customer* prev;
				customer* next;
			public:
				customer(){}
				customer(string na, int e, customer* p, customer *ne): name(na), energy(e), prev(p), next(ne){}
				~customer(){}
				void print() {
					cout << name << "-" << energy << endl;
				}
			};
	class Node {
	public:
		customer * cus;
		Node *pre;
		Node*next;
	public:
		Node (customer *c = NULL,Node *p = NULL, Node * n = NULL) :cus(c),pre(p), next(n) {}
		~Node () {}
	};

	Node * head;
	Node *tail;
    Node * current;
	int count;
	friend class imp_res;
public:
	Queue(): head(NULL),tail(NULL),current(NULL),count(0){}
	~Queue() {
		clear();
	}
    void addCir(customer &cus,int num = 0) {
        count++;
        if(count == 0) {
            current = new Node(&cus,NULL,NULL);
            current->pre = current;
            current->next = current;
        }
        else if(num > 0) {
            Node  * p = new Node(&cus,current,current->next);
            current->next->pre = p;
            current->next = p;
            current = p;
        }
        else {
            Node * p = new Node (&cus,current->pre,current) ;
            current->pre->next = p;
            current->pre = p;
            current = p;
        }
    }
	void add (customer &cus) {
		if(count == 0) {
			head = new Node(&cus,NULL,NULL);
			tail = head;
			count++;
		}
		else {
			tail->next = new Node(&cus,tail, NULL);
			tail = tail->next;
			count++;
		}
	}
	void clear() {
		if(head == NULL) {
			while(current) {
				Node * p = current->next;
				delete current;
				current = p;
			}
		}
		else {
			while(head) {
				Node *p = head->next;
				delete head;
				head = p;
			}
		}
		count = 0;
		tail = NULL;
	}
    void setCurrent(Node * p) {
        this->current = p;
    }
	customer * remove () {
		count--;
		Node * p = head;
		head = head->next;
		head->pre = NULL;
		customer * temp = p->cus;
		delete p;
		return temp;
	}
	void removeCir(customer * cus) {
		count--;
		Node * p = current->next;
		if(current->cus == cus) {
			p = current;
			current->pre->next = current->next;
			current->next->pre = current->pre;
			if(p->cus->energy > 0) current = p->next;
			else current = p->pre;
			delete cus;
			delete p;
		}
		while(p != current) {
			if(p->cus == cus) {
				p->pre->next = p->next;
				p->next->pre = p->pre;
				if(p->cus->energy > 0) current = p->next;
				else current = p->pre;
				delete cus;
				delete p;
				break;
			}
			p = p->next;
		}
	}
	Node * ind(int index) {
		Node *p = head;
		if(index > count || index < 0) throw "Segmentation fail!";
		else if(index == 0) {
			return head;
		}
		else {
			while(index) {
				index--;
				p = p->next;
			}
			return p;
		}
	}
	bool prior(Node *p, Node *q) {
		Node * ptr = head;
		while(ptr != q) {
			if(ptr == p) return 1;
			ptr = ptr->next;
		}
		return 0;
	}
	int insSort2(int n, int incr) {
		int cnt = 0;
		for(int i = incr; i < n; i += incr) {
			for(int j =i ; j >= incr && prior(ind(j),ind(j-incr)); j -= incr ) {
				Node *p = ind(j);
				Node * ptr = ind(j -incr);
				customer *temp = p->cus;
				p->cus = ptr->cus;
				ptr->cus = temp;
				cnt++;
			}
		}
		return cnt;
	}
	int shellSort(int n) {
		int cnt = 0;
		for(int i = n/2; i > 2; i /= 2) {
			for(int j =0; j < i; j++) {
				cnt += insSort2(n-j,i);
			}
			cnt += insSort2(n,1);
		}
		return cnt;
	}
};

class imp_res : public Queue
{
    public: 
        Queue *qtime;
        Queue * q;
        Queue * qcho;
	public:	
		imp_res() {
            qtime = new Queue();
            q = new Queue();
            qcho = new Queue();
        }
        ~imp_res() {
            qtime->clear();
            qcho->clear();
            q->clear();
        }
        bool checkName(string name);
		void RED(string name, int energy);
		void BLUE(int num);
		void PURPLE();
		void REVERSAL();
		void UNLIMITED_VOID();
		void DOMAIN_EXPANSION();
		void LIGHT(int num);
};


//implementation
bool imp_res::checkName(string name) {
    Node * p = q->current->next;
    if(q->current->cus->name == name) return 1;
    while(p != q->current) {
		if(p->cus->name == name) return 1;
		p = p->next;
	}
	return 0;
}

void imp_res::RED(string name, int energy) {
	cout << name << " " << energy << endl;
	customer *cus = new customer (name, energy, nullptr, nullptr);
    if(energy == 0) ;
    else if(checkName(name)) ;
    else if(q->count == 0) {
        q->addCir(*cus);
        qtime->add(*cus);
    }
    else if(q->count < MAXSIZE/2 && q->count > 0) {
        qtime->add(*cus);
        Node * p = q->current;
        Node * n = p->next, * s;
        int max = -1e9;
        for(int i =0; i < q->count; i++) {
            if((abs(p->cus->energy) - abs(n->cus->energy)) > max) {
                max = (abs(p->cus->energy) - abs(n->cus->energy));
                s = p;
            }
            p = p->next;
            n = p->next;
        }
        if(s->cus->energy - s->next->cus->energy < 0) {
            q->setCurrent(s);
            q->addCir(*cus,-1);
        }
        else {
            q->setCurrent(s);
            q->addCir(*cus,1);
        }
    }
    else if(q->count == MAXSIZE && qcho->count == MAXSIZE) ;
    else if(q->count >= MAXSIZE) {
        qcho->add(*cus);
    }
}

void imp_res::BLUE(int num) {
    cout << "blue "<< num << endl;
	if(num >= q->count) {
		qtime->clear();
		q->clear();
	}
	else {	
		while(num) {
			num--;
			customer * cus = qtime->remove();
			q->removeCir(cus);
		}
	}
	while(qcho->count > 0 && q->count < MAXSIZE) {
		customer * cus = qcho->remove();
		RED(cus->name,cus->energy);
		delete cus;
	}
}

void imp_res::LIGHT(int num) {
	cout << "light " << num << endl;
	if(num > 0) {
		Node * p = q->current;
		while(p->next != q->current) {
			p->cus->print();
			p = p->next;
		}
		p->cus->print();
	}
	else if(num == 0) {
		Node * p = qcho->head;
		while(p) {
			p->cus->print();
			p = p->next;
		}
	}
	else {
		Node * p = q->current;
		while(p->pre != q->current) {
			p->cus->print();
			p = p->pre;
		}
		p->cus->print();
	}
}

void imp_res::DOMAIN_EXPANSION() {
	cout << "domain_expansion" << endl;
	long sump =0, sumn = 0;
	Node * p = qtime->head;
	while(p) {
		if(p->cus->energy > 0) sump += p->cus->energy;
		else sumn += p->cus->energy;
	}
	p = qcho->head;
	while(p) {
		if(p->cus->energy > 0) sump += p->cus->energy;
		else sumn += p->cus->energy;
	}
	if(sump >= abs(sumn)) {
		Node * p = qcho->tail;
		while(p) {
			if(p->cus->energy < 0) {
				if(p-> pre) p->pre->next = p->next;
				if(p->next) p->next->pre = p->pre;
				p->cus->print();
				delete p->cus;
				delete p;
			}
			p = p->pre;
		}
		p = qtime->tail;
		while(p) {
			if(p->cus->energy < 0) {
				if(p-> pre) p->pre->next = p->next;
				if(p->next) p->next->pre = p->pre;
				p->cus->print();
				q->removeCir(p->cus);
				delete p->cus;
				delete p;
			}
			p = p->pre;
		}
	}
	else {
		Node * p = qcho->tail;
		while(p) {
			if(p->cus->energy > 0) {
				if(p-> pre) p->pre->next = p->next;
				if(p->next) p->next->pre = p->pre;
				p->cus->print();
				delete p->cus;
				delete p;
			}
			p = p->pre;
		}
		p = qtime->tail;
		while(p) {
			if(p->cus->energy > 0) {
				if(p-> pre) p->pre->next = p->next;
				if(p->next) p->next->pre = p->pre;
				p->cus->print();
				q->removeCir(p->cus);
				delete p->cus;
				delete p;
			}
			p = p->pre;
		}
	}
	while(qcho->count > 0 && q->count < MAXSIZE) {
		customer * cus = qcho->remove();
		RED(cus->name,cus->energy);
		delete cus;
	}
}

void imp_res::REVERSAL() {
	cout << "reversal" << endl;
	if(current ->cus->energy > 0) {
		Node * i = current, *j = current ->next;
		while(i!= j && i != j->next) {
			while(i->cus->energy < 0) i = i->pre;
			while(i->cus->energy < 0) j = j->next;
			if(i->cus->energy > 0 && j->cus->energy > 0) {
				customer * temp = i->cus;
				i->cus = j->cus;
				j->cus = temp;
			}
			i = i->pre;
			j = j->next;
		}
	}
	else {
		Node * i = current, *j = current ->next;
		while(i!= j && i != j->next) {
			while(i->cus->energy > 0) i = i->pre;
			while(i->cus->energy > 0) j = j->next;
			if(i->cus->energy < 0 && j->cus->energy < 0) {
				customer * temp = i->cus;
				i->cus = j->cus;
				j->cus = temp;
			}
			i = i->pre;
			j = j->next;
		}
	}
}

void imp_res::PURPLE() {
	cout << "purple"<< endl;
	int n = qcho->shellSort(qcho->count);
	BLUE(n%MAXSIZE);
}

void imp_res::UNLIMITED_VOID() {
	cout << "unlimited_void" << endl;
	if(q->count >= 4) {
		long min = 1e9,sum =0;
		int count = 0,len = 4;
		string result = "";
		Node * p = q->current->pre;
		Node * n ,*s;
		for(int i = 0; i < q->count; i++) {
			p = p->next;
			n = p->next;
			sum = p->cus->energy;
			count =1;
			for(int j = 0; j < q->count -1 ; j++) {
				count++;
				sum += n->cus->energy;
				if(sum <= min  && count >= len) {
					s = p;
					len = count;
				}
				n = n->next;
			}
		}
		p = s->next;
		min = s->cus->energy;
		for(int i =0; i < len -1; i++) {
			if(p->cus->energy < min) min = p->cus->energy;
			p = p->next;
		}
		n = s;
		for(int i =0; i < len; i++) {
			if(s == p) {
				for(i;i < len; i++) {
					result = result + n->cus->name + '-' + to_string(n->cus->energy) + '\n';
					n =  n->next;
				}
				break;
			}	
			else {
				result = n->cus->name + '-' + to_string(n->cus->energy) + '\n' + result;
				n = n->next;
			}
		}
		cout << result;
	}
}