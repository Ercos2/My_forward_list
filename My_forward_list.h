//
// Created by dimak on 21.04.2024.
//

#ifndef MY_FORWARD_LIST_MY_FORWARD_LIST_H
#define MY_FORWARD_LIST_MY_FORWARD_LIST_H

template<typename T>
class Node {
public:
    T data;
    Node* next;

    explicit Node(T data) : data(data), next(nullptr) {}
};

template<typename T>
class My_forward_list {
private:
    Node<T>* head;
    Node<T>* tail;
    int list_size = 0;
public:
    My_forward_list() : head(nullptr), tail(nullptr) {}

    ~My_forward_list(){
        for(int a = 0; a < list_size; ++a) {
            Node<T>* temp_head;
            temp_head = head->next;
            delete head;
            head = temp_head;
        }
    }

    void insert(T data) {
        auto newNode = new Node<T>(data);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode; // place the element by the tail
            tail = newNode;     // updating the tail value
            // the "next" value of NewNode is set as nullptr when creating it.
        }
        ++list_size;
    }

    Node<T>* search_by_data(T data) {
        Node<T>* temp = head;
        while (temp != nullptr) {
            if (temp->data == data) {
                return temp;
            }
            temp = temp->next;
        }
        throw std::out_of_range("No Node with this data");
    }

    Node<T>* search_by_index(int index) {
        Node<T>* temp = head;
        if (index > list_size || index < 0)
            throw std::out_of_range("Index out of range");

        for(int i = 0; i < index; i++) {
            temp = temp->next;
        }

        if(temp == nullptr) {
            throw std::out_of_range("Something wrong in search_by_index");
        }
        return temp;
    }

    int element_index(Node<T>* element) {
        Node<T>* temp = head;
        if (element == nullptr) {
            throw std::out_of_range("no such element in this list");
        }
        for (int a = 0; temp != nullptr; ++a) {
            if (temp == element) {
                return a;
            }
            temp = temp->next;
        }
        throw std::out_of_range("no such element in this list");
    }

    [[nodiscard]] int size() const {
        return list_size;
    }

    bool is_data_exist(T data) {
        try {
            search_by_data(data);
            return true;
        }
        catch (std::out_of_range& what) {
            std::cout << what.what() << "\n";
            return false;
        }
    }

    void remove(T index) {
        if (index > list_size || index < 0) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* element_for_delete = search_by_index(index);

        if (element_for_delete == head) {
            head = element_for_delete->next;
            delete element_for_delete;
        }
        else {
            Node<T>* prev_element = search_by_index(index - 1);
            if(element_for_delete == tail) {
                tail = prev_element;
                tail->next = nullptr;
            }
            else {
                prev_element->next = element_for_delete->next;
            }
            delete element_for_delete;
            std::cout << "seccussful\n";
        }
        --list_size;
    }

    void remove(Node<T>* element) {
        //element_index has it own test of argument
        remove(element_index(element));
    }

    T& operator[] (int index) {
        return search_by_index(index)->data;
    }

    class Iterator {
    private:
        Node<T>* current;
    public:
        explicit Iterator(Node<T>* start) : current(start) {}

        T& operator*() {
            return current->data;
        }
        T* operator->() { return current->data; }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator== (const Iterator& a, const Iterator& b) {
            return a.current == b.current;
        };

        friend bool operator!= (const Iterator& a, const Iterator& b) {
            return a.current != b.current;
        };
    };

    Iterator begin() {
        return Iterator(head);
    }
    Iterator end() {
        return Iterator(tail->next);
    }
};

#endif //MY_FORWARD_LIST_MY_FORWARD_LIST_H
