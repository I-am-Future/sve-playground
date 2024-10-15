
#include <stdio.h>
#include <arm_sve.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

int main() {
    srand(time(NULL));  

    svbool_t pg = svptrue_b32();  

    svfloat32_t random_vector = generate_random_vector(pg);
    print_vector(random_vector, pg);

    svfloat32_t sequence_vector = generate_sequence_vector(pg, 1.0f, 1.0f);
    print_vector(sequence_vector, pg);

    return 0;
}