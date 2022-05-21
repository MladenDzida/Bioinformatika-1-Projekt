#include <iostream>
#include "Cuckoo.h"
#include "Table.h"
#include <bitset>

using namespace std;

int main() {
	unsigned char s_1[] = "Marko jede sniclu";
	unsigned char s_2[] = "Marko jede snitu";

	cout << "Kreirajmo dva tekstualna niza:" << endl;
	cout << "\t" << s_1 << endl;
	cout << "\t" << s_2 << endl;

	system("pause");

	uint64_t hash_1 = return_hash(s_1);
	uint64_t hash_2 = return_hash(s_2);

	bitset<64> b_1(hash_1);
	bitset<64> b_2(hash_2);

	cout << endl;
	cout << "Pogledajmo koji su 64-bitni SHA1 hashevi za dva zadana niza:" << endl;
	cout << "\t" << hash_1 << endl;
	cout << "\t\tBinarni oblik:" << b_1 << endl;
	cout << "\t" << hash_2 << endl;
	cout << "\t\tBinarni oblik:" << b_2 << endl;

	system("pause");

	CuckooFilter filter(4, 4, 5);
	H_KEY info_1 = filter.AddrAndFingerprint(hash_1);
	H_KEY info_2 = filter.AddrAndFingerprint(hash_2);

	cout << endl;
	cout << "Definirajmo da ce fingerprint biti velicine 5, te da ce u tablici biti 4 bucketa s 2 pretinca." << endl;

	system("pause");

	Table table1(4, 2, 4, false);

	cout << endl;
	cout << "Pogledajmo adrese h_1 i h_2, kao i fingerprint od dva primjera:" << endl;
	cout << "\th_1: " << info_1.h_1 << ", h_2: " << info_1.h_2 << ", fingerprint: " << info_1.fingerprint << ", position_1: "
		<< info_1.h_1 % filter.number_of_buckets
		<< ", position_2: "
		<< info_1.h_2 % filter.number_of_buckets
		<< endl;
	cout << "\th_1: " << info_2.h_1 << ", h_2: " << info_2.h_2 << ", fingerprint: " << info_2.fingerprint << ", position_1: "
		<< info_2.h_1 % filter.number_of_buckets
		<< ", position_2: "
		<< info_2.h_2 % filter.number_of_buckets
		<< endl;

	system("pause");

	table1.insert(info_1.h_1, info_1.h_2, info_1.fingerprint);
	table1.insert(info_2.h_1, info_2.h_2, info_2.fingerprint);

	cout << endl;
	cout << "Pogledajmo kako izgleda tablica nakon ubacivanja:" << endl;
	table1.print_table();

	system("pause");

	cout << endl;
	cout << "Popunjenost tablice je: " << table1.get_fill() << endl;

	system("pause");

	unsigned char s_3[] = "Idemo.";

	cout << endl;
	cout << "Mozemo vidjeti postoji li odredeni niz u podacima: " << s_3 << endl;

	system("pause");

	uint64_t hash_3 = return_hash(s_3);
	H_KEY info_3 = filter.AddrAndFingerprint(hash_3);

	cout << endl;
	cout << "Pogledajmo adrese h_1 i h_2, kao i fingerprint NOVOG primjera:" << endl;
	cout << "\th_1: " << info_3.h_1 << ", h_2: " << info_3.h_2 << ", fingerprint: " << info_3.fingerprint << ", position_1: "
		<< info_3.h_1 % filter.number_of_buckets
		<< ", position_2: "
		<< info_3.h_2 % filter.number_of_buckets
		<< endl;

	system("pause");

	cout << "\tUnutra je: " << table1.lookup(info_3.h_1, info_3.h_2, info_3.fingerprint, false) << endl;

	system("pause");
	// return 2;
}