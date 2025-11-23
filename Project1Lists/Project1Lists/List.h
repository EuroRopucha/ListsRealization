#pragma once

struct Link1 {
    int val;
    Link1* next;
    Link1(int _val = 0, Link1* _next = nullptr) : val(_val), next(_next) {}
};

class Iterator {
    Link1* tmp;

public:
    Iterator(Link1* _tmp) : tmp(_tmp) {}

    bool hasNext() {
        return tmp != nullptr;
    }
    int Next() {
        if (!hasNext()) throw - 1;
        int curr = tmp->val;
        tmp = tmp->next;
        return curr;
    }

};

class List {
    Link1* fp;
public:
    List() { fp = nullptr; }

    void delFirst() {
        if (fp == nullptr)
            return;
        Link1* tmp;
        tmp = fp;
        fp = fp->next;
        delete(tmp);
    }
    void Clean() {
        while (fp != nullptr)
            delFirst();
    }
    ~List(){
        Clean();
    }
    void addFirst(int& value) {
        Link1* tmp = new Link1(value, fp);
        fp = tmp;
    }
    List(const List& other) {
        Link1* tmp = other.fp;
        
        if (tmp == nullptr) {
            fp = nullptr;
            return;
        }
        fp = new Link1(tmp->val);

        Link1* tmp2 = fp;
        while (tmp->next != nullptr) {
            tmp = tmp->next;
            tmp2->next = new Link1(tmp->val);
            tmp2 = tmp2->next;
            
        }
    }
    int& operator[](const int ind) {
        if (ind < 0) throw - 1;
        Link1* tmp = fp;
        for (int i = 0; i = ind; i++)
        {
            if (tmp == nullptr) throw - 1;
            tmp = tmp->next;
        }
        if (tmp == nullptr) throw - 1;
        return tmp->val;
    }
    int Size() {
        int cnt = 0;
        Link1* tmp = fp;
        while (tmp != nullptr) {
            cnt++;
            tmp = tmp->next;
        }
        return cnt;
    }
    Iterator iter() { return Iterator(fp); };


    void delInd(int ind) {
        if (ind == 0) {
            delFirst();
            return;
        }
        Link1* tmp = fp;
        while (ind > 1) {
            if (tmp == nullptr) throw - 1;
            tmp = tmp->next;
            ind--;
        }

        Link1* tmp2 = tmp->next;
        tmp->next = tmp2->next;
        delete(tmp2);
    }
    
};








