#include <iostream>
#include "Cuckoo.h"
#include "Table.h"

using namespace std;

int main() {

    unsigned char s_2[] = "Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh Mgfhgfhgdjdg jh gfhdghdghgh dghdghdgh";
    unsigned char s_3[] = "Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh";
    unsigned char s_4[] = "Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh Mgfhgfhgdjdg jh gfhdghdghgh dghdghdgh";
    unsigned char s_5[] = "Mladen sas a dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh Mgfhgfhgdjdg jh gfhdghdghgh dghdghdgh";
    unsigned char s_6[] = "Mladen sas  dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh sgfhgfhgdjdg jh gfhdghdghgh dghdghdgh Mladen sas sadfsgfs dfgfsdgsfdh Mgfhgfhgdjdg jh gfhdghdghgh dghdghdgh";

    /*CuckooFilter filter(10000, 4, 2);

    uint64_t returned = return_hash(s_2);
    uint64_t returned_2 = return_hash(s_3);
    uint64_t returned_3 = return_hash(s_4);
    uint64_t returned_4 = return_hash(s_5);
    uint64_t returned_5 = return_hash(s_6);

    H_KEY got = filter.AddrAndFingerprint(returned);
    cout << "hash1_1: " << got.h_1 << endl;
    cout << "hash1_2: " << got.h_2 << endl;
    cout << "fingerprint1: " << got.fingerprint << endl;

    H_KEY got_2 = filter.AddrAndFingerprint(returned_2);
    cout << "hash2_1: " << got_2.h_1 << endl;
    cout << "hash2_2: " << got_2.h_2 << endl;
    cout << "fingerprint2: " << got_2.fingerprint << endl;

    H_KEY got_3 = filter.AddrAndFingerprint(returned_3);
    cout << "hash3_1: " << got_3.h_1 << endl;
    cout << "hash3_2: " << got_3.h_2 << endl;
    cout << "fingerprint3: " << got_3.fingerprint << endl;

    H_KEY got_4 = filter.AddrAndFingerprint(returned_4);
    cout << "hash4_1: " << got_4.h_1 << endl;
    cout << "hash4_2: " << got_4.h_2 << endl;
    cout << "fingerprint4: " << got_4.fingerprint << endl;

    H_KEY got_5 = filter.AddrAndFingerprint(returned_5);
    cout << "hash5_1: " << got_5.h_1 << endl;
    cout << "hash5_2: " << got_5.h_2 << endl;
    cout << "fingerprint5: " << got_5.fingerprint << endl;

    Table table1(3, 2, 4, false);

    cout << table1.get_fill() << endl;
    table1.insert(got.h_1, got.h_2, got.fingerprint);
    table1.print_table();
    cout << table1.get_fill() << endl;

    table1.insert(got_2.h_1, got_2.h_2, got_2.fingerprint);
    table1.print_table();
    cout << table1.get_fill() << endl;

    table1.insert(got_3.h_1, got_3.h_2, got_3.fingerprint);
    table1.print_table();
    cout << table1.get_fill() << endl;

    table1.insert(got_4.h_1, got_4.h_2, got_4.fingerprint);
    table1.print_table();
    cout << table1.get_fill() << endl;

    table1.insert(got_5.h_1, got_5.h_2, got_5.fingerprint);
    table1.print_table();
    cout << table1.get_fill() << endl;

    cout << "fingerprint1 se nalazi u tablici za hash1? " << table1.lookup(got.h_1, got.h_2, got.fingerprint) << endl;
    cout << "fingerprint2 se nalazi u tablici za hash2? " << table1.lookup(got_2.h_1, got_2.h_2, got_2.fingerprint) << endl;
    cout << "fingerprint1 se nalazi u tablici za hash2? " << table1.lookup(got_2.h_1, got_2.h_2, got.fingerprint) << endl;*/

    CuckooFilter filter(10, 4, 18);
    // set<char*> ha = filter.load_file(
    //     "C:\\Users\\grga\\Documents\\Fakultet\\DIPLOMSKI\\2_semestar\\bioinformatika_1\\Bioinformatika_1\\Bioinformatika_1\\Bioinformatika-1-Projekt\\genom.fna",
    //     10);

    set<char*>::iterator it;
    // for (it = ha.begin(); it != ha.end(); ++it) {
        // cout << *it << endl;
    // }

    Table table = filter.construct_table("C:\\Users\\grga\\Documents\\Fakultet\\DIPLOMSKI\\2_semestar\\bioinformatika_1\\Bioinformatika_1\\Bioinformatika_1\\Bioinformatika-1-Projekt\\idemo.txt",
         3, 1000, false);

    // while (true) {
    //     string s;
    //     cout << "Write sequeance:" << endl;
    //     cin >> s;

    //     uint64_t returned = return_hash((unsigned char*)s.c_str());
    //     H_KEY got = filter.AddrAndFingerprint(returned);
    //     cout << table.lookup(got.h_1, got.h_2, got.fingerprint) << endl;
    // }

    filter.test_on_file("C:\\Users\\grga\\Documents\\Fakultet\\DIPLOMSKI\\2_semestar\\bioinformatika_1\\Bioinformatika_1\\Bioinformatika_1\\Bioinformatika-1-Projekt\\check.txt",
        "C:\\Users\\grga\\Documents\\Fakultet\\DIPLOMSKI\\2_semestar\\bioinformatika_1\\Bioinformatika_1\\Bioinformatika_1\\Bioinformatika-1-Projekt\\results.txt",
        table);
    table.print_table();

    filter.test_on_random("C:\\Users\\grga\\Documents\\Fakultet\\DIPLOMSKI\\2_semestar\\bioinformatika_1\\Bioinformatika_1\\Bioinformatika_1\\Bioinformatika-1-Projekt\\idemo.txt",
        "C:\\Users\\grga\\Documents\\Fakultet\\DIPLOMSKI\\2_semestar\\bioinformatika_1\\Bioinformatika_1\\Bioinformatika_1\\Bioinformatika-1-Projekt\\results.txt",
        table, 10, 3, 2);

    system("Pause");
}