#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "arm_sve.h"
#include "malloc.h"
#include <arm_sve.h>

#define LOG(...) do {printf("====="); printf(__VA_ARGS__); printf("=====\n"); } while (0)

// signatures
svfloat32_t generate_random_vector(svbool_t pg);

svfloat32_t generate_sequence_vector(svbool_t pg, float start, float step);

void print_vector(svfloat32_t vector, svbool_t pg);

