
#include <signal.h>
#include <stdio.h>

static volatile int keepRunning = 1;
void sig_fpe(int sig)
{
	keepRunning = 0;
}

int main(void)
{
	if (signal(SIGINT, sig_fpe) == SIG_ERR)
	{
		puts("Le gestionnaire de signal pour SIG_FPE n'a pu etre defini.");
	}
	else
	{
		puts("Le gestionnaire de signal pour SIG_FPE a pu etre defini.");
	}
	while(keepRunning)
		;
	sleep(3);
	return 0;
}
