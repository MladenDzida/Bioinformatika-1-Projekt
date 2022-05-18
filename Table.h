#pragma once

#include <vector>
#include "Cuckoo.h"

class Table {
public:
	int number_of_buckets;
	int bucket_size;
	int MNK;
	int MNK_counter;

	Table(int number_of_buckets, int bucket_size, int MNK);

	bool insert(uint32_t hash1, uint32_t hash2, uint32_t fingerprint);

	double get_fill();

	uint32_t get_random(uint32_t hash);

	bool lookup(uint32_t hash1, uint32_t hash2, uint32_t fingerprint);

private:
	std::vector<std::vector<uint32_t>> hash_table;

	int position(uint32_t hash);
};