#include "shell.h"

/**
 * str_compare - function that compare two strings with a limit
 * @str1: Pointer - First strings
 * @str2: Ponter - Second strings
 * @n: Interger
 * Return: 0 on Success -1 if it fails
 */

char str_compare(char *str1, char *str2, int n)
{
	int i = 0;

	while (i < n)
	{
		if (str1[i] == str2[i])
			i++;
		else if (str1[i] != str2[i])
			return (-1);
	}
	return (0);
}

/**
 * str_lenght - Lenght of the string
 * @string: Pointer to the string
 * Return: lenght of the string
 */

int str_lenght(char *string)
{
	int i = 0;

	while (*string != '\0')
	{
		i++;
		string++;
	}
	return (i);
}

/**
 * str_concat - Function that concatenate to strings str2 to str1
 * @str1: String
 * @str2: String
 * Return: THe string complete
 */

char *str_concat(char *str1, char *str2)
{
	char *cstring; /*String concatenada*/
	int lenght1 = 0;/*Largo string 1*/
	int lenght2 = 0;/*Largo string 2*/
	int i = 0;

	if (str1 == NULL)
		str1 = "";
	if (str2 == NULL)
		str2 = "";
	 /*largos de las cadenas que entraron*/
	while (str1[lenght1] != '\0')
		lenght1++;
	while (str2[lenght2] != '\0')
		lenght2++;
	/*Reservamos memoria para concatenar ambas cadenas*/
	cstring = malloc(sizeof(char) * (lenght1 + lenght2 + 1));
	if (cstring == NULL)
	{
		free(cstring);
		return (NULL);
	}

	while (*str1)
	{
		cstring[i] = *str1;
		i++;
		str1++;
	}
	while (*str2)
	{
		cstring[i] = *str2;
		i++;
		str2++;
	}
	cstring[i] = '\0';
	return (cstring);
}
