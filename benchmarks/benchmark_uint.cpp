#include "uint.h"
#include "utils.h"
#include <benchmark/benchmark.h>

using namespace large_numbers;

void addition(benchmark::State& state) {
    for (auto _ : state) {
        UInt a = large_numbers::rand(64);
        UInt b = large_numbers::rand(64);
        UInt c = a + b;
    }
}

void multiplication(benchmark::State& state) {
    for (auto _ : state) {
        UInt a = large_numbers::rand(64);
        UInt b = large_numbers::rand(64);
        UInt c = a * b;
    }
}

void gcd(benchmark::State& state) {
    for (auto _ : state) {
        UInt a = large_numbers::rand(64);
        UInt b = large_numbers::rand(64);
        UInt c = UInt::gcd(a,b);
    }
}


BENCHMARK(addition);
BENCHMARK(multiplication);
BENCHMARK(gcd);

BENCHMARK_MAIN();