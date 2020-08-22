#include "Args.h"

struct Arguments ArgsProc(int argc, char** argv) {
	struct Arguments args;

	args.NoDupLines = false;
	args.Infile = false;
	args.failed = false;

	args.rangemin = 0;
	args.rangemax = -1;

	//First argument is processname, so we can skip that one
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-i") == 0) {
			int len = strlen(argv[i + 1]);
			args.Inputfile = malloc(len + 1);
			strcpy(args.Inputfile, argv[i + 1]);
			i++;
			args.Infile = true;
		}
		else if (strcmp(argv[i], "-NoDupLines") == 0) {
			args.NoDupLines = true;
		}
		else if (strcmp(argv[i], "-r") == 0) {
			int* values = GetRange(argv[i + 1]);
			
			args.rangemin = values[0];
			args.rangemax = values[1];

			free(values);
		}
	}

	if (args.Infile == false) {
		printf("No inputfile detected\n");
		args.failed = true;
		return args;
	}

	return args;
}

void ClearArgs(struct Arguments* args) {
	if (args->Infile == true) {
		free(args->Inputfile);
	}
}

int* GetRange(char* range) {
	int* ret = malloc(2 * sizeof(int));
	ret[0] = 0;
	ret[1] = 0;

	int len = strlen(range);
	char* stripe = strrchr(range, '-');

	int minlen = len - strlen(stripe);
	int maxlen = len - minlen - 1;

	for (int i = 0; i < minlen; i++) {
		//Range[i] is a number
		if ((range[i] >= 0x30) && (range[i] <= 0x39)) {
			ret[0] += (range[i] - '0') * (int)pow(0x10, (double)minlen - i - 1);
		}
		//Range[i] is a capital number
		else if ((range[i] >= 0x41) && (range[i] <= 0x46)) {
			ret[0] += (range[i] - 0x37) * (int)pow(0x10, (double)minlen - i - 1);
		}
		//Range[i] is a lowercase number
		else if ((range[i] >= 0x61) && (range[i] <= 0x66)) {
			ret[0] += (range[i] - 0x57) * (int)pow(0x10, (double)minlen - i - 1);
		}
	}
	for (int i = 0; i < maxlen; i++) {
		if ((range[minlen + i + 1] >= 0x30) && (range[minlen + i + 1] <= 0x39)) {
			ret[1] += (range[minlen + i + 1] - '0') * (int)pow(0x10, (double)maxlen - i - 1);
		}
		else if ((range[minlen + i + 1] >= 0x41) && (range[minlen + i + 1] <= 0x46)) {
			ret[1] += (range[minlen + i + 1] - 0x37) * (int)pow(0x10, (double)maxlen - i - 1);
		}
		else if ((range[minlen + i + 1] >= 0x61) && (range[minlen + i + 1] <= 0x66)) {
			ret[1] += (range[minlen + i + 1] - 0x57) * (int)pow(0x10, (double)maxlen - i - 1);
		}
	}
	return ret;
}