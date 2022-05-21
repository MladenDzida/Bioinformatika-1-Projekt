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
#include <sstream>
#include <time.h>
#include <numeric>
#include <iomanip>
#include <chrono>

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

double get_average_from_vector(std::vector<double> data) {
    if (data.empty()) {
        return 0;
    }
    return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

double get_sum_from_vector(std::vector<double> data) {
    if (data.empty()) {
        return 0;
    }
    return std::accumulate(data.begin(), data.end(), 0.0);
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
        char* buffer = new char[length_of_sequence + 1];
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

                if (file.tellg() == -1)
                    break;

                if (i != 0) {
                    i--;
                }
            }
        }

        if (file.tellg() == -1) {
            break;
        }
        unique.insert(string(buffer));
    }
    file.close();

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
    bool flag = false;
    bool first = false;
    int position = 0;

    while (file.tellg() != -1) {
        flag = false;
        char* buffer = new char[interval + 1];
        buffer[interval] = '\0';

        file.seekg(position, ios::beg);
        file.read(buffer, interval);

        for (int i = 0; i < interval; i++) {
            if (buffer[i] == '\n' && i == 0) {
                flag = true;
            }
            if (buffer[i] == '\n') {
                for (int j = i; j < interval - 1; j++) {
                    buffer[j] = buffer[j + 1];
                }
                file.read(buffer + interval - 1, 1);
            }
        }

        if (file.tellg() != -1 && !flag) {
            // cout << buffer << endl;
            unique.insert(string(buffer));
            counter++;
            if (counter % 100000 == 0) {
                cout << counter << endl;
            }
        }
        position++;
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

        auto t1 = std::chrono::high_resolution_clock::now();
        uint64_t hash = return_hash((unsigned char*) it->c_str());
        H_KEY got = this->AddrAndFingerprint(hash);
        bool res = table1.insert(got.h_1, got.h_2, got.fingerprint);
        auto t2 = std::chrono::high_resolution_clock::now();

        auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        std::chrono::duration<double, std::milli> ms_double = t2 - t1;

        this->insertion_time.push_back((double)ms_double.count());

        // this->insertion_time.push_back((double)(clock() - begin_time));
        this->mnk_counter.push_back(table1.MNK_counter);
        table1.MNK_counter = 0;
        if (!res) {
            cout << *it << endl;
            table1.not_stored++;
        }
        else {
            table1.number_of_insertions++;
        }

        if (counter % 100000 == 0) {
            cout << "P:" << counter << endl;
        }
    }
    return table1;
}

std::vector<string> split_by_word(string s) {
    string s2 = s;
    s2.erase(std::remove(s2.begin(), s2.end(), '\n'), s2.end());
    
    std::stringstream ss(s2);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);

    return vstrings;
}

void CuckooFilter::test_on_file(const char* filename, const char* results, Table table) {
    ifstream file;
    file.open(filename);

    ifstream writer_check;
    writer_check.open(results);

    ofstream writer;
    writer.open(results, std::ios_base::app);

    if (!file) {
        cout << "Error opening a file." << endl;
        exit(1);
    }

    if (!writer_check) {
        cout << "Creating file..." << endl;
        std::ofstream writer(results);

        if (!writer) {
            cout << "Error writing to file." << endl;
            exit(1);
        }

        writer << "per_fill,bits,num_of_insertion_call,num_of_insert,length_of_sequence,num_of_buckets,bucket_size,MNK,avg_MNK,sum_MNK,reduce,tp,fp,fn,tn,not_stored,random,insertion_time,insertion_time_avg,fingerprint_size,row_fill" << endl;
    }
    writer_check.close();

    std::string str;
    bool b;
    int interval = -1;
    while (std::getline(file, str))
    {
        std::vector<std::string> words = split_by_word(str);
        std::istringstream(words[1]) >> b;

        interval = words[0].length();

        uint64_t returned = return_hash((unsigned char*) words[0].c_str());
        H_KEY got = this->AddrAndFingerprint(returned);
        table.lookup(got.h_1, got.h_2, got.fingerprint, b);
    }
    file.close();

    Info info = table.get_info();
    writer
        << info.per_fill
        << ","
        << info.bits
        << ","
        << info.num_of_insertion_call
        << ","
        << info.num_of_insertion
        << ","
        << interval
        << ","
        << info.num_of_buckets
        << ","
        << info.bucket_size
        << ","
        << info.MNK
        << ","
        << get_average_from_vector(this->mnk_counter)
        << ","
        << get_sum_from_vector(this->mnk_counter)
        << ","
        << info.reduce
        << ","
        << info.tp
        << ","
        << info.fp
        << ","
        << info.fn
        << ","
        << info.tn
        << ","
        << info.not_stored
        << ","
        << "False"
        << ","
        << get_sum_from_vector(this->insertion_time)
        << ","
        << get_average_from_vector(this->insertion_time)
        << ","
        << this->fingerprint_size_in_bits
        << ","
        << info.row_fill
        << endl;
    this->mnk_counter.clear();
    this->insertion_time.clear();
}

void CuckooFilter::test_on_random(const char* filename, const char* results, Table table, int number_of_unique, int length_of_sequence, int interval, bool is_it_in) {
    ifstream writer_check;
    writer_check.open(results);

    ofstream writer;
    writer.open(results, std::ios_base::app);

    if (!writer_check) {
        cout << "Creating file..." << endl;
        std::ofstream writer(results);

        if (!writer) {
            cout << "Error writing to file." << endl;
            exit(1);
        }

        writer << "per_fill,bits,num_of_insertion_call,num_of_insert,length_of_sequence,num_of_buckets,bucket_size,MNK,avg_MNK,sum_MNK,reduce,tp,fp,fn,tn,not_stored,random,insertion_time,insertion_time_avg,fingerprint_size,row_fill" << endl;
    }
    writer_check.close();

    std::set<std::string> rand = this->load_random(filename, number_of_unique, length_of_sequence, interval);

    std::set<std::string>::iterator iterator;

    for (iterator = rand.begin(); iterator != rand.end(); ++iterator) {
        uint64_t returned = return_hash((unsigned char*) (*(iterator)).c_str());
        H_KEY got = this->AddrAndFingerprint(returned);
        bool loook = table.lookup(got.h_1, got.h_2, got.fingerprint, is_it_in);
    }

    Info info = table.get_info();
    writer
        << info.per_fill
        << ","
        << info.bits
        << ","
        << info.num_of_insertion_call
        << ","
        << info.num_of_insertion
        << ","
        << length_of_sequence
        << ","
        << info.num_of_buckets
        << ","
        << info.bucket_size
        << ","
        << info.MNK
        << ","
        << get_average_from_vector(this->mnk_counter)
        << ","
        << get_sum_from_vector(this->mnk_counter)
        << ","
        << info.reduce
        << ","
        << info.tp
        << ","
        << info.fp
        << ","
        << info.fn
        << ","
        << info.tn
        << ","
        << info.not_stored
        << ","
        << "True" 
        << ","
        << get_sum_from_vector(this->insertion_time)
        << ","
        << get_average_from_vector(this->insertion_time)
        << ","
        << this->fingerprint_size_in_bits
        << ","
        << info.row_fill
        << endl;
    this->mnk_counter.clear();
    this->insertion_time.clear();
    cout << "DONE" << endl;
}