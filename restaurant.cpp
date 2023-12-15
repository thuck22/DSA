#include "main.h"
const int MAXSIZE;
class Restaurant {
	private:
		class Function{
			public:
			static map<char,int> mp;
			public:
				void static Ceasar(string name){
					int n = name.length();
					map <char,int> nmp ;
					for(int i = 0; i < n; i++) {
						mp[name[i]]++;
					}
					for(pair<char,int> x : mp) {
						int n = x.second % 26;
						while(n--) {
							if(x.first == 'z') x.first = 'a';
							else if(x.first == 'Z') x.first ='A';
							else x.first += 1;
						}
						nmp[x.first] += x.second;
					}
					vector<pair<int,char>> v;
					for(pair<char,int> x : nmp) v.push_back({x.second,x.first});
					sort(v.begin(),v.end());
					for(pair<int,char> x: v) vt.push_back({x.second,x.first});
				}
				friend class Restaurant;
		};
		class Node {
			public:
				int data;
				Node * left;
				Node * right;
			public:
				Node(int d,Node * l = nullptr, Node * r = nullptr): data(d),left(l),right(r) {} 
				~Node() {}
				friend class HuffTree;
				friend class BSTree;
		};
		class HuffTree {
			public:
			Node * root;
			public:
				HuffTree(Node * r = nullptr):root(r) {}
				~HuffTree() {clear(root);}
				void clear(Node * root) {
					Node * l = root->left;
					Node * r = root->right;
					delete root;
					if(l) clear(l);
					if(r) clear(r);
				}
				Node * rotateLeft(Node * root) {
					Node * p = root->left;
					root->left = p->right;
					p->right = root;
					return p;
				}
				Node * rotateRight(Node * root) {
					Node * p = root->right;
					root->right = p->left;
					p->left = root;
					return p;
				} 
				Node * leftBalance(Node * root) {
					Node * leftTree = root->left;
					//LL
					// incomplete
				}
				void insert(Node * a, Node * b) {
					int total = a->data + b->data;
					Node * newn;
					if(a->data >= b->data) newn = new Node(total,a,b);
					else newn = new Node (total,b,a);
					root = newn;
				}
				void print(Node * root) {
					if(root->left) print(root->left);
					cout << root->data << endl;
					if(root->right) print(root->right);
				}
				void print() {
					if(!root) return;
					else print(root);
				}
		};
		class G {
			public:
			enum balance {LH,EH,RH};
			class Node {
			public:
				int data;
				Node * left;
				Node * right;
				balance b;
			public:
				Node(int d,Node * l = nullptr, Node * r = nullptr,balance ba = EH): data(d),left(l),right(r),b(ba) {} 
				~Node() {}
				friend class BSTree;
			};
			long long luythua(int n) {
			if(n <= 0) return 1;
			else return n *luythua(n-1);
			}
			long long chap(int n,int k) {
			long long result = luythua(n) / (luythua(k) * luythua(n-k));
			return result;
			}
			long long hoanvi(int n) {
			if(num == 0 || num == 1) return 1;
			else {
			//dynamic 
				for(int i = 0; i < n; i++) {
					
				}
			}
			}
			class BSTree {
				Node * root;
				public:
					friend class G;
					BSTree() { root = nullptr; }
					~BSTree() { clear(root); }
					void print(Node * root) {
						if(root->left) print(root->left);
						cout << root->data << endl;
						if(root->right) print(root->right);
					}
					void print() {
						if(!root) return;
						else print(root);
					}
					void clear(Node * root) {
						Node * l = root->left;
						Node * r = root->right;
						delete root;
						if(l) clear(l);
						if(r) clear(r);
					}
					void insert(Node * root, int &id) {
						if(id < root->data) {
							if(root->left) insert(root->left,id);
							else root->left = new Node(id);
						}
						else {
							if(root->right) insert(root->right,id);
							else root->right = new Node(id);
						}
					}
					void insert(int id) {
						if(!root) root = new Node(id);
						else insert(id);
					}
					bool search(Node * root, int &id) {
						if(id == root->data) return 1;
						else if(id < root->data ) { if (root->left) search(root->left,id); else return 0;}
						else { if (root->right) search(root->right,id); else return 0;}
					}
					bool search(int id) {
						if(!root) return 0;
						else search(root,id);
					}
					Node * remove(Node *root,int &id) {
						if(!root) return root;
						
						if(id < root->data) {root->left = remove(root->left,id); return root;}
						else {root->right = remove(root->right,id); return root;}

						if(!root->left && !root->right) { delete root; return nullptr; }
						else if(!root->left) {delete root; return root->right; }
						else if(!root->right) {delete root; return root->left; }
						else {
							Node * pa = root;
							Node * p = root->right;
							while(p->left) {
								pa = p; 
								p = p->left;
							}
							root->data = p ->data;
							if(pa == root) root->right = p ->right;
							else pa->left = p->right;
							delete p;
							return root;
						}
					}
					void remove(int id) {
						if(!search(id)) return; 
						if(!root) return;
						else root = remove(root,id);
					}
			};

