#pragma once
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

struct Arguments {
	char* Inputfile;
	bool NoDupLines;
	bool Infile;
	bool failed;
	int rangemin, rangemax;
};

struct Arguments ArgsProc(int argc, char** argv);

void ClearArgs(struct Arguments* args);

int* GetRange(char* range);