#include "Table.h"
#include <vector>
#include "Cuckoo.h"
#include <iterator>
#include <ctime>
#include <cstdlib>

using namespace std;

Table::Table(int number_of_buckets, int bucket_size){
	this->number_of_buckets = number_of_buckets;
	this->bucket_size = bucket_size;
	srand(unsigned(time(0)));

	for (int i = 0; i < number_of_buckets; i++) {
		std::vector<uint32_t> tmp;
		this->hash_table.push_back(tmp);
	}
}

int Table::position(uint32_t hash) {
	return hash % this->number_of_buckets;
}

bool Table::insert(uint32_t hash) {
	int position = this->position(hash);
	
	if (this->hash_table[position].size() >= this->bucket_size) {
		return false;
	}

	hash_table[position].push_back(hash);
	return true;
}

double Table::get_fill() {
	std::vector<vector<uint32_t>>::iterator iter;

	int size = 0;

	for (int i=0; i < this->hash_table.size(); i++) {
		size += this->hash_table[i].size();
	}

	return (double)(size / (this->number_of_buckets * this->bucket_size));
}

uint32_t Table::get_random(uint32_t hash) {
	std::vector<uint32_t> vec = this->hash_table[this->position(hash)];
	int random_position = vec.size() * (rand() / (RAND_MAX + 1.0));

	uint32_t tmp = vec[random_position];
	vec.erase(vec.begin() + random_position);
}

int main() {

}