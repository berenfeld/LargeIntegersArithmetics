# LargeIntegersArithmetics

Try to see how complicated would it be to work with very large integers and maybe even try to break some RSA numbers.
This project is pure c++, built with G++/Clang. It has 100% unit tests coverage policy.
We implement her basic arithmetic operations and try to implement number sieve algorithms to break some RSA numbers.
Colaborations are welcome !

Ran

## Benchmarking

Sample benchmarking on gitpod machines and github runner machines

### Local machine, G++ 9.3.0

```
ran@RANB-LPT:~/LargeIntegersArithmetics$ ./benchmark.sh
2021-10-20 11:45:52
Running ./build/Release/BenchmarkLargeInts
Run on (16 X 1696.75 MHz CPU s)
CPU Caches:
  L1 Data 32K (x8)
  L1 Instruction 32K (x8)
  L2 Unified 512K (x8)
  L3 Unified 4096K (x1)
Load Average: 0.46, 0.39, 0.28
----------------------------------------------------------------
Benchmark                      Time             CPU   Iterations
----------------------------------------------------------------
addition_mean               4536 ns         4536 ns            5
addition_median             4543 ns         4543 ns            5
addition_stddev             11.5 ns         11.5 ns            5
substraction_mean           5312 ns         5312 ns            5
substraction_median         5284 ns         5284 ns            5
substraction_stddev          101 ns          101 ns            5
multiplication_mean         5658 ns         5658 ns            5
multiplication_median       5595 ns         5595 ns            5
multiplication_stddev        120 ns          120 ns            5
power_mean                 16004 ns        16004 ns            5
power_median               15998 ns        15998 ns            5
power_stddev                58.0 ns         58.0 ns            5
gcd_mean                  533340 ns       533334 ns            5
gcd_median                534040 ns       534011 ns            5
gcd_stddev                  8501 ns         8501 ns            5
base_check_mean         28639644 ns     28639539 ns            5
base_check_median       28506205 ns     28506203 ns            5
base_check_stddev        4252339 ns      4252180 ns            5
```

### Gitpod machine, Clang 13.0.0

```
gitpod /workspace/LargeIntegersArithmetics $ ./build/Release/BenchmarkLargeInts  --benchmark_repetitions=5 --benchmark_report_aggregates_only
2021-10-17 18:07:29
Running ./build/Release/BenchmarkLargeInts
Run on (16 X 2800.21 MHz CPU s)
CPU Caches:
  L1 Data 32K (x8)
  L1 Instruction 32K (x8)
  L2 Unified 1024K (x8)
  L3 Unified 33792K (x1)
Load Average: 0.99, 1.49, 1.73
----------------------------------------------------------------
Benchmark                      Time             CPU   Iterations
----------------------------------------------------------------
addition_mean               5246 ns         5246 ns            5
addition_median             5223 ns         5223 ns            5
addition_stddev             70.1 ns         70.2 ns            5
multiplication_mean        10369 ns        10368 ns            5
multiplication_median      10316 ns        10314 ns            5
multiplication_stddev        188 ns          188 ns            5
power_mean                123122 ns       123108 ns            5
power_median              121955 ns       121937 ns            5
power_stddev                3719 ns         3718 ns            5
gcd_mean                  601103 ns       601023 ns            5
gcd_median                590274 ns       590213 ns            5
gcd_stddev                 21783 ns        21769 ns            5
gitpod /workspace/LargeIntegersArithmetics $ clang++ --version
Ubuntu clang version 13.0.0-++20210309052636+4e1c487004a2-1~exp1~20210309163348.339
Target: x86_64-pc-linux-gnu
Thread model: posix
InstalledDir: /usr/bin
```

### Github machine, G++ 9.3.0

```
2021-10-17 18:11:32
Running ./build/Release/BenchmarkLargeInts
Run on (2 X 2294.69 MHz CPU s)
CPU Caches:
  L1 Data 32K (x2)
  L1 Instruction 32K (x2)
  L2 Unified 256K (x2)
  L3 Unified 51200K (x1)
Load Average: 0.47, 0.21, 0.09
----------------------------------------------------------------
Benchmark                      Time             CPU   Iterations
----------------------------------------------------------------
addition_mean               7636 ns         7635 ns            5
addition_median             7526 ns         7525 ns            5
addition_stddev              223 ns          223 ns            5
multiplication_mean        14875 ns        14874 ns            5
multiplication_median      14537 ns        14536 ns            5
multiplication_stddev       1314 ns         1314 ns            5
power_mean                165498 ns       165484 ns            5
power_median              166213 ns       166190 ns            5
power_stddev                5034 ns         5034 ns            5
gcd_mean                  803144 ns       803069 ns            5
gcd_median                803845 ns       803657 ns            5
gcd_stddev                  7793 ns         7812 ns            5
```