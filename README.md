# Bioinformatika-1-Projekt
Reducing Relocations in Cuckoo Filter

## Instalation

On **linux** just go into project directory and write in terminal:

`$<project_directory>: make`

The instalation process will start.

## First run

At the end you just need to pass parameters filename in terminal:
`$<project_directory>: main <path_to_parameters>`

There is example of properties file.

### Properties file atributes

+ `genom_path` - path to genom file
+ `results_path` - where to store results
+ `k_gram` - sequence length
+ `num_of_buckets` - number of buckets
+ `num_of_slots` - number of slots
+ `f` - number of bits for fingerprint
+ `MNK` - maximum number of rellocations
+ `reduce` - use insert reduction
+ `test_length` - approx number of test examples
+ `test_step` - random skip from 0 to this number in random testing
