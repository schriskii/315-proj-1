#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "map.hpp"

using namespace std;

int main(int argc, char *argv[]) {
	Map map;
	
	ifstream first("firstnames.txt");
	ifstream last("lastnames.txt");
	
	string text, text2;
	
	int i = 0;
	
	if (true) while (getline(first, text)){
		while (getline(last, text2)){
			string text3 = text + " " + text2;
			map.add(text3.c_str(), i);
			cout << i++ << "\n";
		}
	}
	
	map.print();
	
	std::cout << map.size() << " bytes\n";
	
	/*
	std::cout << map.add("woah", 100) << "\n";
	std::cout << map.add("woahg", 100) << "\n";
	
	// std::cout << map.remove("woahh") << "\n";
	// std::cout << map.remove("woa") << "\n";
	// std::cout << map.remove("woahg") << "\n";
	
	std::cout << "----------\n";
	
	std::cout << map.howMany("w") << "\n";
	std::cout << map.howMany("wo") << "\n";
	std::cout << map.howMany("k") << "\n";
	std::cout << map.howMany("woa") << "\n";
	std::cout << map.howMany("woah") << "\n";
	std::cout << map.howMany("woahg") << "\n";
	*/
}

