#include <iostream>
#include "My_forward_list.h"

int main() {
    //My_forward_list<int> my_list;
    auto my_list = new My_forward_list<int>;

    std::cout << "\nSIZE OF THE LIST: " << my_list->size() << "\n\n";

///////////////////////////////////////////////////
/// insert
///////////////////////////////////////////////////

    for(int a = 0; a < 100; ++a) {
        my_list->insert(a);
    }

    std::cout << "\nSIZE OF THE LIST: " << my_list->size() << "\n\n";

///////////////////////////////////////////////////
/// for_each
///////////////////////////////////////////////////

    //for(int a = 0; a < my_list.size() && a < 100; ++a) { std::cout << "element number " << a << ": " << my_list[a] << "\n"; }
    int temp_a = 0;
    for(auto a : *my_list) { std::cout << "element number " << temp_a++ << " " << a << "\n"; }

///////////////////////////////////////////////////
/// search
///////////////////////////////////////////////////

    for(int a = 0; a < 100; ++a) {
        int new_rand = rand()%99 + 1;
        std::cout << "searching rand element " << new_rand << ": " << (my_list->search_by_data(new_rand)->data) << "\n";
    }

    try {
        std::cout << "\nsearch element with data that isn't exist\n";
        my_list->search_by_data(1045);
    }
    catch (std::out_of_range what){ std::cout << what.what() << "\n";}

///////////////////////////////////////////////////
/// is_it_data_exist
/// element_index
/// search
///////////////////////////////////////////////////

    for(int a = 0; a < 50; ++a) {
        int new_rand = rand()%99 + 1;
        if (my_list->is_data_exist(new_rand)) {
            std::cout << "delete element with data " << new_rand << " and index " << my_list->element_index(my_list->search_by_data(new_rand))
                      << "\n";
            my_list->remove(my_list->element_index(my_list->search_by_data(new_rand)));
        } else --a;
    }

    try {
        std::cout << "\ntry to take index of element that isn't exist\n";
        Node<int> *try_node = new Node(5);
        my_list->element_index(try_node);
    }
    catch (std::out_of_range what){ std::cout << what.what() << "\n";}

///////////////////////////////////////////////////
/// []
///////////////////////////////////////////////////

    std::cout << "\nSIZE OF THE LIST: " << my_list->size() << "\n\n";
    //for(int a = 0; a < my_list.size() && a < 100; ++a) { std::cout << "element number " << a << ": " << my_list[a] << "\n"; }
    temp_a = 0;
    for(auto a : *my_list) { std::cout << "element number " << temp_a++ << " " << a << "\n"; }

    try {
        std::cout << "\ntry to cout -1\n";
        (*my_list)[-1];
    }
    catch (std::out_of_range what){ std::cout << what.what() << "\n"; }

    delete my_list;

    return 0;
}
