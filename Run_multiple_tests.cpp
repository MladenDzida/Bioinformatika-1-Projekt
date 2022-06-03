#include <iostream>
#include "Cuckoo.h"
#include "Table.h"
#include <bitset>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

int main(int argc, char* argv[]) {
	const char* parameters[1];
	std::map<std::string, std::string> map_;

	for (int i = 0; i < argc; ++i) {
		if (i == 0)
			continue;

		parameters[i - 1] = argv[i];
	}

	ifstream file;
	file.open(parameters[0]);
	
	if (!file) {
		cout << "File " << parameters[0] << " does not exists." << endl;
		exit(0);
	}

	std::string name;
	std::string value;
	while (file >> name >> value) {
		map_.insert({ name, value });
	}

	
	int k_gram = stoi(map_["k_gram"]);
	int num_of_buckets = stoi(map_["num_of_buckets"]);
	int num_of_slots = stoi(map_["num_of_slots"]);
	int f = stoi(map_["f"]);
	int MNK = stoi(map_["MNK"]);
	bool reduce = (bool)stoi(map_["reduce"]);
	int test_length = stoi(map_["test_length"]);
	int test_step = stoi(map_["test_step"]);
	bool exists = (bool)stoi(map_["exists"]);

	CuckooFilter filter_1(num_of_buckets, num_of_slots, f);
	Table table_1 = filter_1.construct_table(map_["genom_path"].c_str(), k_gram, MNK, reduce);
	filter_1.test_on_random(map_["test_path"].c_str(), map_["results_path"].c_str(), table_1, test_length, k_gram, test_step, exists);

	system("Pause");
	// return 0;
}