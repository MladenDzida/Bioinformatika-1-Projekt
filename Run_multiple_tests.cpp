#include <iostream>
#include "Cuckoo.h"
#include "Table.h"
#include <bitset>

using namespace std;

int main10() {
	// num of buckets
	// bucket size
	// fingerptint size in bits

	const char* genom_path = "C:\\Users\\grga\\Documents\\Fakultet\\DIPLOMSKI\\2_semestar\\bioinformatika_1\\Bioinformatika_1\\Bioinformatika_1\\Bioinformatika-1-Projekt\\genom.fna";
	const char* results_path = "C:\\Users\\grga\\Documents\\Fakultet\\DIPLOMSKI\\2_semestar\\bioinformatika_1\\Bioinformatika_1\\Bioinformatika_1\\Bioinformatika-1-Projekt\\results.txt";

	// We choose 10000 x 100 number of positions beacuse good fillment rate is 50%.

	// TEST BY FINGERPRINT BITS
	int k_gram = 10;

	int num_of_buckets = 10000;
	int num_of_slots = 1000;
	int f = 18;

	int MNK = 1000;
	bool reduce = false;

	int test_length = 10000;
	int test_step = 1000;

	CuckooFilter filter_1(num_of_buckets, num_of_slots, f);
	Table table_1 = filter_1.construct_table(genom_path, k_gram, MNK, reduce);
	filter_1.test_on_random(genom_path, results_path, table_1, test_length, k_gram, test_step, true);

	system("Pause");
	return 1;
}