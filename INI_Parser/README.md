# Electrux-Codes

This is an INI parser which is completely defined in 1 header file and has a sample .c file. It can do the following:
	Defines custom INI_Parser structure which, for the end user will b same as the default FILE available in C.
	
	Functions:
		INI_Parser* ini_open(const char *_file):
			Returns a pointer of type INI_Parser opening the file which is given as parameter. Returns NULL if file is not opened.
		
		int ini_close(INI_Parser *file);
			Returns 1 if file given in parameter is successfully closed. Else returns 0.
		
		int ini_closedelete(INI_Parser *file);
			Returns 1 if the file in parameter is successfully closed (if opened) AND deleted. The file will not be accessible ever again!
		
		int ini_set(INI_Parser *file, const char *key, const char *val);
			Returns 1 if the key and value are set. If key exists, the value will be replaced. Will return 0 if the file is not opened.
			
		int ini_get(INI_Parser *file, const char *_key, char *_val);
			Returns 1 if the given _key has been found and _val has been filled with the data. Else returns 0. If it returns 0, means _val is intact as before the function call.
			
		int ini_isopen(INI_Parser *file);
			Returns 1 if the file is open, else returns 0.
		
		int ini_remove(INI_Parser *file, const char *_key);
			Returns 1 if the _key has been found and removed. Else returns 0.
			
		int ini_disp(INI_Parser *file);
			Displays all the key and values in the file in tabular form. Returns 1 if it was able to find data to display. Returns 0 if nothing was there to display.
			
		void get_delimitedstring(char *str, char *key, char *val);
			This is meant for bifercation of the key=value line. It gives key, and value seperately.
			

		
	NOTE 1: ini_close and ini_delete will handle memory deallocation by themselves.. YOU NEED NOT FREE INI_Parser MANUALLY.
	
	NOTE 2: All the above functions (except get_delimitedstring(...)) return 0 if the file is not open or the INI_Parser pointer is NULL.