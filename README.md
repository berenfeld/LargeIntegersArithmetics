# LargeIntegersArithmetics
Try to see how complicated would it be to work with very large integers and maybe even try to break some RSA numbers

## Benchmarking

Sample benchmarking on gitpod machines and github runner machines

### Gitpod machine, G++ 9.3.0

```
gitpod /workspace/LargeIntegersArithmetics $ ./build/Release/BenchmarkLargeInts  --benchmark_repetitions=5 --benchmark_report_aggregates_only
2021-10-17 18:03:56
Running ./build/Release/BenchmarkLargeInts
Run on (16 X 2800.21 MHz CPU s)
CPU Caches:
  L1 Data 32K (x8)
  L1 Instruction 32K (x8)
  L2 Unified 1024K (x8)
  L3 Unified 33792K (x1)
Load Average: 1.48, 1.86, 1.88
----------------------------------------------------------------
Benchmark                      Time             CPU   Iterations
----------------------------------------------------------------
addition_mean               6939 ns         6938 ns            5
addition_median             6855 ns         6854 ns            5
addition_stddev              184 ns          184 ns            5
multiplication_mean        13237 ns        13235 ns            5
multiplication_median      13262 ns        13260 ns            5
multiplication_stddev        248 ns          247 ns            5
power_mean                154908 ns       154888 ns            5
power_median              154510 ns       154490 ns            5
power_stddev                4963 ns         4956 ns            5
gcd_mean                  757904 ns       757753 ns            5
gcd_median                753313 ns       753242 ns            5
gcd_stddev                 13517 ns        13422 ns            5
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