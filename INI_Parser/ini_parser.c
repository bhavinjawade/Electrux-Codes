#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ini_parser.h"

int main(int argc, char const *argv[])
{
	INI_Parser *newfile = ini_open("my.txt");
	ini_set(newfile, "testkey", "testval");
	//ini_get(newfile, "testkey", val);
	ini_disp(newfile);
	ini_remove(newfile, "testkey");
	//ini_close(newfile);
	ini_closedelete(newfile);
	return 0;
}
