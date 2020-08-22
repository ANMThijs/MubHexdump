#pragma once
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct line {
	unsigned char offset[8];
	unsigned char bytes[16][3];
	int bytecount;
};

struct line linefill(FILE* file, int linenum, int offset, int bytecount);

void Writeline(struct line l);

void linecpy(struct line* dest, struct line* src);

int linecmp(struct line* l1, struct line* l2);