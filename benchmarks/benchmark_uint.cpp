#include "algorithms.h"
#include "consts.h"
#include "primes_base.h"
#include "spdlog/spdlog.h"
#include "uint.h"
#include "utils.h"
#include <Python.h>
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
        std::string op = "x = " + a.toString(16) + " + " + b.toString(16);
    }
}

void addition_python(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt b = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        std::string op = "x = " + a.toString(16) + " + " + b.toString(16);
        PyRun_SimpleString(op.c_str());
    }
}

void substraction(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt b = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        if (a > b) {
            UInt c = a - b;
            std::string op = "x = " + a.toString(16) + " - " + b.toString(16);
        } else {
            UInt c = b - a;
            std::string op = "x = " + b.toString(16) + " - " + a.toString(16);
        }
    }
}

void substraction_python(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt b = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        if (a > b) {
            std::string op = "x = " + a.toString(16) + " - " + b.toString(16);
            PyRun_SimpleString(op.c_str());
        } else {
            std::string op = "x = " + b.toString(16) + " - " + a.toString(16);
            PyRun_SimpleString(op.c_str());
        }
    }
}

void multiplication(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt b = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        std::string op = "x = " + a.toString(16) + " * " + b.toString(16);
        UInt c = a * b;
    }
}

void multiplication_python(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt b = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        std::string op = "x = " + a.toString(16) + " * " + b.toString(16);
        PyRun_SimpleString(op.c_str());
    }
}

void shift_left(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        auto shift_amount = ::rand() % 1024;
        std::string op = "x = " + a.toString(16) + " << " + std::to_string(shift_amount);
        UInt x = a << shift_amount;
    }
}

void shift_left_python(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        auto shift_amount = ::rand() % 1024;
        std::string op = "x = " + a.toString(16) + " << " + std::to_string(shift_amount);
        PyRun_SimpleString(op.c_str());
    }
}

void shift_right(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        auto shift_amount = ::rand() % 1024;
        std::string op = "x = " + a.toString(16) + " >> " + std::to_string(shift_amount);
        UInt x = a << shift_amount;
    }
}

void shift_right_python(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        auto shift_amount = ::rand() % 1024;
        std::string op = "x = " + a.toString(16) + " >> " + std::to_string(shift_amount);
        PyRun_SimpleString(op.c_str());
    }
}

void power(benchmark::State &state)
{
    for (auto _ : state) {
        UInt base = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        auto exp = ::rand() % 10;
        std::string op = "x = pow(" + base.toString(16) + " , " + std::to_string(exp) + ")";
        UInt c = UInt::pow(base, exp);
    }
}

void power_python(benchmark::State &state)
{
    for (auto _ : state) {
        UInt base = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        auto exp = ::rand() % 10;
        std::string op = "x = pow(" + base.toString(16) + " , " + std::to_string(exp) + ")";
        PyRun_SimpleString(op.c_str());
    }
}

void modulo(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt b = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        if (a > b) {
            std::string op = "x = " + a.toString(16) + " % " + b.toString(16);
        } else {
            std::string op = "x = " + b.toString(16) + " % " + a.toString(16);
        }
        UInt c = a % b;
    }
}

void modulo_python(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        UInt b = large_numbers::rand(LN_BENCHMARK_UINT_BITS / LN_BITS_IN_BLOCK);
        if (a > b) {
            std::string op = "x = " + a.toString(16) + " % " + b.toString(16);
            PyRun_SimpleString(op.c_str());
        } else {
            std::string op = "x = " + b.toString(16) + " % " + a.toString(16);
            PyRun_SimpleString(op.c_str());
        }
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

BENCHMARK(addition);
BENCHMARK(addition_python);
BENCHMARK(substraction);
BENCHMARK(substraction_python);
BENCHMARK(multiplication);
BENCHMARK(multiplication_python);
BENCHMARK(shift_left);
BENCHMARK(shift_left_python);
BENCHMARK(shift_right);
BENCHMARK(shift_right_python);
BENCHMARK(power);
BENCHMARK(power_python);
BENCHMARK(modulo);
BENCHMARK(modulo_python);
BENCHMARK(remainder_tree_naive);
BENCHMARK(remainder_tree);
BENCHMARK(product_tree_naive);
BENCHMARK(product_tree);
BENCHMARK(gcd);
BENCHMARK(base_check);

int main(int argc, char **argv)
{
    srand(time(nullptr));
    spdlog::set_pattern("%H:%M:%S.%f %l %v");
    spdlog::info("Starting benchmark...");
    Py_InitializeEx(0);
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) {
        return 1;
    }
    ::benchmark::RunSpecifiedBenchmarks();
    spdlog::info("Benchmark Done...");
}