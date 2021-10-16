#include "uint.h"
#include "utils.h"
#include "consts.h"
#include <benchmark/benchmark.h>

using namespace large_numbers;

void addition(benchmark::State& state) {
    for (auto _ : state) {
        UInt a = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt b = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt c = a + b;
    }
}

void multiplication(benchmark::State& state) {
    for (auto _ : state) {
        UInt a = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt b = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt c = a * b;
    }
}

void gcd(benchmark::State& state) {
    for (auto _ : state) {
        UInt a = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt b = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt c = UInt::gcd(a,b);
    }
}


BENCHMARK(addition);
BENCHMARK(multiplication);
BENCHMARK(gcd);

BENCHMARK_MAIN();