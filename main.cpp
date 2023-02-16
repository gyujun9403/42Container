#include <iostream>
#include <string>
#include <deque>
	#include "containers/map.hpp"
	#include "containers/stack.hpp"
	#include "containers/vector.hpp"

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))


int main() {
	ft::map<int, int> map_int;
    //size_t C = 25;
	for (size_t i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(i, i));
	}

	return (0);
}