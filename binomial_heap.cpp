#include<bits/stdc++.h>
using namespace std;
struct Node{
    int key;
    int degree;
    Node* parent;
    Node* child;
    Node* sibling;  
};

class BinomialHeap{
    Node* head;
    public:
        Node* newNode(int key){
            Node* node = new Node();
            node->key  = key;
            node->degree =0;
            node->parent = NULL;
            node->child = NULL;
            node->sibling = NULL;
            return node;
        }
        void Link(Node* y, Node* z){
            y->parent = z;
            y->sibling = z->child;
            z->child = y;
            z->degree = z->degree + 1;
        }

        Node* merge(BinomialHeap h2){
            Node* curr1 = this->getHead();
            Node* curr2 = h2.getHead();
            if(curr1 == NULL)return curr2;
            if(curr2 == NULL)return curr1;
            Node* newHead = NULL;
            Node* curr = NULL;
            while(curr1!=NULL && curr2!=NULL)
            {
                if(curr1->degree <= curr2->degree){
                    Node* n = newNode(curr1->key);
                    n->child = curr1->child;
                    if(newHead == NULL){
                        newHead = n;
                        curr = newHead;
                    }else{
                        curr->sibling = n;
                        curr = curr->sibling;
                    }
                    curr1 = curr1->sibling;
                }
                else
                {
                    Node* n = newNode(curr2->key);
                    n->child = curr2->child;
                    if(newHead == NULL){
                        newHead = n;
                        curr = newHead;
                    }else{
                        curr->sibling = n;
                        curr = curr->sibling;
                    }
                    curr2 = curr2->sibling;
                }
            }
            if(curr1==NULL)
            {
                while(curr2!=NULL)
                {
                     Node* n = newNode(curr2->key);
                    n->child = curr2->child;
                    if(newHead == NULL){
                        newHead = n;
                        curr = newHead;
                    }else{
                        curr->sibling = n;
                        curr = curr->sibling;
                    }
                    curr2 = curr2->sibling;
                }
            }
            else if(curr2 == NULL)
            {
                while(curr1!=NULL)
                {
                    Node* n = newNode(curr1->key);
                    n->child = curr1->child;
                    if(newHead == NULL){
                        newHead = n;
                        curr = newHead;
                    }else{
                        curr->sibling = n;
                        curr = curr->sibling;
                    }
                    curr1 = curr1->sibling;
                }
            }
            return newHead;
        }

        Node* heap_union(BinomialHeap h2)
        {
            BinomialHeap newHeap;
            newHeap.setHead(this->merge(h2));
            if(newHeap.getHead()==NULL)return NULL;
            Node* prev_x = NULL;
            Node* x = newHeap.getHead();
            Node* next_x = x->sibling;
            while(next_x != NULL){
                if(x->degree != next_x->degree || (next_x->sibling != NULL && next_x->sibling->degree == x->degree)){
                    prev_x = x;
                    x = next_x;
                }else{
                    if(x->key <= next_x->key){
                        x->sibling = next_x->sibling;
                        Link(next_x,x);
                    }else{
                        if(prev_x == NULL)newHeap.setHead(next_x);
                        else prev_x->sibling = next_x;
                        Link(x,next_x);
                    }
                }
                next_x = x->sibling;
            }
            return newHeap.getHead();
        }
        Node* findUtil(Node* node,int x)
        {
            if(node==NULL)return NULL;
            if(node->key == x)return node;
            if(findUtil(node->sibling,x)!=NULL)return findUtil(node->sibling,x);
            return findUtil(node->child,x);
        }
        public:
            BinomialHeap(){
                head = NULL;
            }
            Node* getHead(){
                return head;
            }
            Node* setHead(Node* h){
                head = h;
            }
            void insert(int x){
                BinomialHeap h;
                Node* node = newNode(x);
                h.setHead(node);
                this->head = this->heap_union(h);
            }
            int extractMin()
            {
                Node* prevmin = NULL;
                Node* min = this->head;
                if(min == NULL)
                {
                    cout<<"Heap is empty\n";
                    return -1;
                }
                else
                {
                    Node* prevcurr = NULL;
                    Node* curr = this->head;
                    while(curr!=NULL)
                    {
                        if(curr->key<min->key)
                        {
                            prevmin = prevcurr;
                            min = curr;
                        }
                        prevcurr = curr;
                        curr = curr->sibling;
                    }
                    if(prevmin == NULL)
                    {
                        this->head = this->head->sibling;
                    }
                    else
                    {
                        prevmin->sibling = prevmin->sibling->sibling;
                    }
                    BinomialHeap h;
                    Node* child = min->child;
                    Node* newHead = NULL;
                    Node* currnode = NULL;
                    while(child!=NULL)
                    {
                        Node* prevlastchild = NULL;
                        Node* lastchild = child;
                        while(lastchild->sibling != NULL)
                        {
                            prevlastchild = lastchild;
                            lastchild = lastchild->sibling;
                        }
                        lastchild->parent = NULL;
                        lastchild->sibling = NULL;
                        if(newHead == NULL)
                        {
                            newHead = lastchild;
                            currnode = newHead;
                        }else
                        {
                            currnode->sibling = lastchild;
                        }
                        if(prevlastchild!=NULL)
                        {
                            prevlastchild->sibling = NULL;
                        }
                        child = child->sibling;
                    }
                    h.setHead(newHead);
                    this->head = this->heap_union(h);
                    return min->key;
                }
            }

            Node* find(int x)
            {
                if(this->head == NULL)return NULL;
                return findUtil(this->head,x);
            }

            void decreaseKey(int x, int k)
            {
                Node* node = find(x);
                if(node == NULL)
                {
                    cout<<"Node with value "<<x<<" not found : \n";
                }
                else
                {
                    if(k> node->key)cout<<"Error \n";
                    else
                    {
                        node->key = k;
                        Node* y = node;
                        Node* z= y->parent;
                        while(z!=NULL && y->key <z->key)
                        {
                            int temp = y->key;
                            y->key = z->key;
                            z->key = temp;
                            y = z;
                            z = y->parent; 
                        }
                    }
                }
            }

            void deleteKey(int x)
            {
                decreaseKey(x,INT_MIN);
                extractMin();
            }
};
int main()
{
    BinomialHeap BH;
    int h=1;
    do{
        cout<<"1 -- Insert Key\t 2 -- Decrease Key\t 3 -- Delete Key\t 4 -- Extract min\t Any other int- exit\n";
        int td;
        cin>>td;
        switch(td){
            case 1 :{
                cout<<"Enter key value\n";int v;cin>>v;BH.insert(v);break;
            }
            case 2 :{
                cout<<"Enter old key value and new one\n";int v,k;cin>>v>>k;BH.decreaseKey(v,k);break;
            }
            case 3 :{
                cout<<"Enter key to be deleted\n";int v;cin>>v;BH.deleteKey(v);break;
            }
            case 4 :{
                int x = BH.extractMin();cout<<"Min value = :"<<x<<endl;break;
            }
            default :
                h=-1;
        }

    }while(h!=-1);   
    
}