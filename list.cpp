#include "list.h"

List::List() {
    first=nullptr;
    last=nullptr;
}
bool List::is_empty() {
    return first==nullptr;
}

void List::push_back(Music dude) {
    Node* p = new Node(dude);

    if(is_empty()) {
        first=p;
        last=p;
    } else {
        p->number=last->number+1;
        last->next=p;
        last=p;

    }
    return;
}

Node* List::find(int num) {
    Node* p = first;
    while(!(p->number==num) && p) p=p->next;
    return p;
}

void List::remove(int num) {
    if(!is_empty()){
        Node* q = find(num);
        if(q) {
            if(q==first) {
                first=first->next;
                delete q;
            } else {
                Node* p = first;
                while (!(p->next==q) && p) p=p->next;
                p->next=q->next;
                if(q==last) last = p;
                delete q;
            }
        }
        Node* p = first;
        for(int i = 0; p; i++) {
            p->number=i;
            p=p->next;
        }
    }

}

int List::length() {
    Node* q = first;
    int l = 0;
    while(q) {
        l++;
        q=q->next;
    }
    return l;
}
