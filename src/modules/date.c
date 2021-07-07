#include <stdio.h>
#include <time.h>

#include "config.h"
#include "modules.h"

#define BASEYEAR 1900

void
sb_date(int sig)
{
	time_t epoch = time(NULL);
	struct tm *ltime = localtime(&epoch);

	sprintf(output[MODULE_ID], "  %02d/%02d/%d", ltime->tm_mday, ltime->tm_mon + 1,
	        ltime->tm_year + BASEYEAR);
}
