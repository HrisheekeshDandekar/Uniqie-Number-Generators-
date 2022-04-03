#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool innitialize_to_zero(FILE* fp);
bool make_new_file(FILE* fp);

int main()
{
	FILE* fp = fopen("Unique_id_current_block.bin", "rb+");

	//If file does not exist, create new one
	if (!fp) 
	{
		if (!make_new_file(fp)) { return 1; }
	}
	
	if (!innitialize_to_zero(fp)) { return 2; }

	fseek(fp, 0, SEEK_SET);

	int f_io_ret = 0;
	int check_write = 69;
	f_io_ret = fwrite(&check_write, sizeof(int), 1, fp);
	printf("[Fwrite ret] : %d\n", f_io_ret);
	fseek(fp, 0, SEEK_SET);
	f_io_ret = fread(&check_write, sizeof(int), 1, fp);
	printf("[Fwrite ret] : %d\n", f_io_ret);
	printf("\n\t[Number found in file : %d]\n", check_write);
	fclose(fp);

	return 0;
}

bool innitialize_to_zero(FILE* fp)
{

	int innitialize_to_zero = 0;

	//Setting file pointer to start of file
	fseek(fp, 0, SEEK_SET);

	int elements_written = fwrite(&innitialize_to_zero, sizeof(int), 1, fp);

	if (elements_written != 1) 
	{
		printf("[Could not write] elements_written = %d\n", elements_written);
		return false;
	}

	printf("[Innitialized to 0 successfully\n");
	return true;
}

bool make_new_file(FILE* fp)
{
	printf("[ FILE NOT FOUND ] \n");
	printf("[ CREATING A BLANK ] \n");

	fp = fopen("Unique_id_current_block.bin", "w");

	if(!fp) 
	{
		printf("[ New file COULD NOT BE CREATED ]\n");
		fclose(fp);
		return false;
	}
	return true;
}

