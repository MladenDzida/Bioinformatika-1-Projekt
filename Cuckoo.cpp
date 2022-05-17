#include <iostream>
#include "Cuckoo.h"
#include <winsock2.h>
#include <windows.h>
#include <openssl/sha.h>
#include <math.h>

using namespace std;

CuckooFilter::CuckooFilter(int number_of_buckets,int bucket_size, int fingerprint_size_in_bits){
    this->number_of_buckets = number_of_buckets;
    this->bucket_size = bucket_size;
    this-> fingerprint_size_in_bits = fingerprint_size_in_bits;
}

unsigned char *CuckooFilter::return_hash(unsigned char *to_hash){
    size_t length = strlen((char*)to_hash);

    cout << length << endl;
    
    unsigned char *results = new unsigned char[SHA_DIGEST_LENGTH];
    SHA1(to_hash, length, results);

    return results;
}

unsigned long CuckooFilter::transform_to_long(unsigned char* to_transform, int length) {
    unsigned long int to_return = 0;
    
    for (int i = 0; i < length; i++) {
        to_return |= to_transform[i] << (i * 8);
    }

    return to_return;
}




int main(){

    unsigned char s_2[] = "Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh Mgfhgfhgdjdg jh gfhdghdghgh dghdghdgh";
    unsigned char s_3[] = "Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh";

    
    CuckooFilter filter(100000, 4, 8);
    unsigned char posalji[] = "Idemo";
    unsigned char *posalji_pointer = posalji;

    unsigned char *results = filter.return_hash(s_2);
    unsigned char *results_2 = filter.return_hash(s_3);

    unsigned long int got = filter.transform_to_long(results, 20);
    unsigned long int got_2 = filter.transform_to_long(results_2, 20);

    cout << got << endl;
    cout << got_2 << endl;
    // cout << *results << endl;

    //int bucket = 3;
    //const unsigned char s_1[] = "Mladei";
    //const unsigned char s_2[] = "Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh Mgfhgfhgdjdg jh gfhdghdghgh dghdghdgh";;
    //const unsigned char s_3[] = "Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh";

    //unsigned char end[SHA_DIGEST_LENGTH];

    //SHA1(s_1, SHA_DIGEST_LENGTH, end);
    //unsigned long int l_1 = end[0] | (end[1] << 8) | (end[2] << 16) | (end[3] << 24);

    //SHA1(s_2, SHA_DIGEST_LENGTH, end);
    //unsigned long int l_2 = end[0] | (end[1] << 8) | (end[2] << 16) | (end[3] << 24);

    //SHA1(s_3, SHA_DIGEST_LENGTH, end);
    //unsigned long int l_3 = end[0] | (end[1] << 8) | (end[2] << 16) | (end[3] << 24);

    //printf("\n");

    //// cout << l_1 % bucket << endl;
    //// cout << l_2 % bucket << endl;
    //// cout << l_3 % bucket << endl;

    //cout << l_1 << endl;
    //cout << l_2 << endl;
    //cout << l_3 << endl;

    system("Pause");
}