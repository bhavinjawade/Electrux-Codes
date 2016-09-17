typedef struct MyINI_Parser {
	char name[400];
	FILE *file;
} INI_Parser;

INI_Parser* ini_open(const char *_file);
int ini_close(INI_Parser *file);
int ini_closedelete(INI_Parser *file);
int ini_set(INI_Parser *file, const char *key, const char *val);
int ini_get(INI_Parser *file, const char *_key, char *_val);
int ini_isopen(INI_Parser *file);
int ini_remove(INI_Parser *file, const char *_key);
int ini_disp(INI_Parser *file);
void get_delimitedstring(char *str, char *key, char *val);

INI_Parser* ini_open(const char *_file)
{
	INI_Parser *file = (INI_Parser *)malloc(sizeof(INI_Parser));
	strcpy(file->name, _file);
	file->file = fopen(_file, "a+");
	if(file->file == NULL)
		free(file);
	file = NULL;
	return file;
}

int ini_close(INI_Parser *file)
{
	int ret = (fclose(file->file) == 0) ? 1 : 0;
	file->file = NULL;
	free(file);
	return ret;
}

int ini_closedelete(INI_Parser *file)
{
	int ret;
	fclose(file->file);
	ret = remove(file->name);
	file->file = NULL;
	free(file);
	return (ret == 0) ? 1 : 0; //Return true if remove is a success
}

int ini_set(INI_Parser *file, const char *_key, const char *_val)
{
	if(!ini_isopen(file)) return 0;
	
	char line[200], key[200][90], val[200][90];
	int i = 0, j, found = 0;
	while(fgets(line, sizeof(line), file->file) != NULL)
	{
		get_delimitedstring(line, key[i], val[i]);
		if(strcmp(key[i], _key) == 0)
		{
			strcpy(val[i], _val);
			found = 1;
		}
		++i;
	}
	if(found == 1)
	{
		freopen(file->name, "w", file->file);
		for(j = 0; j < i; ++j)
		{
			fprintf(file->file, "%s=%s\n", key[j], val[j]);
		}
		freopen(file->name, "a+", file->file);
		rewind(file->file);
		return 1;
	}
	else
	{
		fseek(file->file, 0, SEEK_END);
		fprintf(file->file, "%s=%s\n", _key, _val);
		rewind(file->file);
		return 1;
	}
	return 0;
}

int ini_get(INI_Parser *file, const char *_key, char *_val)
{
	if(!ini_isopen(file)) return 0;

	char line[200], key[90], val[90];
	int found = 0;
	while(fgets(line, sizeof(line), file->file) != NULL)
	{
		get_delimitedstring(line, key, val);
		if(strcmp(key, _key) == 0)
		{
			strcpy(_val, val);
			found = 1;
			break;
		}
	}
	rewind(file->file);
	if(found == 1)
	{
		return 1;
	}
	return 0;
}

int ini_isopen(INI_Parser *file)
{
	return (file == NULL || file->file == NULL) ? 0 : 1;
}

int ini_remove(INI_Parser *file, const char *_key)
{
	if(!ini_isopen(file)) return 0;

	char line[200], key[200][90], val[200][90];
	int i = 0, j, found = 0;
	while(fgets(line, sizeof(line), file->file) != NULL)
	{
		get_delimitedstring(line, key[i], val[i]);
		if(strcmp(key[i], _key) == 0)
		{
			--i;
			found = 1;
		}
		++i;
	}
	if(found == 1)
	{
		freopen(file->name, "w", file->file);
		for(j = 0; j < i; ++j)
		{
			fprintf(file->file, "%s=%s\n", key[j], val[j]);
		}
		freopen(file->name, "a+", file->file);
		rewind(file->file);
		return 1;
	}
	rewind(file->file);
	return 0;
}

int ini_disp(INI_Parser *file)
{
	if(!ini_isopen(file)) return 0;

	char line[200], key[90], val[90];
	int count = 0;
	while(fgets(line, sizeof(line), file->file) != NULL)
	{
		get_delimitedstring(line, key, val);
		printf("Key: %s\t\tValue: %s\n", key, val);
		count++;
	}
	rewind(file->file);
	if(count == 0)
	{
		return 0;
	}
	return 1;
}

void get_delimitedstring(char *str, char *key, char *val)
{
	int i, j = 0, k = 0, len = strlen(str), key_done = 0;
	for(i = 0; i <= len; ++i)
	{
		if(str[i] == '=')
		{
			key_done = 1;
		}
		else if(key_done == 0)
		{
			key[j] = str[i];
			j++;
		}
		else if(str[i] != '\n')
		{
			val[k] = str[i];
			k++;
		}
	}
	key[j] = '\0';
	val[k] = '\0';
}
