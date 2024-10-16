#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "arm_sve.h"
#include "malloc.h"
#include <arm_sve.h>

#define LOG(...) do {printf("====="); printf(__VA_ARGS__); printf("=====\n"); } while (0)

// signatures
double *generate_random_vector_c(int size);

svfloat64_t generate_random_vector(svbool_t pg);

svfloat64_t generate_sequence_vector(svbool_t pg, double start, double step);

void print_vector(svfloat64_t vector, svbool_t pg);

void print_vector_c(double *vector, int size);

