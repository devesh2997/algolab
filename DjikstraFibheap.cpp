#include<bits/stdc++.h>
using namespace std;

template <class V>
class FibHeap;

template <class V>
struct node {
 private:
  node<V>* prev, *next, *child, *parent;
  V* value; int degree,vertex; bool marked;
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
  node<V>* insert(int vert,V* value) {
    node<V>* ret = _singleton(value,vert);
    heap = _merge(heap, ret);
    return ret;
  }
  void merge(FibHeap& other) {
    heap = _merge(heap, other.heap);
    other.heap = _empty();
  }
  bool isEmpty() { return heap == NULL; }
  pair<int,V> ShowMin() { return {heap->vertex,*(heap->value)}; }
  V* ExtractMin() {
    node<V>* old = heap; heap = _ExtractMin(heap);
    V* ret = old->value; delete old;
    return ret;    
  }
  void decreaseKey(node<V>* n, V value) { heap = _decreaseKey(heap, n, value); }
 public:
  node<V>* _empty() { return NULL; }
  node<V>* _singleton(V* value, int vert) {
    node<V>* n = new node<V>;
    n->value = value; n->prev = n->next = n;
    n->vertex = vert;
    n->degree = 0; n->marked = false;
    n->parent = n->child = NULL;
    return n;
  }
  node<V>* _merge(node<V>* a, node<V>* b) {
    if(a==NULL || b==NULL) return a==NULL?b:a;
    if (*(a->value) > *(b->value)) {auto temp=a; a=b; b=temp;}
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
  node<V>* _ExtractMin(node<V>* n) {
    _unMarkAndUnParentAll(n->child);
    if (n->next == n) n = n->child;
    else {
      n->next->prev = n->prev; n->prev->next = n->next;
      n = _merge(n->next, n->child);
    }
    if (n == NULL) return n;
    node<V>* trees[100] = {NULL};
    while (true) {
      if (trees[n->degree] != NULL) {
        node<V>* t = trees[n->degree];
        if (t == n) break;
        trees[n->degree] = NULL;
        if (*(n->value) < *(t->value)) {
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
      if (*(n->value) < *(min->value)) min = n;
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
    if ( *(n->value) < (value)) return heap;
    *(n->value) = value;
    if (n->parent) {
      if (*(n->value) < *(n->parent->value)) {
        heap = _cut(heap, n); node<V>* parent = n->parent;
        n->parent = NULL;
        while (parent != NULL && parent->marked) {
          heap = _cut(heap, parent); n = parent;
          parent = n->parent; n->parent = NULL;
        }
        if (parent != NULL && parent->parent != NULL) parent->marked = true;
      }
    } 
    else if (*(n->value) < *(heap->value)) heap = n;
    return heap;
  }
};

int main(){
    FibHeap<int> vertices;
    cout<<"Enter number of nodes and edges\n";
    int v,e;
    cin>>v>>e;
    vector<vector<pair<int,int> > > adls(v+1);
    cout<<"Enter edges source first, then destinaton and weight\n";
    for(int i(0);i<e;i++){
	    int s,d,w;
	    cin>>s>>d>>w;
	    adls[s].push_back({d,w});	    
    }
    cout<<"Enter source node\n";
    int source;
    cin>>source;
    int a = INT_MAX/20;
    vector<int> dist(v+1,a);
    vector<node<int> * > biject(v+1,NULL);
    dist[source]=0;
    long long curd=0;
    int ct=0;
    for(int i(1);i<=v;i++){
    	biject[i] = vertices.insert(i,&dist[i]);
    	curd+=dist[i];
    }
    while(!vertices.isEmpty()){
    	
    	long long newd=0;
    	pair<int,int> p = vertices.ShowMin();
	    vertices.ExtractMin();
    	ct++;
    	if(ct>=v || p.second==a)break;
    	int s = p.first;
    for(int i(0);i<adls[s].size();i++){
      int x=dist[adls[s][i].first];
      int y=p.second+adls[s][i].second;
      if(y<x){
      dist[adls[s][i].first]=y;
      vertices.decreaseKey(biject[adls[s][i].first],y);
    }
	}
    }
    cout<<"By Djisktra's algorithm, the required minimum distances are\n";
    for(int i(1);i<=v;i++){
 	cout<<"vertex "<<i<<" -- ";if(dist[i]!=a)cout<<dist[i]<<endl;else cout<<"not reachable"<<endl;   	
    }   
    
}