			public:
				int num;
				map<int,BSTree> mp;
			public:
				G() {
					for(int i = 1; i < MAXSIZE; i++) mp[i].root == nullptr;
				}
				void LIMITLESS(int num) {
					if(mp[num].root == nullptr);
					else {
						mp[num].print();
					}
				}
				void KOKUSEN() {}
				void LAPSE(int val) {
					mp[id].insert(val);
				}
		};
		class S {
			public:
				class Node {
					public:
						int data;
						queue<int> q;
						Node * parent;
						Node * left;
						Node * right;
					public:
						Node(int d,Node * p = nullptr,Node * l = nullptr, Node * r = nullptr) {
							data = d;
							parent = p;
							left= l;
							right = r;
						}
						~Node() {}
						friend class Heap;
				};
				class Heap {
					int count;
					Node * root;
					public:
						Heap() {count = 0; root = nullptr;}
						~Heap() {clear(root);}
						void print(int num) {
							for(int i = 0; i < num; i++) {
								&
							}
						}
						Node * clear( Node *root) {
							if(!root) return root;
							if(root->left) root->left = clear(root->left);
							if(root->right) root->right = clear(root->right);
							if(!root->left && !root->right) {delete root; return nullptr;}
						}
						void clear() {root = clear(root);}
						void ReheapUp(Node *p) {
							if(p != NULL) {
								Node * par = p->parent;
								if(p->q.size() > par->q.size()) {
									queue<int> q1 = p->q;
									p->q = par->q;
									par->q = q1;
									int temp = p->data;
									p->data = par->data;
									par->data = temp;
									ReheapUp(p->parent);
								}
							}
							else return;
						}
						void ReheapDown(Node * p) {
							Node * l = p->left;
							Node * r = p->right;
							int data;
							if(l) {
								queue<int> q1 = p->q;
								if(r) { if(r->q.size() > l->q.size()) {
									p->q = r->q;
									r->q = q1;
									data = r->data; 
									r->data = p->data;
									p->data = data;
									ReheapDown(r);}
								}
								else {
									p->q = l->q;
									l->q = q1;
									data = l->data;
									l->data = p->data;
									p->data = data;
									ReheapDown(l);
								}
							}
						}
						Node * search(Node * root, int &id) {
							if(id == root->data) return root;
							if(id < root->data) {if(root->left) return search(root->left,id); else return nullptr;}
							else {if(root->right) return search(root->right,id); else return nullptr;}
						}
						Node * search(int id) {
							if(!root) return root;
							else return search(root,id);
						}
						void insert(int val,int id) {
							if(count == MAXSIZE) return;
							if(!root) { root = new Node (id,NULL,NULL,NULL),count++; root->q.push(val);}
							else {
								Node * ptr = search(id);
								if(ptr != nullptr) {
									ptr->q.push(val);
									ReheapUp(ptr);
									ReheapDown(ptr);
								}
								else {
									count++;
									queue<Node*> qu;
									qu.push(root);
									while(!qu.empty()) {
										Node * p = qu.front();
										qu.pop();
										if(!p->left) {p->left = new Node (id,p,NULL,NULL);p->left->q.push(val);ReheapUp(p->left); break;}
										else if(!p->right) {p->right = new Node (id,p,NULL,NULL);p->right->q.push(val);ReheapUp(p->right); break;}
										else {
											qu.push(p->left);
											qu.push(p->right);
										} 
									}
									while(!qu.empty()) qu.pop();
								}
							}
						}
						void remove() {
							if(!root) return;
							else if(root->q.size() == 0) {
								count--;
								Node * tail;
								queue<Node *> que;
								que.push(root);
								while(!que.empty()) {
									tail = que.front();
									que.pop();
									if(tail->left) que.push(tail->left);
									if(tail->right) que.push(tail->right);
								}
								root->data = tail->data;
								root->q = tail->q;
								Node * pa = tail->parent;
								if(pa->left == tail) pa->left = nullptr;
								else pa->right = nullptr;
								delete tail;
								ReheapDown(root);
							}
						}
				};		
			public:
				int num;
				Heap * heap;
			public:
				S(): heap(nullptr) {}
				~S() {heap->clear(); }
				void LAPSE(int result) {
					//
				}
				void KEIKEIKEN(int num) {
					for(int i = 0; i < num; i++) {
			//
					}
				}
				void CLEAVE(int num) {
					heap->print(num);
				}
		};
	public:
		string name;
		int num;
		int result;
		HuffTree * huff;
		G *g;
		S *s;
		static int id;
		static vector<pair<char,int>> vt;
	public:
		Restaurant() {huff = nullptr;g = new G; s = new S;}
		friend class Fuction;
		void LAPSE(string name) {
			Function::Ceasar(name);
//build huffman tree
//result = giai ma
			id = result %MAXSIZE +1;
			if(result % 2 == 1) g->LAPSE(result);
			else s->LAPSE(result);
		}

		void KOKUSEN() {g->KOKUSEN();}

		void KEITEIKEN(int num) {s->KEIKEIKEN(num);}

		void HAND() {huff->print();}

		void LIMITLESS(int num) {g->LIMITLESS(num);}

		void CLEAVE(int num) {s->CLEAVE(num);}
};

void simulate(string filename)
{
	cout << "Good Luck";
	return;
}