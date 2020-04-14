#include "randie.h"

#define CMD_COUNT 6

int check_id()
{
	uid_t id = getuid();

	if (id && printf("[Invalid permissions] : Be L33T and run as root or leave.\n"))
		return (1);
	return (0);
}

// Pool of commands
char *base_cmd[CMD_COUNT] = {"gcc " , "echo ", "mkdir ", "touch ", "rm ", "cat "};

char *add_arg(char *bcmd, int arg_len)
{
	int al = rand() % arg_len + 1;
	char *fcmd;
	
	int t_size = strlen(bcmd) + al + 1;
	printf("size=%d, arglen=%d\n", t_size, arg_len);
	if (!(fcmd = malloc(t_size)))
		return (NULL);
	int i = 0;
	while (i < t_size)
		fcmd[i++] = 0;
	strcat(fcmd, bcmd);
	i = strlen(bcmd);
	while (i < t_size)
		fcmd[i++] = (rand() % 95) + 32;
		// Only take chars between ascii 32(' ') and 126('~')
	fcmd[i] = 0;
	return (fcmd);
}

void random_cmd(int arg_len)
{
	time_t	t = time(0);
	char	*bcmd;
	srand(t*42);
	bcmd = base_cmd[rand() % CMD_COUNT];
	bcmd = add_arg(bcmd, arg_len);
	system(bcmd);
}

#define DEF_ARG_LEN 10

int main(int argc, char **argv)
{
	int arg_len;

	if (check_id())
		return (1);
	if (argc == 2 && !(arg_len = atoi(argv[1])) && printf("[Invalid argument]: %s num\n", argv[0]))
		return (1);
	else if (argc != 2)
		arg_len = DEF_ARG_LEN;
	random_cmd(arg_len);
}
