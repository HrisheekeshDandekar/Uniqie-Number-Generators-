/*     ---=== A Program to create a binary file which stores all possible 10 digit numbers
 *
 * Sudo Code : 
 *     1] Open binary file called available_numbers
 *     (undecided) 2] Fill it with numbers in sequence prepended by A (available)
 */
#include <stdio.h>
#include <stdbool.h>

bool write_numbers(FILE* fp, long start, long end);
bool read_print_check_bin (FILE* fp, long start, long end);
int write_and_check();
void read();

int main()
{
	//read();
	write_and_check();
	return 0;
}

int write_and_check()
{
	//Open File
	FILE* fp = fopen("available_numbers.bin", "wb"); 	
	if (!fp) 
	{
		printf("\nFailed to open file\n");
		return 1;
	}

	//Fill file with numbers 
	if (!write_numbers(fp, 0, 9999999999)) 
	{
		fclose(fp);	
		printf("\n\t Failed to write\n");
		return 1;
	}
	fclose(fp);

	//Verify written data
	fp = fopen("available_numbers.bin", "rb");
	if (!read_print_check_bin(fp, 0, 9999999999))
	{
		return 1;
	}

	//closing file
	fclose(fp);	
	return 0;
}

bool write_numbers(FILE* fp, long start, long end)
{
	for (;start <= end; start++)
	{
		if (fwrite(&start, sizeof(long), 1, fp) != 1) {
			return false;
		}
	}
	return true;	
}

bool read_print_check_bin (FILE* fp, long start, long end)
{
	for (;start <= end; start++)
	{
		long check = 4;
		long read_check = fread(&check, sizeof(long), 1, fp);
		if (read_check != 1)
		{
			printf("\n\t Fread failed, Returned : %ld\n", read_check);
			//return false;
		}
		if (check != start) {
			printf("\n\tAnomoly found\n Expected : %ld\n Found : %ld", start, check);
			return false;
		}
		//printf("num [%ld]\n", check);
	}
	printf("\n\t [ DATA VERIFIED ]\n\n");
	return true;	
}

void read()
{
	FILE* fp = fopen("available_numbers.bin", "rb");
	long expected_number = 0;
	long retrived_number = 0;
	while (fread(&retrived_number, sizeof(long), 1, fp))
	{
		if (expected_number != retrived_number)
		{
			printf("\n\t [ ANOMOLY AT %ld ] found : %ld\n\n", expected_number, retrived_number);
		}
		expected_number++;
		retrived_number++;
	}
	printf("\n\t [DataVerification success]\n\n");
	fclose(fp);
}

