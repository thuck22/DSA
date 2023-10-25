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
	int count;
	friend class imp_res;
public:
	Queue(): head(NULL),tail(NULL),count(0){}
	~Queue() {
		clear();
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
	customer * remove() {
		if(count >0) {
			Node * p = head;
			head = head->next;
			head->pre = NULL;
			count--;
			customer * cus = p->cus;
			delete p;
			return cus;
		}
		else throw "Segmentation fail!";
	}
	void clear() {
		while(head) {
			Node *p = head->next;
			delete head;
			head = p;
		}
		count = 0;
		tail = NULL;
	}
	customer *front() {
		if(head == NULL) throw "Segmentation fail!";
		else return head->cus;
	}
	customer *rear() {
		if(tail == NULL) throw "Segmentation fail!";
		else return tail->cus;
	}
	Node * maxEnergy() {
		Node *p = head->next;
		int max = abs(head->cus->energy);
		Node * s = head;
		while(p) {
			if(abs(p->cus->energy) > max) {
				max = abs(p->cus->energy);
				s = p;
			}
			p = p->next;
		}
		return s;
	}
	Node * ind(int index) {
		if(index == 0) return head;
		else if(index > count || index <0) throw "out_of_range"; 
		else if(index == count-1) return tail;
		else {
			Node *p = head;
			for(int i = 1; i <= index; i++) {
				p = p->next;
			}
			return p;
		}
	}
	int shellSort() {
		int n = 1; 
		Node *p = head;
		while(p != maxEnergy()) {
			p = p->next;
			n++;
		}
		int i = n/2;
		int cnt = 0;
		while(i) {
			cnt++;
			for(int j = 0; j < i ; j++) {
				for(int k = j +i; k < n; k += i) {
					if(abs(ind(k-i)->cus->energy) < abs(ind(k)->cus->energy) ) {
						customer * temp = ind(k-i)->cus;
						ind(k-1)->cus = ind(k)->cus;
						ind(k)->cus = temp;
					}
				}
			}
			i /= 2;
			cnt++;
		}
		return cnt;
	}

	void print() {
		Node *p = head;
		while(p) {
			cout << p->cus->name << ' ' << p->cus->energy << endl;
			p = p->next;
		}
	}
};















