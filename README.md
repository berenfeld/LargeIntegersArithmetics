# LargeIntegersArithmetics

Try to see how complicated would it be to work with very large integers and maybe even try to break some RSA numbers.
This project is pure c++, built with G++/Clang. It has 100% unit tests coverage policy.
We implement her basic arithmetic operations and try to implement number sieve algorithms to break some RSA numbers.
Colaborations are welcome !

Ran

## Benchmarking

Sample benchmarking on gitpod machines and github runner machines

### gitpod machine, G++ 9.3.0

```
gitpod /workspace/LargeIntegersArithmetics (benchmark-with-python) $ BUILD_TYPE=Release ./benchmark.sh
12:42:02.721071 info Starting benchmark...
2022-06-02 12:42:02
Running ./build/Release/BenchmarkLargeInts
Run on (16 X 2450 MHz CPU s)
CPU Caches:
  L1 Data 32K (x8)
  L1 Instruction 32K (x8)
  L2 Unified 512K (x8)
  L3 Unified 32768K (x1)
Load Average: 10.53, 11.31, 8.54
-----------------------------------------------------------------------
Benchmark                             Time             CPU   Iterations
-----------------------------------------------------------------------
addition_mean                     21244 ns        19929 ns            5
addition_median                   20976 ns        19950 ns            5
addition_stddev                     821 ns          204 ns            5
addition_python_mean              32305 ns        31675 ns            5
addition_python_median            31662 ns        31220 ns            5
addition_python_stddev             1959 ns         1696 ns            5
substraction_mean                 18990 ns        18906 ns            5
substraction_median               19008 ns        18999 ns            5
substraction_stddev                 363 ns          283 ns            5
substraction_python_mean          26748 ns        26743 ns            5
substraction_python_median        26581 ns        26579 ns            5
substraction_python_stddev          787 ns          785 ns            5
multiplication_mean               20845 ns        20844 ns            5
multiplication_median             20997 ns        20997 ns            5
multiplication_stddev               830 ns          829 ns            5
multiplication_python_mean        29892 ns        29868 ns            5
multiplication_python_median      30167 ns        30059 ns            5
multiplication_python_stddev        933 ns          925 ns            5
power_mean                        57257 ns        57253 ns            5
power_median                      54524 ns        54522 ns            5
power_stddev                       4305 ns         4305 ns            5
power_python_mean                 20806 ns        20804 ns            5
power_python_median               20717 ns        20716 ns            5
power_python_stddev                 551 ns          551 ns            5
remainder_tree_naive_mean       2646747 ns      2646643 ns            5
remainder_tree_naive_median     2633863 ns      2633767 ns            5
remainder_tree_naive_stddev       33925 ns        33938 ns            5
remainder_tree_mean              584541 ns       584160 ns            5
remainder_tree_median            556627 ns       556614 ns            5
remainder_tree_stddev             51052 ns        50317 ns            5
product_tree_naive_mean         8125984 ns      8124567 ns            5
product_tree_naive_median       8053739 ns      8053513 ns            5
product_tree_naive_stddev        173553 ns       172926 ns            5
product_tree_mean               2080646 ns      2080539 ns            5
product_tree_median             2074957 ns      2074915 ns            5
product_tree_stddev               38178 ns        38188 ns            5
gcd_mean                        2032377 ns      1975395 ns            5
gcd_median                      2049137 ns      1925251 ns            5
gcd_stddev                        68886 ns        84992 ns            5
base_check_mean               249206555 ns    249132310 ns            5
base_check_median             208959500 ns    208960059 ns            5
base_check_stddev             197489154 ns    197366400 ns            5
12:42:54.548117 info Benchmark Done...
gitpod /workspace/LargeIntegersArithmetics (benchmark-with-python) $
```