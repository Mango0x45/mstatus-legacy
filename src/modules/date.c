#include <stdio.h>
#include <time.h>

#include "config.h"
#include "modules.h"

#define BASEYEAR 1900

void sb_example_date(int sig)
{
	time_t epoch;
	struct tm *ltime;

	(void) time(&epoch);
	ltime = localtime(&epoch);

	(void) sprintf(output[MODULE_ID], " %02d/%02d/%d", ltime->tm_mday,
	               ltime->tm_mon + 1, ltime->tm_year + BASEYEAR);
}
