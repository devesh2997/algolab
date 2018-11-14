#include<bits/stdc++.h>
using namespace std;

template <class V>
class FibHeap;

template <class V>
struct node {
 private:
  node<V>* prev, *next, *child, *parent;
  V value; int degree; bool marked;
 public:
  friend class FibHeap<V>;
  node<V>* getPrev() { return prev; }
  node<V>* getNext() { return next; }
  node<V>* getChild() { return child; }
  node<V>* getParent() { return parent; }
  V getValue() { return value; }
  bool isMarked() { return marked; }
  bool hasChildren() { return child; }
  bool hasParent() { return parent; }
};

template <class V>
class FibHeap {
 public:
  node<V>* heap;

 public:
  FibHeap() { heap = _empty(); }
  node<V>* insert(V value) {
    node<V>* ret = _onlyone(value);
    heap = _merge(heap, ret);
    return ret;
  }
  void merge(FibHeap& other) {
    heap = _merge(heap, other.heap);
    other.heap = _empty();
  }
  bool isEmpty() { return heap == NULL; }
  V getMinimum() { return heap->value; }
  V ExtractMin() {
    node<V>* old = heap; heap = _removeMinimum(heap);
    V ret = old->value; delete old;
    return ret;
  }
  void decreaseKey(node<V>* n, V value) { heap = _decreaseKey(heap, n, value); }
 
  node<V>* _empty() { return NULL; }
  node<V>* _onlyone(V value) {
    node<V>* n = new node<V>;
    n->value = value; n->prev = n->next = n;
    n->degree = 0; n->marked = false;
    n->parent = n->child = NULL;
    return n;
  }
  node<V>* _merge(node<V>* a, node<V>* b) {    
    if(a==NULL || b==NULL) return a==NULL?b:a;
    if (a->value > b->value) {auto temp=a; a=b; b=temp;}
    node<V>* an = a->next; node<V>* bp = b->prev;
    a->next = b; b->prev = a; an->prev = bp; bp->next = an;
    return a;
  }
  void _addChild(node<V>* parent, node<V>* child) {
    child->prev = child->next = child;  child->parent = parent;
    parent->degree++; parent->child = _merge(parent->child, child);
  }
  void _unMarkAndUnParentAll(node<V>* n) {
    if (n == NULL) return;
    node<V>* c = n;
    do {
      c->marked = false;  c->parent = NULL; c = c->next;
    } while (c != n);
  }
  node<V>* _removeMinimum(node<V>* n) {
    _unMarkAndUnParentAll(n->child);
    if (n->next == n) n = n->child;
    else {
      n->next->prev = n->prev; n->prev->next = n->next;
      n = _merge(n->next, n->child);
    }
    if (n == NULL) return n;
    node<V>* trees[64] = {NULL};
    while (true) {
      if (trees[n->degree] != NULL) {
        node<V>* t = trees[n->degree];
        if (t == n) break;
        trees[n->degree] = NULL;
        if (n->value < t->value) {
          t->prev->next = t->next; t->next->prev = t->prev;
          _addChild(n, t);
        } else {
          t->prev->next = t->next; t->next->prev = t->prev;
          if (n->next == n) {
            t->next = t->prev = t; _addChild(t, n); n = t;
          } else {
            n->prev->next = t; n->next->prev = t; t->next = n->next;
            t->prev = n->prev; _addChild(t, n); n = t;
          }
        }
        continue;
      } else trees[n->degree] = n;
      n = n->next;
    }
    node<V>* min = n;
    node<V>* start = n;
    do {
      if (n->value < min->value) min = n;
      n = n->next;
    } while (n != start);
    return min;
  }
  node<V>* _cut(node<V>* heap, node<V>* n) {
    if (n->next == n) n->parent->child = NULL;
    else {
      n->next->prev = n->prev; n->prev->next = n->next;
      n->parent->child = n->next; 
    }
    n->next = n->prev = n; n->marked = false;
    return _merge(heap, n);
  }
  node<V>* _decreaseKey(node<V>* heap, node<V>* n, V value) {
    if (n->value < value) return heap;
    n->value = value;
    if (n->parent) {
      if (n->value < n->parent->value) {
        heap = _cut(heap, n); node<V>* parent = n->parent;
        n->parent = NULL;
        while (parent != NULL && parent->marked) {
          heap = _cut(heap, parent); n = parent;
          parent = n->parent; n->parent = NULL;
        }
        if (parent != NULL && parent->parent != NULL) parent->marked = true;
      }
    } 
    else if (n->value < heap->value) heap = n;
    return heap;
  }
};


int main(){
    FibHeap<int> h1, h2; 
    cout<<"two integer heaps have been created\n";
    int flag=0,ismerge=0;
    do{
      cout<<"1 - to insert. 2 - to display min. 3 - to merge h1, h2.  4 - to extract min. 5 - Decrease key. any other - exit\n";
      int ch;
      cin>>ch;
      switch(ch){
        case 1 : {if(ismerge)break;
          cout<<" 1 - insert in h1, 2 - insert in h2\n";
          int n,val;
          cin>>n;
          cout<<"Enter value to be inserted\n";
          cin>>val;
          if(n==1)h1.insert(val);else h2.insert(val);
          break;
        }
        case 2 : {if(ismerge){
          cout<<"Minimum is: "<<h1.getMinimum()<<endl;
          break;
        }
        cout<<" 1 - min(h1) , 2 - min(h2)\n";
        int n;
        cin>>n;
        if(n==1 || ismerge==1)cout<<h1.getMinimum()<<endl;
        else cout<<h2.getMinimum()<<endl;
        break;
        }
        case 3 : {
          h1.merge(h2);
          cout<<"both heaps merged\n";
          break;
        }
        case 4 : {
          if(ismerge){
            h1.ExtractMin();
            break;
          }
          cout<<" 1 for h1 , 2 for h2\n";
          int n;cin>>n;
          if(n==1)h1.ExtractMin();else h2.ExtractMin();
          cout<<"Min extracted\n";
          break;
        }
        case 5 : {
          cout<<" Enter key value to be inserted, new decreased value\n";
          int key,val;
          cin>>key>>val;
          auto head = h1.insert(key);
          cout<<"Old minimum = "<<h1.getMinimum()<<endl;
          h1.decreaseKey(head,val);
          cout<<"New minimum = "<<h1.getMinimum()<<endl;
          break;
        }
        default :
          flag=-1;
      }
    }while(flag!=-1);
    
}