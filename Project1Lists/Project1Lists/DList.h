#pragma once

struct DLink {
    int val;
    DLink* next;
    DLink* prev;

    DLink(int _val = 0, DLink* _next = nullptr, DLink* _prev = nullptr)
        : val(_val), next(_next), prev(_prev) {
    }
};
class DList {
    DLink* head; // фиктивный узел
    DLink* last; // последний элемент

public:
    DList() {
        head = new DLink();   // sentinel
        head->next = head;
        head->prev = head;
        last = head;
    }

    ~DList() {
        clear();
        delete head;
    }

    bool isEmpty() const { return head == last; }

    void addFirst(int val) {
        DLink* node = new DLink(val, head->next, head);
        head->next->prev = node;
        head->next = node;
        if (last == head) last = node;
    }

    void addLast(int val) {
        DLink* node = new DLink(val, head, last);
        last->next = node;
        head->prev = node;
        last = node;
    }

    void remove(DLink* node) {
        if (node == head) throw -1;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        if (node == last) last = node->prev;
        delete node;
    }

    void clear() {
        DLink* curr = head->next;
        while (curr != head) {
            DLink* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
        head->next = head;
        head->prev = head;
        last = head;
    }
};

