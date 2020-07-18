/*
 * HashTable.hpp
 *
 *  Created on: Jul 17, 2020
 *      Author: d-w-h
 */

#ifndef HASHTABLE_HPP_
#define HASHTABLE_HPP_

class Data {
public:
    double number;
};

class Node {
public:
    int key;
    Data data;
    Node* prev = NULL;
    Node* next = NULL;
};

class HashTable {
private:
    int m;
    int size_table;
    Node** T;

    int hash_fcn(int k);
    Node* get_node_ptr(int key);
    bool check_key_taken(int key);
public:
    HashTable(int length_table);
    ~HashTable();
    void print_keys_table();
    void print_data_table();
    void print_data_node(int key);
    Data get_data_node(int key);
    void insert_node(Node node);
    void delete_node(int key);
    void delete_table();
    int get_size_table();
};

#endif /* HASHTABLE_HPP_ */
