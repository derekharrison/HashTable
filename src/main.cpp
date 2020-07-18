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
    int length_table = 10;
    HashTable htable(length_table);

    /* Inserting random data in hash table. Note: hash table only admits unique keys */
    int size_table = 15;
    srand(time(NULL));
    for(int i = 0; i < size_table; ++i) {
        int key = rand() % size_table;
        Data data = {key * 3.14159};
        Node node = {key, data, };
        htable.insert_node(node);
    }

    /* Printing, getting and deleting data */
    int key = 9;
    htable.print_data_table();
    Data data = htable.get_data_node(key);
    std::cout << "data node: " << data.number << std::endl;
    std::cout << "size table: " << htable.get_size_table() << std::endl;
    htable.print_keys_table();
    htable.delete_node(key);
    std::cout << "delete table" << std::endl;
    htable.delete_table();
    htable.print_keys_table();
    std::cout << "size table: " << htable.get_size_table() << std::endl;

    return 0;
}
