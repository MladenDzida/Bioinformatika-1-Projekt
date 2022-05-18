#pragma once

#include <vector>
#include "Cuckoo.h"

class Table {
public:
	int number_of_buckets;
	int bucket_size;

	Table(int number_of_buckets, int bucket_size);

	bool insert(uint32_t hash);

	double get_fill();

	uint32_t get_random(uint32_t hash);

private:
	std::vector<std::vector<uint32_t>> hash_table;

	int position(uint32_t hash);
};