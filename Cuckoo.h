#pragma once

class CuckooFilter
{
public:
  int number_of_buckets;
  int bucket_size;
  int fingerprint_size_in_bits;

  CuckooFilter(int number_of_buckets,int bucket_size, int fingerprint_size_in_bits);

  unsigned char *return_hash(unsigned char *to_hash);

  unsigned long transform_to_long(unsigned char* to_transform, int length);

  H_KEY split_h_key();

};

struct H_KEY
{
	unsigned long int h;
	unsigned long int key;
};