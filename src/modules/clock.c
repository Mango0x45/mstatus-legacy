#include <stdio.h>
#include <time.h>

#include "config.h"
#include "modules.h"

void sb_example_clock(int sig)
{
	time_t epoch;
	struct tm *ltime;

	(void) time(&epoch);
	ltime = localtime(&epoch);

	(void) sprintf(output[MODULE_ID], " %02d:%02d", ltime->tm_hour,
	               ltime->tm_min);
}
