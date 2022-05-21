#include "Table.h"
#include <vector>
#include "Cuckoo.h"
#include <iterator>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <algorithm>
#include <iterator>

using namespace std;

Table::Table(int number_of_buckets, int bucket_size, int MNK, bool reduce_relocations){
	this->number_of_buckets = number_of_buckets;
	this->bucket_size = bucket_size;
	this->MNK = MNK;
	this->MNK_counter = 0;
	this->reduce_relocations = reduce_relocations;
	this->number_of_insertion_call = 0;
	this->number_of_insertions = 0;
	this->tp = 0;
	this->tn = 0;
	this->fp = 0;
	this->fn = 0;
	this->not_stored = 0;

	srand(unsigned(time(0)));

	for (int i = 0; i < number_of_buckets; i++) {
		std::vector<uint32_t> tmp;
		this->hash_table.push_back(tmp);
	}
}

int Table::position(uint32_t hash) {
	return hash % this->number_of_buckets;
}

bool Table::insert(uint32_t hash1, uint32_t hash2, uint32_t fingerprint) {
	this->number_of_insertion_call++;

	int position1 = this->position(hash1);
	int position2 = this->position(hash2);

	
	if (this->hash_table[position1].size() < this->bucket_size && this->hash_table[position2].size() < this->bucket_size) {
		
		if (this->reduce_relocations == false) {
			int random_bucket = rand() % 2 + 1;
			if (random_bucket == 1)
				hash_table[position1].push_back(fingerprint);
			else
				hash_table[position2].push_back(fingerprint);
		}
		else {
			if (this->hash_table[position1].size() <= this->hash_table[position2].size())
				hash_table[position1].push_back(fingerprint);
			else
				hash_table[position2].push_back(fingerprint);
		}
		return true;
	}
	else if (this->hash_table[position1].size() >= this->bucket_size && this->hash_table[position2].size() < this->bucket_size) {
		hash_table[position2].push_back(fingerprint);
		return true;
	}
	else if (this->hash_table[position1].size() < this->bucket_size && this->hash_table[position2].size() >= this->bucket_size) {
		hash_table[position1].push_back(fingerprint);
		return true;
	}
	else{
		if (this->MNK_counter >= this->MNK) {
			return false;
		}

		int random_bucket = rand() % 2 + 1;
		int random_compartment = rand() % this->bucket_size;

		if (random_bucket == 1) {
			uint32_t fingerprint_to_relocate = hash_table[position1][random_compartment];
			hash_table[position1][random_compartment]= fingerprint;
			HashOutput tmp;
			tmp.hash_32 = fingerprint_to_relocate;
			uint32_t new_hash = hash1 ^ (uint32_t)return_hash(tmp.sha_output);
			this->MNK_counter += 1;
			bool confirmation = this->insert(hash1, new_hash, fingerprint_to_relocate);
			if (confirmation == false) {
				return false;
			}
		}
		else {
			uint32_t fingerprint_to_relocate = hash_table[position1][random_compartment];
			hash_table[position1][random_compartment] = fingerprint;
			HashOutput tmp;
			tmp.hash_32 = fingerprint_to_relocate;
			uint32_t new_hash = hash2 ^ (uint32_t)return_hash(tmp.sha_output);
			this->MNK_counter += 1;
			bool confirmation = this->insert(new_hash, hash2, fingerprint_to_relocate);
			if (confirmation == false) {
				return false;
			}
		}
		
	}

	return true;
}

double Table::get_fill() {
	std::vector<vector<uint32_t>>::iterator iter;

	int size = 0;

	for (int i=0; i < this->hash_table.size(); i++) {
		size += this->hash_table[i].size();
	}

	return ((double) size / (this->number_of_buckets * this->bucket_size));
}

uint32_t Table::get_random(uint32_t hash) {
	std::vector<uint32_t> vec = this->hash_table[this->position(hash)];
	int random_position = vec.size() * (rand() / (RAND_MAX + 1.0));

	uint32_t tmp = vec[random_position];
	vec.erase(vec.begin() + random_position);

	return tmp;
}

bool Table::lookup(uint32_t hash1, uint32_t hash2, uint32_t fingerprint, bool in) {
	int position1 = this->position(hash1);
	int position2 = this->position(hash2);

	if (std::find(this->hash_table[position1].begin(), this->hash_table[position1].end(), fingerprint) != this->hash_table[position1].end() || std::find(this->hash_table[position2].begin(), this->hash_table[position2].end(), fingerprint) != this->hash_table[position2].end()) {
		if (in) {
			this->tp++;
		}
		else {
			this->fp++;
		}
		return true;
	}
	else {
		if (in) {
			this->fn++;
		}
		else {
			this->tn++;
		}
		return false;
	}
}

void Table::print_horizontal_line(char c) {
	for (int i = 0; i < this->bucket_size; i++) {
		cout
			<< left
			<< '+' << c << c << c << c << c << c << c << c << c << c << c << c;
	}
	cout << '+' << endl;
}

void Table::print_table() {
	this->print_horizontal_line('=');

	for (int i = 0; i < this->bucket_size; i++) {
		cout
			<< left
			<< setw(1)
			<< "|"
			<< setw(12)
			<< "T:" + std::to_string(i);
	}
	cout << "|" << endl;

	this->print_horizontal_line('=');

	for (int i = 0; i < this->number_of_buckets; i++) {
		int max_bucket = this->hash_table[i].size();
		std::vector<uint32_t> tmp = this->hash_table[i];

		for (int j = 0; j < this->bucket_size; j++) {
			if (max_bucket > j) {
				cout
					<< left
					<< setw(1)
					<< "|"
					<< setw(12)
					<< tmp[j];
				continue;
			}

			cout
				<< left
				<< setw(13)
				<< "|";
		}
		cout << "|" << endl;

		this->print_horizontal_line('_');
	}
}

double Table::row_fill() {
	double sum = 0.0;
	for (int i = 0; i < this->number_of_buckets; i++) {
		if (this->hash_table[i].size() == this->bucket_size)
			sum += 1;
	}
	return sum;
}

struct Info Table::get_info() {
	Info info;
	info.per_fill = this->get_fill();
	info.bits = info.per_fill * (this->number_of_buckets * this->bucket_size) * 32;
	info.num_of_insertion_call = this->number_of_insertion_call;
	info.num_of_insertion = this->number_of_insertions;
	info.num_of_buckets = this->number_of_buckets;
	info.bucket_size = this->bucket_size;
	info.MNK = this->MNK;
	info.reduce = this->reduce_relocations;
	info.tp = this->tp;
	info.fp = this->fp;
	info.fn = this->fn;
	info.tn = this->tn;
	info.not_stored = this->not_stored;
	info.row_fill = this->row_fill();
	
	return info;
}
