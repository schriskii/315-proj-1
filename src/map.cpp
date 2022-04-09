#include "map.hpp"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdint>
#include <iostream>

Map::Map() {
	
}

bool Map::add_rec(const char *key, int val, Node *node){
	
	// base case
	if (key[0] == '\0'){
		if (node->get_id() == 0){
			node->set_id(val);
			node->inc_count(1);
			return true;
		}
		else{
			return false;
		}
	}
	
	if (node->get_ptr(key[0]) == NULL){
		Node new_node;
		node->set_ptr(key[0], new Node());
		num_nodes++;
	}
	
	if (add_rec(&key[1], val, node->get_ptr(key[0]))){
		node->inc_count(1);
		return true;
	}
	else{
		return false;
	}
}

bool Map::add(const char *key, int val) {
	return add_rec(key, val, &master_node);
}

bool Map::get(const char *key, int &ret) {
	Node *here = &master_node;
	char *cur = (char*)key;
	for (;cur[0] != '\0'; cur++){
		if (here->get_ptr(cur[0]) == NULL){
			return false;
		}
		
		here = here->get_ptr(cur[0]);
	}
	
	
	if (cur[0] == '\0'){
		if (here->get_id() == 0){
			return false;
		}
		else{
			ret = here->get_id();
			return true;
		}
	}
	
	return false;
}

int Map::size() { // in bytes; only heap memory
	int size_of_id = 4;
	int size_of_count = 4;
	int size_of_ptrs = 8 * 27;
	int size_of_node = size_of_id + size_of_count + size_of_ptrs;
	return num_nodes * size_of_node;
}

bool Map::rem_rec(const char *key, Node *node){
	
	// base case
	if (key[0] == '\0'){
		if (node->get_id() != 0){
			node->inc_count(-1);
			return true;
		}
		else{
			return false;
		}
	}
	
	if (node->get_ptr(key[0]) == NULL){
		return false;
	}
	
	if (rem_rec(&key[1], node->get_ptr(key[0]))){
		if (node->get_ptr(key[0])->inc_count(0) < 1){
			delete node->get_ptr(key[0]);
			node->set_ptr(key[0], NULL);
			num_nodes--;
		}
		node->inc_count(-1);
		return true;
	}
	else{
		return false;
	}
}

bool Map::remove(const char *key) {
	return rem_rec(key, &master_node);
}

int Map::howMany(const char *prefix) {
	Node *here = &master_node;
	char *cur = (char*)prefix;
	for (;cur[0] != '\0'; cur++){
		if (here->get_ptr(cur[0]) == NULL){
			return 0;
		}
		
		here = here->get_ptr(cur[0]);
	}
	
	if (cur[0] == '\0'){
		return here->inc_count(0);
	}
	
	return 0;
}

void Map::print_rec(Node *node, int level, bool capital){
	for (int i = 0; i < 27; i++){
		if (node->get_ptr((char)i) != NULL){
			for (int j = 0; j < level; j++){
				std::cout << "-";
			}
			if (i > 0) std::cout << (char)((capital ? 64 : 96) + i);
			else std::cout << "_";
			if (node->get_ptr((char)i)->get_id() != 0){
				for (int j = 0; j < 50 - level; j++){
					std::cout << "-";
				}
				std::cout << node->get_ptr((char)i)->get_id();
			}
			std::cout << "\n";
			print_rec(node->get_ptr((char)i), level + 1, i == 0);
		}
	}
}

void Map::print(){
	print_rec(&master_node, 0, true);
}

Map::~Map() {
	
}



void Node::set_id(int n){
	id = n;
}

int Node::get_id(){
	return id;
}

void Node::set_ptr(char n, Node* obj){
	ptrs[n % 32] = obj;
}

Node* Node::get_ptr(char n){
	return ptrs[n % 32];
}

int Node::inc_count(int n){
	count += n;
	return count;
}

Node::~Node(){
	for (int i = 0; i < 27; i++){
		if (ptrs[i] != NULL){
			delete ptrs[i];
			ptrs[i] = NULL;
		}
	}
}




