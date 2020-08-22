#include "Dump.h"

int DumpFile(struct Arguments* args) {
	FILE* infile = fopen(args->Inputfile, "rb");
	if (infile == NULL) {
		printf("Failed to open file\n");
		return -1;
	}

	/*Get the filesize by seeking the end and getting the position*/
	fseek(infile, 0L, SEEK_END);
	int filelen = ftell(infile);
	rewind(infile);

	fseek(infile, args->rangemin, SEEK_SET);

	int linecount = 0, lineoff = 0, lastlinelen = 0;
	if ((args->rangemax == -1) || (args->rangemax == filelen)) {
		args->rangemax = filelen;

		lastlinelen = filelen % 16;
		linecount = (filelen - lastlinelen) / 16;
		if (lastlinelen > 0) {
			linecount++;
		}
	}
	else {
		int minoff = args->rangemin % 16;
		int maxoff = args->rangemax % 16;
		
		linecount = (args->rangemax - args->rangemin) / 16;
		lineoff = args->rangemin / 16;
		if ((minoff > 0) || (maxoff > 0)) {
			linecount++;
		} 
	}

	struct line l;
	if (args->NoDupLines == true) {
		int prevlinestar = 0;

		struct line prevline;

		int offset = args->rangemin % 16;
		for (int i = 0; i < linecount; i++) {
			if (i == linecount - 1) {
				l = linefill(infile, i + lineoff, offset, lastlinelen);
			}
			else {
				l = linefill(infile, i + lineoff, offset, 16);
			}

			if (linecmp(&prevline, &l) == 0) {
				if (prevlinestar == 0) {
					printf("*\n");
				}
				prevlinestar = 1;
			}
			else {
				Writeline(l);
				linecpy(&prevline, &l);
			}
			offset = 0;
		}
	}
	else {
		int offset = args->rangemin % 16;
		for (int i = 0; i < linecount; i++) {
			if (i == linecount - 1) {
				l = linefill(infile, i + lineoff, offset, lastlinelen);
			}
			else {
				l = linefill(infile, i + lineoff, offset, 16);
			}
			Writeline(l);
			offset = 0;
		}
	}
	fclose(infile);
}