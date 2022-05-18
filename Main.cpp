#include <iostream>
#include "Cuckoo.h"
#include "Table.h"

using namespace std;

int main() {

    unsigned char s_2[] = "Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh Mgfhgfhgdjdg jh gfhdghdghgh dghdghdgh";
    unsigned char s_3[] = "Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh";

    CuckooFilter filter(100000, 4, 2);
    uint64_t returned = return_hash(s_2);
    uint64_t returned_2 = return_hash(s_3);

    H_KEY got = filter.AddrAndFingerprint(returned);
    cout << "hash1_1: " << got.h_1 << endl;
    cout << "hash1_2: " << got.h_2 << endl;
    cout << "fingerprint1: " << got.fingerprint << endl;

    H_KEY got_2 = filter.AddrAndFingerprint(returned_2);
    cout << "hash2_1: " << got_2.h_1 << endl;
    cout << "hash2_2: " << got_2.h_2 << endl;
    cout << "fingerprint2: " << got_2.fingerprint << endl;

    Table table1(10000, 4, 100);

    table1.insert(got.h_1, got.h_2, got.fingerprint);
    table1.insert(got_2.h_1, got_2.h_2, got_2.fingerprint);

    cout << "fingerprint1 se nalazi u tablici za hash1? " << table1.lookup(got.h_1, got.h_2, got.fingerprint) << endl;
    cout << "fingerprint2 se nalazi u tablici za hash2? " << table1.lookup(got_2.h_1, got_2.h_2, got_2.fingerprint) << endl;
    cout << "fingerprint1 se nalazi u tablici za hash2? " << table1.lookup(got_2.h_1, got_2.h_2, got.fingerprint) << endl;

    system("Pause");
}