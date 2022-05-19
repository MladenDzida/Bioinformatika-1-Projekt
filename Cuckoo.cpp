#include <iostream>
#include "Cuckoo.h"
#include <winsock2.h>
#include <windows.h>
#include <openssl/sha.h>
#include <cmath>
#include <bitset>
#include <string>
#include <fstream>
#include <set>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "Table.h"

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

    srand(unsigned(time(0)));
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

set<string> CuckooFilter::load_random(const char *filename, int number_of_unique, int length_of_sequence, int interval) {
    ifstream file;
    file.open(filename);

    if (!file) {
        cout << "Can't open file." << endl;
        exit(1);
    }

    set<string> unique;


    for (int n = 0; n < number_of_unique; n++) {
        char* buffer = new char[length_of_sequence];
        buffer[length_of_sequence] = '\0';

        int ran = rand() % interval + 1;

        file.seekg(ran + file.tellg(), ios::beg);
        file.read(buffer, length_of_sequence);

        for (int i = 0; i < length_of_sequence; i++) {
            if (buffer[i] == '\n') {
                for (int j = i; j < length_of_sequence - 1; j++) {
                    buffer[j] = buffer[j + 1];
                }
                file.read(buffer + length_of_sequence - 1, 1);
                i--;
            }
        }

        if (file.tellg() == -1) {
            break;
        }
        unique.insert(string(buffer));
    }

    return unique;
}

set<string> CuckooFilter::load_file(const char* filename, int interval) {
    ifstream file;
    file.open(filename);

    if (!file) {
        cout << "Can't open file." << endl;
        exit(1);
    }

    set<string> unique;
    int counter = 0;

    while (file.tellg() != -1) {
        char* buffer = new char[interval + 1];
        buffer[interval] = '\0';

        file.read(buffer, interval);

        for (int i = 0; i < interval; i++) {
            if (buffer[i] == '\n') {
                for (int j = i; j < interval - 1; j++) {
                    buffer[j] = buffer[j + 1];
                }
                file.read(buffer + interval - 1, 1);
                i--;
            }
        }

        if (file.tellg() != -1) {
            unique.insert(string(buffer));
            // cout << buffer << endl;
            counter++;
            if (counter % 100000 == 0) {
                cout << counter << endl;
            }
        }


        file.seekg(-(interval - 1 - file.tellg()), ios::beg);
    }
    return unique;
}

Table CuckooFilter::construct_table(const char *filename, int interval, int MNK, bool reduce_relocations) {
    set<string> unique = this->load_file(filename, interval);

    cout << "SIZE: " << unique.size() << endl;

    Table table1(this->number_of_buckets, this->bucket_size, MNK, reduce_relocations);

    set<string>::iterator it;

    int counter = 0;

    for (it = unique.begin(); it != unique.end(); ++it) {
        counter++;
        uint64_t hash = return_hash((unsigned char*) it->c_str());
        H_KEY got = this->AddrAndFingerprint(hash);

        bool res = table1.insert(got.h_1, got.h_2, got.fingerprint);
        table1.MNK_counter = 0;
        if (!res) {
            cout << *it << endl;
        }

        if (counter % 100000 == 0) {
            cout << "P:" << counter << endl;
        }
    }
    return table1;
}