#include <cstdint>
#include <cstddef>

#ifndef MAP_H
#define MAP_H

class Node{
	public:
		void set_id(int n);		// set id to n
		int get_id();			// ret id
		void set_ptr
			(char n, Node* obj);// set pointer at pos n; used for both add and remove (NULL)
		Node* get_ptr(char n);	// ret pointer at pos n
		int inc_count(int n);	// increment count by n; return new count
		~Node();
	private:
		std::uint32_t id;		// number id; 0 if this is not the last letter of a name
		std::uint32_t count = 0;// number of names contained in this node
		Node* ptrs[27] = {NULL};// pointers to nodes for space + 26 letters; NULL if not exist
};

class Map{
	public:
		Map();
		
		// add string, store int, return success
		bool add(const char *key, int val);
		
		// find string, set ret to int, return success
		bool get(const char *key, int &ret);
		
		// return size of data structure
		int size();
		
		// remove string, return success
		bool remove(const char *key);
		
		// return how many start with prefix
		int howMany(const char *prefix);
		
		// visually show the whole structure
		void print();
		
		// free memory
		~Map();
		
	private:
		bool add_rec(const char *key, int val, Node *node);
		bool rem_rec(const char *key, Node *node);
		void print_rec(Node *node, int level, bool capital);
		Node master_node;
		int num_nodes = 0; // nodes on the HEAP
};

#endif
