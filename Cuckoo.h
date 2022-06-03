#pragma once

#include <openssl/sha.h>
#include <set>
#include "Table.h"
#include <string>

class CuckooFilter
{
public:
	int number_of_buckets;
	int bucket_size;
	int fingerprint_size_in_bits;
	std::vector<double> insertion_time;
	std::vector<double> mnk_counter;
	std::set<std::string> not_stored;
	std::set<std::string> test_set;

	CuckooFilter(int number_of_buckets, int bucket_size, int fingerprint_size_in_bits);

	/**
	Returns H_KEY structure which has 3 values: first hash (32 bits), second hash (32 bits) and fingerprint (32 bits).
	@param hash - uint64_t hash
	@return H_KEY - structure with values: first hash, second hash and fingerprint.
	*/
	struct H_KEY AddrAndFingerprint(uint64_t hash);

	Table construct_table(const char *filename, int interval, int MNK, bool reduce_relocations);

	void test_on_file(const char* filename, const char* results, Table table);

	void test_on_random(const char* filename, const char* results, Table table, int number_of_unique, int length_of_sequence, int interval, bool is_it_in);

	std::set<std::string> load_random(const char* filename, int number_of_unique, int length_of_sequence, int interval);

private:
	std::set<std::string> load_file(const char* filename, int interval);
};

/**
Holder for output data. It is used to easily  transform output of SHA1 algorithm to uint32_t or uint64_t format.
*/
union HashOutput {
	uint32_t hash_32;
	uint64_t hash_64;
	unsigned char sha_output[SHA_DIGEST_LENGTH];
};

/**
Structure that holds result values.
*/
struct H_KEY
{
	uint32_t h_1;
	uint32_t h_2;
	uint32_t fingerprint;
};

std::vector<std::string> split_by_word(std::string s);

double get_average_from_vector(std::vector<double> data);

double get_average_from_vector(std::vector<double> data);

uint64_t return_hash(unsigned char* to_hash);