class imp_res : public Queue
{
	customer * current;
	int guest;
    Queue * cir;
	Queue * q1;
	Queue * q2;
	public:	
		imp_res(){
			current = NULL;
			guest = 0;
            cir = new Queue();
			q1 = new Queue() ;
			q2 = new Queue() ;
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

// impliment class imp_res
bool imp_res::checkName(string name) {
	customer * p = current;
	while(p!= current) {
		if(name.compare(p->name) == 0) return 1;
	}
	return 0;
}

void imp_res::RED(string name,int energy) {
	cout << name << " " << energy << endl;
	if(energy == 0);
	else if(guest == 0) {
		current = new customer (name,energy,NULL,NULL);
        
		current->prev = current;
		current->next = current;
		guest++;
		q1->add(*current);
	}
	else if(guest >= MAXSIZE/2) {
        guest++;
        customer * p = current;
        customer * n = current->next;
        customer * s;
        int res = -1e9;
        for(int i =0; i < guest; i++) {
            if((abs(p->energy) - abs(n->energy)) > res) {
                res = (abs(p->energy) - abs(n->energy));
                s = p;
            }
            p = p->next;
            n = p->next;
        }
        if((s->energy - s->next->energy) < 0) {
            customer * cus = new customer(name,energy,s->prev,s);
            s->prev->next = cus;
            s ->prev = cus;
            q1->add(*cus);
        }
        else {
            customer * cus = new customer (name,energy,s,s->next);
            s->next->prev = cus;
            s->next =cus;
            q1->add(*cus);
        }
	}
	else if(guest < MAXSIZE) {
		if(energy >= current->energy) {
			customer * cus = new customer(name,energy,current->prev,current);
			current->prev->next = cus;
			current->prev = cus;
			current = cus;
			guest++;
		}
		else {
			customer * cus = new customer(name,energy,current,current->next);
			current->next ->prev = cus;
			current->next = cus;
			current = cus;
			guest++;
		}
		q1->add(*current);
	}
	else {
		if(checkName(name) || q2->count == MAXSIZE) ;
		else {
			customer * cus = new customer(name,energy,NULL,NULL);
			q2->add(*cus);
		}
	}
}

void imp_res::BLUE(int num) {
	cout << "blue "<< num << endl;
	if(num >= MAXSIZE) {
		while(current) {
			customer *p = current->next;
			delete current;
			current = p;
		}
		q1->clear();
		guest = 0;
	}
	else {
		for(int i = 0; i < num; i++) {
			customer *p = q1->remove();
			p->next ->prev = p->prev;
			p->prev->next = p ->next;
			delete p;
			guest--;
		}
		if(q1->count == 0) current = NULL;
		else current = q1->front();
	}
}

void imp_res::PURPLE() {
	cout << "purple"<< endl;
	BLUE(q1->shellSort() %MAXSIZE);
}

void imp_res::DOMAIN_EXPANSION() {
	cout << "domain_expansion" << endl;
	long long sump =0,sumn = 0;
	if(current->energy > 0) sump += current->energy;
	else sumn += current->energy;
	customer *p = q1->front();
	while(p != q1->rear()) {
		if(p->energy >0) {
			sump+= p->energy;
		}
		else sumn += p->energy;
		p = p->next;
	}
	Node * ptr = q2->head;
	while(ptr) {
		if(ptr->cus->energy >0) {
			sump+= ptr->cus->energy;
		}
		else sumn += ptr->cus->energy;
		ptr = ptr->next;
	}
	if(sump >= abs(sumn)) {
		while(current->energy <0) {
			p = current;
			current = current ->next;
			p->prev ->next = p ->next;
			p->next ->prev = p->prev;
			delete p;
		}
		p = current->next;
		while(p != current) {
			customer *n = p->next;
			if(p->energy <0) {
				p->prev ->next = p ->next;
				p->next ->prev = p->prev;
				delete p;
				p = n;
			}
			else p = p->next;
		}
		Node * ptr = q1->tail;
		while(ptr) {
			Node *n = ptr->pre;
			if(ptr->cus->energy < 0) {
				ptr->pre ->next = ptr ->next;
				if(ptr->next) ptr->next ->pre = ptr->pre;
				cout << ptr->cus->name << '-' << ptr->cus->energy << endl;
				delete ptr;
				ptr = n;
			}
			else ptr = ptr->pre;
		}
		ptr = q2->tail;
		while(ptr) {
			Node *n = ptr->pre;
			if(ptr->cus->energy < 0) {
				ptr->pre ->next = ptr ->next;
				if(ptr->next) ptr->next ->pre = ptr->pre;
				cout << ptr->cus->name << '-' << ptr->cus->energy << endl;
				delete ptr;
				ptr = n;
			}
			else ptr = ptr->pre;
		}
	}
	else {
		while(current->energy > 0) {
			p = current;
			current = current ->next;
			p->prev ->next = p ->next;
			p->next ->prev = p->prev;
			delete p;
		}
		p = current->next;
		while(p != current) {
			customer *n = p->next;
			if(p->energy > 0) {
				p->prev ->next = p ->next;
				p->next ->prev = p->prev;
				delete p;
				p = n;
			}
			else p = p->next;
		}
		Node * ptr = q1->tail;
		while(ptr) {
			Node *n = ptr->pre;
			if(ptr->cus->energy > 0) {
				ptr->pre ->next = ptr ->next;
				if(ptr->next) ptr->next ->pre = ptr->pre;
				cout << ptr->cus->name << '-' << ptr->cus->energy << endl;
				delete ptr;
				ptr = n;
			}
			else ptr = ptr->pre;
		}
		ptr = q2->tail;
		while(ptr) {
			Node *n = ptr->pre;
			if(ptr->cus->energy > 0) {
				ptr->pre ->next = ptr ->next;
				if(ptr->next) ptr->next ->pre = ptr->pre;
				cout << ptr->cus->name << '-' << ptr->cus->energy << endl;
				delete ptr;
				ptr = n;
			}
			else ptr = ptr->pre;
		}
	}
}

void imp_res::LIGHT(int num) {
	cout << "light " << num << endl;
	if(num > 0) {
		customer *p = current;
		while(p->next != current) {
			p->print();
			p = p->next;
		}
		p->print();
	}
	else if(num < 0) {
		customer *p = current;
		while(p->prev != current) {
			p->print();
			p = p->prev;
		}
		p->print();
	}
	else {
		Node * p = q2->head ;
		while(p) {
			p->cus->print();
			p = p->next;
		}
	}
}

void imp_res::REVERSAL() {
	cout << "reversal" << endl;
	customer * i = current;
	customer * j = current ->next;
	if(current->energy > 0) {
		while(i != j || j == i->next ) {
			if(i == j) break;
			while(i->energy < 0 && i != j) i = i->prev;
			while(j->energy < 0 && j != i) j = j->next;
			if(i == j) break;
			if(i->energy > 0 && j->energy > 0) {
				customer * temp = i;
				i = j;
				j = temp;
			}
			i = i->prev;
			j = j->next;
		}
	}
	else {
		while(i != j || j == i->next ) {
			if(i == j) break;
			while(i->energy > 0 && i != j) i = i->prev;
			while(j->energy > 0 && j != i) j = j->next;
			if(i == j) break;
			if(i->energy < 0 && j->energy < 0) {
				customer * temp = i;
				i = j;
				j = temp;
			}
			i = i->prev;
			j = j->next;
		}
	}
}

void imp_res::UNLIMITED_VOID() {
	cout << "unlimited_void" << endl;
	customer * p = current->prev;
	customer * n = current;
	customer * s =current;
	int count = 1,save =1;
	int sum =0, min = 1e9;
	if(guest >= 4) {
		for(int i =0; i < guest; i++) {
			p = p->next;
			n = p;
			sum = p->energy;
			count = 1;
			for(int j = 0; j < guest; j++) {
				n = n->next;
				count++;
				sum += n->energy;
				if(sum <= min && count >= save) {
					s = p;
					min = sum;
					save = count;
				}
			}
		}
		n = s;
		p= s;
		min = s->energy;
		string result = "";
		for(int i = 0; i < save; i++) {
			if(n->energy < min) {
				min = n->energy;
				p = n;
			}
			n = n->next;
		}
		n = s;
		for(int i =0; i < save; i++) {
			if(n == p) {
				for(i; i < save; i++) {
					result = n->name + '-' + to_string(n->energy) + '\n' + result;
					n = n->next;
				}
			}
			else {
				result = result + n->name + '-' + to_string(n->energy) + '\n';
			}
			n = n->next;
		}
		cout << result;
	}
}
