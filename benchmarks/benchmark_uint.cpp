#include "consts.h"
#include "primes_base.h"
#include "uint.h"
#include "utils.h"
#include <benchmark/benchmark.h>

using namespace large_numbers;

void addition(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt b = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt c = a + b;
    }
}

void substraction(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt b = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt c = a > b ? a - b : b - a;
    }
}

void multiplication(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt b = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt c = a * b;
    }
}

void power(benchmark::State &state)
{
    for (auto _ : state) {
        UInt base = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        auto exp = ::rand() % 10;
        UInt c = UInt::pow(base, exp);
    }
}

void gcd(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt b = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt c = UInt::gcd(a, b);
    }
}

void base_check(benchmark::State &state)
{
    large_numbers::PrimesBase base(512);
    UInt reminder;
    for (auto _ : state) {
        UInt a = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        if (base.contains(a, reminder)) {
            a = a + 1;
        }
    }
}

BENCHMARK(addition);
BENCHMARK(substraction);
BENCHMARK(multiplication);
BENCHMARK(power);
BENCHMARK(gcd);
BENCHMARK(base_check);

BENCHMARK_MAIN();