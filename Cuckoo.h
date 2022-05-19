#pragma once

#include <openssl/sha.h>
#include <set>
#include "Table.h"
#include <string>

uint64_t return_hash(unsigned char* to_hash);

class CuckooFilter
{
public:
	int number_of_buckets;
	int bucket_size;
	int fingerprint_size_in_bits;

	CuckooFilter(int number_of_buckets, int bucket_size, int fingerprint_size_in_bits);

	/**
	Calculate SHA1 on unsigned char *to_hash, and returns uint64_t reprezentation of output.
	@param to_hash - pointer to unsigned char array on which to calculate SHA1
	@return uint64_t - result
	*/

	/**
	Returns H_KEY structure which has 3 values: first hash (32 bits), second hash (32 bits) and fingerprint (32 bits).
	@param hash - uint64_t hash
	@return H_KEY - structure with values: first hash, second hash and fingerprint.
	*/
	struct H_KEY AddrAndFingerprint(uint64_t hash);

	Table construct_table(const char *filename, int interval, int MNK, bool reduce_relocations);

private:
	std::set<std::string> load_random(const char* filename, int number_of_unique, int length_of_sequence, int interval);
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