#include "../headers/main.h"

/**
 * _atoi - convert str to int
 * @s: string to convert
 *
 * Return: integer value
 */
int _atoi(char *s)
{
	int j, sign;
	unsigned int n;

	j = 0;
	sign = 1;
	n = 0;
	/* up to null end of string */
	while (s[j] != '\0')
	{
		if (s[j] >= '0' && s[j] <= '9')
		{
			n = (n * 10) + (s[j] - '0');
		}
		if (n != 0 && !(s[j] >= '0' && s[j] <= '9'))
		{
			break;
		}
		/* if number is negative */
		if (s[j] == '-')
		{
			sign = sign * -1;
		}
		j++;
	}
	return (sign * n);
}

/**
 * _strdup - duplicate string
 * @str: string parameter
 *
 * Return: the duplicated string
 **/
char *_strdup(char *str)
{
	char *dup;
	int i = 0, strlength = 0;

	if (str == NULL)
		return (NULL);
	/* find length of string */
	strlength = _length(str);
	/* alloc mem for the string */
	dup = malloc(sizeof(char) * (strlength + 1));
	if (dup == NULL)
	{
		free(dup);
		return (NULL);
	}
	/* coppy each character */
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/**
 * _length - finds length of a string
 * @str: string value
 *
 * Return: the length of a string
 **/
int _length(char *str)
{
	int i = 0;

	/** null end of string **/
	while (str[i] != '\0')
		i++;
	return (i);
}

/**
 * get_altitude - read altitude from tex file
 * @argv: args
 *
 * Return: altitue found
 **/
int **get_altitude(char **argv)
{
	int **altitude;
	int fd, i, j;
	char buf[1024];
	char **rows, ***cols;

	/* open the file */
	fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		fprintf(stderr, "Error in opening a file");
		return (NULL);
	}
	/* read the file */
	read(fd, buf, 1023);
	close(fd);
	/* alloc mem for the map */
	altitude = malloc(sizeof(int *) * map_x);
	if (altitude == NULL)
		return (NULL);
	for (i = 0; i < map_x; i++)
		altitude[i] = malloc(sizeof(int) * map_y);
	rows = str_split(buf, "\n");
	/* allocate memory for the row */
	cols = malloc(sizeof(char **) * map_x);
	/* split the row per space */
	for (i = 0; rows[i]; i++)
		cols[i] = str_split(rows[i], " ");
	/* convert the character  into number type */
	for (i = 0; i < map_x; i++)
	{
		for (j = 0; j < map_y; j++)
			altitude[i][j] = _atoi(cols[i][j]);
	}
	free_tokens(rows);
	free_cols(cols);
	return (altitude);
}
/**
 * str_split - split a string
 * @str: the given string
 * @del: the delimeter
 *
 * Return: array of a string
 **/
char **str_split(char *str, char *del)
{
	char **tokens;
	char *token, *str2;
	int i = 0;
	int tokens_size = 2;

	/* allocate memory for the tokens */
	tokens = malloc(sizeof(char *) * (tokens_size + 1));
	if (tokens == NULL)
		return (NULL);
	/* duplicate the given string */
	str2 = _strdup(str);
	/* split the string based on the delimeter character */
	token = strtok(str2, del);
	tokens_size++;
	/* upto the end of the string */
	while (token)
	{
		tokens[i] = _strdup(token);
		tokens = realloc(tokens, sizeof(char *) * tokens_size);
		token = strtok(NULL, del);
		i++;
		tokens_size++;
	}
	/* add terminate 0/character of the string */
	tokens[i] = "";
	if (token)
		free(token);
	if (str2)
		free(str2);
	return (tokens);
}

