/*
 * HashTable.cpp
 *
 *  Created on: Jul 17, 2020
 *      Author: d-w-h
 */

#include <iostream>
#include <cstdlib>
#include "../inc/HashTable.hpp"

int HashTable::hash_fcn(int k) {
    return k % this->m;
}

HashTable::HashTable(int length_table) {
    this->m = length_table;
    this->size_table = 0;
    this->T = new Node*[this->m];
    for(int i = 0; i < this->m; ++i) {
        this->T[i] = NULL;
    }
}

HashTable::~HashTable() {
	HashTable::delete_table();
    delete [] this->T;
}

void HashTable::print_keys_table() {
    for(int i = 0; i < this->m; ++i) {
        /* Case: Slot not empty */
        if(this->T[i] != NULL) {
            /* Case: One element in list */
            if(this->T[i]->next == NULL) {
                std::cout << this->T[i]->key << std::endl;
            }
            /* Case: All elements except last, for lists greater than 1*/
            Node* dummy = this->T[i];
            while(dummy->next != NULL) {
                std::cout << dummy->key << " ";
                dummy = dummy->next;
            }
            /* Case: Last element, for lists greater than 1 */
            if(dummy->next == NULL && dummy->prev != NULL) {
                std::cout << dummy->key << std::endl;
            }
        }
        /* Case: Slot empty */
        else {}
    }
}

void HashTable::print_data_table() {
    for(int i = 0; i < this->m; ++i) {
        /* Case: Slot not empty */
        if(this->T[i] != NULL) {
            /* Case: One element in list */
            if(this->T[i]->next == NULL) {
                std::cout << this->T[i]->data.number << std::endl;
            }
            /* Case: All elements except last, for lists greater than 1*/
            Node* dummy = this->T[i];
            while(dummy->next != NULL) {
                std::cout << dummy->data.number << " ";
                dummy = dummy->next;
            }
            /* Case: Last element, for lists greater than 1 */
            if(dummy->next == NULL && dummy->prev != NULL) {
                std::cout << dummy->data.number << std::endl;
            }
        }
        /* Case: Slot empty */
        else {}
    }
}

void HashTable::print_data_node(int key) {
    Node* node_ptr = HashTable::get_node_ptr(key);

    /* Case: Node with matching key found */
    if(node_ptr != NULL) {
        std::cout << node_ptr->data.number << std::endl;
    }
    /* Case: No node with matching key found */
    else {
        std::cout <<
                     "Unable to print node data. No node with matching key found"
                  << std::endl;
    }
}

Data HashTable::get_data_node(int key) {
    Node* node_ptr = HashTable::get_node_ptr(key);
    Data data = {0};

    /* Case: Node with matching key found */
    if(node_ptr != NULL) {
        data = node_ptr->data;
    }
    /* Case: No node with matching key found */
    else {
        std::cout <<
                     "Unable to get node data. No node with matching key found"
                  << std::endl;
    }

    return data;
}

bool HashTable::check_key_taken(int key) {
    bool key_taken = false;
    Node* node_ptr = HashTable::get_node_ptr(key);

    /* Case: Node with matching key found */
    if(node_ptr != NULL) {
        key_taken = true;
    }
    /* Case: No node with matching key found */
    else {}

    return key_taken;
}

void HashTable::insert_node(Node node) {
    int index_ht = HashTable::hash_fcn(node.key);
    /* Case: Slot empty */
    if(this->T[index_ht] == NULL) {
        this->T[index_ht] = new Node;
        this->T[index_ht]->key = node.key;
        this->T[index_ht]->data = node.data;
        this->T[index_ht]->next = NULL;
        this->T[index_ht]->prev = NULL;
        this->size_table++;
    }
    /* Case: Slot not empty */
    else {
        bool key_taken = HashTable::check_key_taken(node.key);
        if(key_taken == false) {
            Node* dummy = this->T[index_ht];
            this->T[index_ht] = new Node;
            this->T[index_ht]->key = node.key;
            this->T[index_ht]->data = node.data;
            this->T[index_ht]->next = dummy;
            this->T[index_ht]->prev = NULL;
            dummy->prev = this->T[index_ht];
            this->size_table++;
        }
        else {}
    }
}

Node* HashTable::get_node_ptr(int key) {
    int index_ht = HashTable::hash_fcn(key);
    Node* node_ptr_iter = this->T[index_ht];
    /* Case: Slot not empty */
    if(node_ptr_iter != NULL) {
        /* Case: One element in list */
        if(node_ptr_iter->next == NULL && node_ptr_iter->prev == NULL) {
            if(node_ptr_iter->key == key) {
                return node_ptr_iter;
            }
        }
        /* Case: Check all but last node in list, for lists greater than 1 */
        while(node_ptr_iter->next != NULL) {
            if(node_ptr_iter->key == key) {
                return node_ptr_iter;
            }
            else {
                node_ptr_iter = node_ptr_iter->next;
            }
        }
        /* Case: Check last node in list, for lists greater than 1 */
        if(node_ptr_iter->next == NULL && node_ptr_iter->prev != NULL) {
            if(node_ptr_iter->key == key) {
                return node_ptr_iter;
            }
        }
    }
    /* Case: Slot is empty */
    else {std::cout << "Slot is empty" << std::endl;}

    return NULL;
}

void HashTable::delete_node(int key) {
    int index_ht = HashTable::hash_fcn(key);
    Node* node_ptr = HashTable::get_node_ptr(key);
    /* Case: Node with matching key found */
    if(node_ptr != NULL) {
        /* Case: Only one node in list */
        if(node_ptr->next == NULL && node_ptr->prev == NULL) {
            this->T[index_ht] = NULL;
            this->size_table--;
            delete node_ptr;
        }
        /* Case: Last node in list, for lists greater than 1 */
        else if(node_ptr->next == NULL && node_ptr->prev != NULL) {
            node_ptr->prev->next = NULL;
            this->size_table--;
            delete node_ptr;
        }
        /* Case: First node in list, for lists greater than 1 */
        else if(node_ptr->next != NULL && node_ptr->prev == NULL) {
            this->T[index_ht] = node_ptr->next;
            node_ptr->next->prev = NULL;
            this->size_table--;
            delete node_ptr;
        }
        /* Case: Central nodes, for lists greater than 1 */
        else if(node_ptr->next != NULL && node_ptr->prev != NULL) {
            node_ptr->next->prev = node_ptr->prev;
            node_ptr->prev->next = node_ptr->next;
            this->size_table--;
            delete node_ptr;
        }
        else{}
    }
    /* Case: No node with matching key found */
    else {
        std::cout <<
                     "Unable to delete node. No node with matching key found"
                  << std::endl;
    }
}

void HashTable::delete_table() {
    for(int i = 0; i < this->m; ++i) {
        /* Case: Slot not empty */
        if(this->T[i] != NULL) {
            /* Case: All elements except last, for lists greater than 1*/
            while(this->T[i]->next != NULL) {
                HashTable::delete_node(this->T[i]->key);
            }
            /* Case: Only one element in list */
            if(this->T[i]->next == NULL && this->T[i]->prev == NULL) {
                HashTable::delete_node(this->T[i]->key);
            }
        }
        /* Case: Slot empty */
        else {}
    }
}

int HashTable::get_size_table() {
    return this->size_table;
}
