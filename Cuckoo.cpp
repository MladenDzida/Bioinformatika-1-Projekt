#include <iostream>
#include "Cuckoo.h"
#include <winsock2.h>
#include <windows.h>
#include <openssl/sha.h>
#include <cmath>
#include <bitset>

using namespace std;

uint64_t return_hash(unsigned char* to_hash) {
    // define length of characters
    size_t length = strlen((char*)to_hash);
    HashOutput output;

    // predefine output of SHA1 algorithm
    unsigned char* results = new unsigned char[SHA_DIGEST_LENGTH];
    SHA1(to_hash, length, output.sha_output);

    uint64_t ret = 0;
    // return value of SHA1
    ret = output.hash_64;

    return ret;
}

CuckooFilter::CuckooFilter(int number_of_buckets,int bucket_size, int fingerprint_size_in_bits){
    this->number_of_buckets = number_of_buckets;
    this->bucket_size = bucket_size;
    this-> fingerprint_size_in_bits = fingerprint_size_in_bits;
}

struct H_KEY CuckooFilter::AddrAndFingerprint(uint64_t has) {
    H_KEY to_ret;
    uint32_t mask = (uint32_t) (pow(2, 32)) - 1;

    to_ret.h_1 = mask & (has >> 32);
    to_ret.fingerprint = (has & mask) % ((uint32_t) (pow(2, this->fingerprint_size_in_bits) - 1));

    HashOutput tmp;
    // store fingerprint inside Union tmp in order to transform value to unsigned char.
    tmp.hash_32 = to_ret.fingerprint;
    // send fingerprint to hashing function, but use unsigned char representation
    to_ret.h_2 = to_ret.h_1 ^ (uint32_t) return_hash(tmp.sha_output);

    return to_ret;
}
