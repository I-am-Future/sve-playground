#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "arm_sve.h"
#include "malloc.h"
#include <arm_sve.h>


// signatures
svfloat32_t generate_random_vector(svbool_t pg);

svfloat32_t generate_sequence_vector(svbool_t pg, float start, float step);

void print_vector(svfloat32_t vector, svbool_t pg);

