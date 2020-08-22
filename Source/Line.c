#include "Line.h"

struct line linefill(FILE* file, int linenum, int offset, int bytecount) {
	struct line l;

	l.bytecount = bytecount;

	sprintf(l.offset, "%06x  ", linenum * 16);

	for (int i = 0; i < bytecount; i++) {
		int val = fgetc(file);
		char temp[15] = { 0 };
		if (i < offset) {
			sprintf(temp, "   ");
		}
		else if (i == bytecount - 1) {
			sprintf(temp, "%02hhx\n", val);
		}
		else {
			sprintf(temp, "%02hhx ", val);
		}
		l.bytes[i][0] = temp[0];
		l.bytes[i][1] = temp[1];
		l.bytes[i][2] = temp[2];
	}

	return l;
}

void Writeline(struct line l) {
	char fin[56] = { 0 };

	int chars = 7 + l.bytecount * 3;
	for (int i = 0; i < chars; i++) {
		if (i < 9) {
			fin[i] = l.offset[i];
		}
		else {
			int maj = (i - 8) / 3;
			int min = (i - 8) % 3;
			fin[i] = l.bytes[maj][min];
		}
	}
	printf("%s\n", fin);
}

void linecpy(struct line* dest, struct line* src) {
	for (int i = 0; i < 8; i++) {
		dest->offset[i] = src->offset[i];
	}
	for (int i = 0; i < src->bytecount; i++) {
		for (int j = 0; j < 3; j++) {
			dest->bytes[i][j] = src->bytes[i][j];
		}
	}
	dest->bytecount = src->bytecount;
}

int linecmp(struct line* l1, struct line* l2) {
	if (l1->bytecount != l2->bytecount) {
		return 1;
	}
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 3; j++) {
			if (l1->bytes[i][j] != l2->bytes[i][j]) {
				return 1;
			}
		}
	}
	return 0;
}