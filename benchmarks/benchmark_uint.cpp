#include "algorithms.h"
#include "consts.h"
#include "primes_base.h"
#include "spdlog/spdlog.h"
#include "uint.h"
#include "utils.h"
#include <benchmark/benchmark.h>
#include <iostream>
#include <spdlog/spdlog.h>

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

void product_tree_naive(benchmark::State &state)
{
    large_numbers::PrimesBase base(1000);
    std::vector<UInt> values = base.getPrimesAsUInts();
    for (auto _ : state) {
        UInt result = 1;
        for (UInt value : values) {
            result *= value;
        }
    }
}

void product_tree(benchmark::State &state)
{
    large_numbers::PrimesBase base(1000);
    std::vector<UInt> values = base.getPrimesAsUInts();
    for (auto _ : state) {
        UInt result = large_numbers::product(values);
    }
}

void remainder_tree_naive(benchmark::State &state)
{
    UInt rsa_100(
        "1522605027922533360535618378132637429718068114961380688657908494580122963258952897654000350692006139");
    large_numbers::PrimesBase base(1000);
    std::vector<UInt> primes = {base.getPrime(999), base.getPrime(998), base.getPrime(997), base.getPrime(996)};
    UInt q, r;
    std::vector<UInt> result;
    for (auto _ : state) {
        for (const UInt &prime : primes) {
            UInt::div_mod(rsa_100, prime, q, r);
            result.push_back(r);
        }
    }
}

void remainder_tree(benchmark::State &state)
{
    UInt rsa_100(
        "1522605027922533360535618378132637429718068114961380688657908494580122963258952897654000350692006139");
    large_numbers::PrimesBase base(1000);
    std::vector<UInt> primes = {base.getPrime(999), base.getPrime(998), base.getPrime(997), base.getPrime(996)};
    std::vector<UInt> result;
    for (auto _ : state) {
        result = remainderTree(rsa_100, primes);
    }
}

BENCHMARK(remainder_tree_naive);
BENCHMARK(remainder_tree);
BENCHMARK(product_tree_naive);
BENCHMARK(product_tree);
BENCHMARK(addition);
BENCHMARK(substraction);
BENCHMARK(multiplication);
BENCHMARK(power);
BENCHMARK(gcd);
BENCHMARK(base_check);

int main(int argc, char **argv)
{
    spdlog::set_pattern("%H:%M:%S.%f %l %v");
    spdlog::info("Starting benchmark...");
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) {
        return 1;
    }
    ::benchmark::RunSpecifiedBenchmarks();
    spdlog::info("Benchmark Done...");
}