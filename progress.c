#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

const char* USAGE=
		"Usage: %s <Total> <Filled look> <Not filled look> <Percentaje>\n";

int main(int argc, char** argv){
	if(argc < 5){
		printf(USAGE, argv[0]);
		return 1;
	}
	int total = atoi(argv[1]);
	double percentaje = atof(argv[4]);
	int filled = total*percentaje/100;
	static char result[500] = "";

	for(int i = 0; i < filled; ++i){
		strcat(result, argv[2]);
	}

	for(int i = filled; i < total; ++i){
		strcat(result, argv[3]);
	}

	puts(result);

	return 0;
}

