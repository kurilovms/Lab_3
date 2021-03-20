#include <iostream>
#include <chrono>
#include <cmath>
using namespace std;

struct ListPair {
    char num;
    ListPair *tail;
};

struct List {
    ListPair *head;
};

List new_list(){
    List list;
    list.head = NULL;
    return list;
}


List push_list(List &lst, char num){
    ListPair *new_head = new ListPair;
    new_head->tail = lst.head;
    new_head->num = num;
    lst.head = new_head;
}

List new_list(List const &lst){
    List new_lst = new_list();
    ListPair *current = lst.head;
    while (current != NULL){
        push_list(new_lst, current->num);
        current = current->tail;
    }
    return new_lst;
}

char pop_list(List &lst){
    if (lst.head != NULL){
        char c = lst.head->num;
        ListPair *new_head = lst.head->tail;
        delete lst.head;
        lst.head = new_head;
        return c;
    }
    else{
        return '\0';
    }
}

char peak_list(List const &lst){
    if (lst.head != NULL){
        return lst.head->num;
    }
    else{
        return '\0';
    }
}

void delete_list(List &lst){
    while (lst.head != NULL){
        ListPair *new_head = lst.head->tail;
        delete lst.head;
        lst.head = new_head;
    }
}

bool is_empty(List const &lst){
    return lst.head == NULL;
}

List reverse_list(List &lst){
    if (lst.head != NULL){
        ListPair *current = lst.head;
        ListPair *next;
        ListPair *last = NULL;
        while (current != NULL){
            next = current->tail;
            current->tail = last;
            last = current;
            current = next;
        }
        lst.head = last;
        delete current;
        return lst;
    }
    else{
        return lst;
    }
}


int main() {
    for (int j = 0; j < 20; j++) {
        for (double i = 4; i <= 8; i += 0.5) {
            int limiter = pow(10, i);
            List A = new_list();
            auto start = std::chrono::steady_clock::now();
            for (int counter = 0; counter < limiter; counter++) {
                push_list(A, 'a');
            }
            auto stop = std::chrono::steady_clock::now();
            auto duration = stop - start;
            cout << limiter << ' ' << std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() << ' ';
            delete_list(A);
        }
        cout << endl;
    }
    return 0;
}
