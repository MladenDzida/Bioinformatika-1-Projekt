#pragma once

#include <vector>
#include <iostream>

using namespace std;

class Table {
public:
	int number_of_buckets;
	int bucket_size;
	int MNK;
	int MNK_counter;
	bool reduce_relocations;
	int number_of_insertion_call;
	int number_of_insertions;
	int tp;
	int tn;
	int fp;
	int fn;
	int not_stored;

	Table(int number_of_buckets, int bucket_size, int MNK, bool use_random);

	bool insert(uint32_t hash1, uint32_t hash2, uint32_t fingerprint);

	double get_fill();

	uint32_t get_random(uint32_t hash);

	bool lookup(uint32_t hash1, uint32_t hash2, uint32_t fingerprint, bool in);

	void print_table();

	struct Info get_info();

	~Table() {

	};

	double avg_row_fill();

	std::vector<std::vector<uint32_t>> hash_table;

private:

	int position(uint32_t hash);

	void print_horizontal_line(char c);
};

struct Info {
	double per_fill;
	double bits;
	int num_of_insertion_call;
	int num_of_insertion;
	int num_of_buckets;
	int bucket_size;
	int MNK;
	bool reduce;
	int tp;
	int fp;
	int fn;
	int tn;
	int not_stored;
	double avg_row_fill;
};