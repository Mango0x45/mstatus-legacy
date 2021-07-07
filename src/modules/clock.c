#include <stdio.h>
#include <time.h>

#include "config.h"
#include "modules.h"

void
sb_clock(int sig)
{
	time_t epoch = time(NULL);
	struct tm *ltime = localtime(&epoch);

	sprintf(output[MODULE_ID], "  %02d:%02d", ltime->tm_hour, ltime->tm_min);
}
