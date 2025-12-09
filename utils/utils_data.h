#ifndef UTILS_DATA_H
#define UTILS_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "utils_data.h"

int dataParaDias(const struct tm data);

int periodosConflitam(struct tm i1, struct tm f1, struct tm i2, struct tm f2);

int calculaDiferencaDias(struct tm inicio, struct tm fim);
#endif //UTILS_DATA_H