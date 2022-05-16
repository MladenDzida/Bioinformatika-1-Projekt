#pragma once

class CuckooFilter
{
public:
  int number_of_buckets;
  int bucket_size;
  int fingerprint_size_in_bits;

  CuckooFilter(int number_of_buckets,int bucket_size, int fingerprint_size_in_bits);

  int return_hash();

};