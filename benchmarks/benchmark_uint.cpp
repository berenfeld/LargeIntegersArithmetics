#include "uint.h"
#include "utils.h"
#include "consts.h"
#include "primes_base.h"
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


void searchAroundRSA100(benchmark::State& state) {
    for (auto _ : state) {
        UInt rsa_100(
        "1522605027922533360535618378132637429718068114961380688657908494580122963258952897654000350692006139");
        UInt z = rsa_100.sqrt() += 1;
        PrimesBase base(128);
        for (int i = 0; i < 1000; ++i) {
            UInt candidate = UInt::power_modulo(z, 2, rsa_100);
            if (base.contains(candidate)) {
                z += 1;
                continue;
            }
            z += 1;
        }
    }
}


BENCHMARK(addition);
BENCHMARK(multiplication);
BENCHMARK(searchAroundRSA100);
BENCHMARK(gcd);

BENCHMARK_MAIN();