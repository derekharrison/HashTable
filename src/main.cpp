/*
 * main.cpp
 *
 *  Created on: Jul 16, 2020
 *      Author: d-w-h
 */

#include <iostream>
#include <time.h>
#include "../inc/HashTable.hpp"

int main(int argc, char* argv[])
{
    int length_table = 100;
    HashTable htable(length_table);

    /* Inserting random data in hash table. Note: hash table only admits unique keys */
    int size_table = 150;
    int* saved_keys = new int[size_table];
    srand(time(NULL));
    for(int i = 0; i < size_table; ++i) {
        int key = rand() % size_table;
        saved_keys[i] = key;
        Data data = {key * 3.14159};
        Node node = {key, data, };
        htable.insert_node(node);
    }

    htable.print_data_table();
    Data data = htable.get_data_node(saved_keys[size_table-1]);
    std::cout << "data node: " << data.number << std::endl;
    std::cout << "size table: " << htable.get_size_table() << std::endl;
    htable.print_keys_table();
    std::cout << "delete table" << std::endl;
    htable.delete_table();
    htable.print_keys_table();
    std::cout << "size table: " << htable.get_size_table() << std::endl;

    return 0;
}
