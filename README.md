# LargeIntegersArithmetics
Try to see how complicated would it be to work with very large integers and maybe even try to break some RSA numbers

## Benchmarking

Sample benchmarking on gitpod machines and github runner machines

### Local machine, G++ 9.3.0

```
ran@RANB-LPT:~/LargeIntegersArithmetics$ ./benchmark.sh
2021-10-20 09:37:44
Running ./build/Release/BenchmarkLargeInts
Run on (16 X 1696.75 MHz CPU s)
CPU Caches:
  L1 Data 32K (x8)
  L1 Instruction 32K (x8)
  L2 Unified 512K (x8)
  L3 Unified 4096K (x1)
Load Average: 0.45, 0.16, 0.05
----------------------------------------------------------------
Benchmark                      Time             CPU   Iterations
----------------------------------------------------------------
addition_mean               4640 ns         4640 ns            5
addition_median             4591 ns         4591 ns            5
addition_stddev             83.1 ns         83.1 ns            5
substraction_mean           5295 ns         5295 ns            5
substraction_median         5303 ns         5303 ns            5
substraction_stddev         23.0 ns         23.0 ns            5
multiplication_mean         5598 ns         5598 ns            5
multiplication_median       5592 ns         5592 ns            5
multiplication_stddev       17.5 ns         17.5 ns            5
power_mean                 16574 ns        16574 ns            5
power_median               16525 ns        16524 ns            5
power_stddev                83.6 ns         83.8 ns            5
gcd_mean                  536304 ns       536306 ns            5
gcd_median                534539 ns       534540 ns            5
gcd_stddev                  8152 ns         8152 ns            5
ran@RANB-LPT:~/LargeIntegersArithmetics$
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