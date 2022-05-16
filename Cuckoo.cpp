#include <iostream>
#include "Cuckoo.h"
#include "openssl/sha.h"
using namespace std;

CuckooFilter::CuckooFilter(int number_of_buckets,int bucket_size, int fingerprint_size_in_bits){
    this->number_of_buckets = number_of_buckets;
    this->bucket_size = bucket_size;
    this-> fingerprint_size_in_bits = fingerprint_size_in_bits;
}

int CuckooFilter::return_hash(){r
    return 12345;
}


int main(){
    
    CuckooFilter filter(100000, 4, 8);
    cout << filter.return_hash() << endl;

    // const unsigned char str[] = "Original String";
    // unsigned char hash[SHA_DIGEST_LENGTH]; // == 20
    // SHA1(str, sizeof(str) - 1, hash);

    system("Pause");
}