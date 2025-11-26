#pragma once
#include<utility>
using namespace std;

struct Link {
    int val;
    Link* next;
    Link(int _val = 0) : val(_val) {
        next = this;
    }
    Link(int _val, Link* _next) : val(_val), next(_next) {}
};

class HList {
    Link* head;
    Link* last;
public:
    HList() {
        head = new Link();
        last = head;
    }
    Link* addafter(Link* p, int val) { //private
        Link* t = new Link(val, p->next);
        p->next = t;
        return t;
    }
    void addfirst(int val) {
        addafter(head, val);
    }
    void addlast(int val) {
        last = addafter(last, val);
    }
    HList(const HList& other) {
        
        Link* tmp = other.head->next;

        head = new Link();
        last = head;

        while (tmp != other.head) {
            addlast(tmp->val);
            tmp = tmp->next;
        }
    }
    void RemoveLast() {
        if (head == last) throw - 1;
        Link* tmp = head;
        while (tmp->next != last)
            tmp = tmp->next;
        delete last;
        tmp->next = head;
        last = tmp;
    }
    void Reverse() {
        HList cpy;
        Link* tmp = head->next;

        while (tmp != head) {
            cpy.addfirst(tmp->val);
            tmp = tmp->next;
        }
        swap(head, cpy.head);
        swap(last, cpy.last);
    }
    void RemoveAllSame(int val) {
        Link* curr = head->next;
        Link* prev = head;

        while (curr != head) {
            if (curr->val == val) {
                prev->next = curr->next;
                delete curr;
                curr = prev->next;
            }
            else {
                prev = curr;
                curr = curr->next;
            }
        }
    }
    void RemoveDuplicate() {
        if (head == last) throw -1;
        Link* curr = head->next;

        while (curr != head) {
            Link* prev = curr;
            Link* tmp = curr->next;

            // Внутренний цикл: проверяем все элементы после curr
            while (curr != head) {
                if (tmp->val == curr->val) {
                    // Удаляем дубликат
                    prev->next = tmp->next;
                    delete tmp;
                    tmp = prev->next; // двигаем tmp на следующий после удалённого
                }
                else {
                    prev = tmp;
                    tmp = tmp->next;
                }
                curr = curr->next;
            }
        }
    }

};
