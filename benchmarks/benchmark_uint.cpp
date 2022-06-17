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

std::vector<UInt> inputs_vec_large;
std::vector<int> exps_vec;
size_t inputs_vec_idx;
size_t exps_idx;

const UInt &get_next_random_input()
{
    inputs_vec_idx = (inputs_vec_idx + 1) % inputs_vec_large.size();
    return inputs_vec_large[inputs_vec_idx];
}

int get_next_random_exp()
{
    exps_idx = (exps_idx + 1) % exps_vec.size();
    return exps_vec[exps_idx];
}

void addition(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = get_next_random_input();
        UInt b = get_next_random_input();
        UInt c = a + b;
        std::string op = "x = " + a.toString(16) + " + " + b.toString(16);
    }
}

void addition_python(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = get_next_random_input();
        UInt b = get_next_random_input();
        std::string op = "x = " + a.toString(16) + " + " + b.toString(16);
        PyRun_SimpleString(op.c_str());
    }
}

void substraction(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = get_next_random_input();
        UInt b = get_next_random_input();
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
        UInt a = get_next_random_input();
        UInt b = get_next_random_input();
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
        UInt a = get_next_random_input();
        UInt b = get_next_random_input();
        std::string op = "x = " + a.toString(16) + " * " + b.toString(16);
        UInt c = a * b;
    }
}

void multiplication_python(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = get_next_random_input();
        UInt b = get_next_random_input();
        std::string op = "x = " + a.toString(16) + " * " + b.toString(16);
        PyRun_SimpleString(op.c_str());
    }
}

void power(benchmark::State &state)
{
    for (auto _ : state) {
        UInt base = get_next_random_input();
        int exp = get_next_random_exp();
        std::string op = "x = pow(" + base.toString(16) + " , " + std::to_string(exp) + ")";
        UInt c = UInt::pow(base, exp);
    }
}

void power_python(benchmark::State &state)
{
    for (auto _ : state) {
        UInt base = get_next_random_input();
        int exp = get_next_random_exp();
        std::string op = "x = pow(" + base.toString(16) + " , " + std::to_string(exp) + ")";
        PyRun_SimpleString(op.c_str());
    }
}

void gcd(benchmark::State &state)
{
    for (auto _ : state) {
        UInt a = get_next_random_input();
        UInt b = get_next_random_input();
        UInt c = UInt::gcd(a, b);
    }
}

void base_check(benchmark::State &state)
{
    large_numbers::PrimesBase base(512);
    UInt reminder;
    for (auto _ : state) {
        UInt a = get_next_random_input();
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
BENCHMARK(power);
BENCHMARK(power_python);
BENCHMARK(remainder_tree_naive);
BENCHMARK(remainder_tree);
BENCHMARK(product_tree_naive);
BENCHMARK(product_tree);
BENCHMARK(gcd);
BENCHMARK(base_check);

int main(int argc, char **argv)
{
    spdlog::set_pattern("%H:%M:%S.%f %l %v");
    spdlog::info("Starting benchmark...");
    Py_Initialize();
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) {
        return 1;
    }

    static const size_t INPUTS = 100;

    for (size_t idx = 0; idx < INPUTS; ++idx) {
        inputs_vec_large.push_back(large_numbers::rand(32));
        exps_vec.push_back(::rand() % 10);
    }

    ::benchmark::RunSpecifiedBenchmarks();
    spdlog::info("Benchmark Done...");
}