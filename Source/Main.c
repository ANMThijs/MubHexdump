#include "Dump.h"

int main(int argc, char** argv) {
	struct Arguments args = ArgsProc(argc, argv);
	if (args.failed == true) {
		ClearArgs(&args);
		return -1;
	}

	DumpFile(&args);

	/*Cleanup and return*/
	ClearArgs(&args);

	return 0;
}