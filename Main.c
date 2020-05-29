#pragma warning(disable: 4996)

#include <stdio.h>

int main(int argc, char** argv) {
	/*Check if there is a inputfile specified*/
	if (argc == 1) {
		printf("No input file detected");
		return 0;
	}
	/*Store the Filename of the inputfile in a buffer*/
	const char* InputFile = argv[1];

	/*Open the input file and check if it opens correctly.*/
	FILE* binfile = fopen(InputFile, "rb");
	if (binfile == NULL) {
		printf("Failed to open file");
		return 0;
	}

	/*Get the filesize by seeking the end and getting the position*/
	fseek(binfile, 0L, SEEK_END);
	int filelen = ftell(binfile);
	rewind(binfile);

	int tenth = filelen / 10;

	/*If there is a Outputfile specified, write the hexadecimal values to it*/
	if (argc == 3) {
		const char* OutputFile = argv[2];
		FILE* OutFile = fopen(OutputFile, "w");
		
		fprintf(OutFile, "000000  ");
		for (int i = 0; i < filelen; i++) {
			if (i % tenth == 0) {
				int x = i / tenth;
				printf("%i%%\n", x * 10);
			}
			fprintf(OutFile, "%02hhx ", fgetc(binfile));
			if (((i + 1) % 16 == 0) && (i != 0)) {
				fprintf(OutFile, "\n%06x  ", i + 1);
			}
		}

		fclose(OutFile);
	}
	/*If there is no Outputfile specified, write the hexadecimal values to the cmd*/
	else {
		printf("000000  ");
		for (int i = 0; i < filelen; i++) {
			printf("%02hhx ", fgetc(binfile));
			if (((i + 1) % 16 == 0) && (i != 0)) {
				printf("\n%06x  ", i + 1);
			}
		}
	}

	/*Close the input file and return*/
	fclose(binfile);

	return 0;
}