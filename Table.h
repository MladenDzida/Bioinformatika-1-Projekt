#pragma once

#include <vector>

class Table {
public:
	int number_of_buckets;
	int bucket_size;
	int MNK;
	int MNK_counter;
	bool reduce_relocations;

	Table(int number_of_buckets, int bucket_size, int MNK, bool use_random);

	bool insert(uint32_t hash1, uint32_t hash2, uint32_t fingerprint);

	double get_fill();

	uint32_t get_random(uint32_t hash);

	bool lookup(uint32_t hash1, uint32_t hash2, uint32_t fingerprint);

	void print_table();

private:
	std::vector<std::vector<uint32_t>> hash_table;

	int position(uint32_t hash);

	void print_horizontal_line(char c);
};