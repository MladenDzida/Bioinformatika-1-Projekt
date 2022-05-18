#include <iostream>
#include "Cuckoo.h"
#include <winsock2.h>
#include <windows.h>
#include <openssl/sha.h>
#include <cmath>
#include <bitset>

using namespace std;

CuckooFilter::CuckooFilter(int number_of_buckets,int bucket_size, int fingerprint_size_in_bits){
    this->number_of_buckets = number_of_buckets;
    this->bucket_size = bucket_size;
    this-> fingerprint_size_in_bits = fingerprint_size_in_bits;
}

uint64_t CuckooFilter::return_hash(unsigned char *to_hash){
    // define length of characters
    size_t length = strlen((char*)to_hash);
    HashOutput output;

    // predefine output of SHA1 algorithm
    unsigned char *results = new unsigned char[SHA_DIGEST_LENGTH];
    SHA1(to_hash, length, output.sha_output);

    uint64_t ret = 0;
    // return value of SHA1
    ret = output.hash_64;

    return ret;
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
    to_ret.h_2 = to_ret.h_1 ^ (uint32_t) this->return_hash(tmp.sha_output);

    return to_ret;
}




int main(){

    unsigned char s_2[] = "Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh Mgfhgfhgdjdg jh gfhdghdghgh dghdghdgh";
    unsigned char s_3[] = "Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh";
    
    CuckooFilter filter(100000, 4, 2);
    uint64_t returned = filter.return_hash(s_2);
    uint64_t returned_2 = filter.return_hash(s_3);

    H_KEY got = filter.AddrAndFingerprint(returned);
    cout << got.h_1 << endl;
    cout << got.h_2 << endl;
    cout << got.fingerprint << endl;

    H_KEY got_2 = filter.AddrAndFingerprint(returned_2);
    cout << got_2.h_1 << endl;
    cout << got_2.h_2 << endl;
    cout << got_2.fingerprint << endl;

    system("Pause");
}