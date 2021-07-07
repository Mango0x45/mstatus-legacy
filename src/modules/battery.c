#include <stdio.h>
#include <string.h>

#include "config.h"
#include "modules.h"

#define STATBUF 32

void
sb_battery(int sig)
{
	char icon[16] = {0}, status[STATBUF];
	int battery;
	FILE *fp = fopen("/sys/class/power_supply/BAT0/status", "r");

	if (!fp) {
		strcat(output[MODULE_ID], "ERROR");
		return;
	}
	fscanf(fp, "%s", status);
	fclose(fp);

	fp = fopen("/sys/class/power_supply/BAT0/capacity", "r");
	if (!fp) {
		strcat(output[MODULE_ID], "ERROR");
		return;
	}
	fscanf(fp, "%d", &battery);
	fclose(fp);

	if (strcmp(status, "Discharging") != 0)
		strcat(icon, "");
	else if (battery == 100)
		strcat(icon, "");
	else if (battery >= 90)
		strcat(icon, "");
	else if (battery >= 80)
		strcat(icon, "");
	else if (battery >= 70)
		strcat(icon, "");
	else if (battery >= 60)
		strcat(icon, "");
	else if (battery >= 50)
		strcat(icon, "");
	else if (battery >= 40)
		strcat(icon, "");
	else if (battery >= 30)
		strcat(icon, "");
	else if (battery >= 20)
		strcat(icon, "");
	else if (battery >= 10)
		strcat(icon, "");
	else
		strcat(icon, "");

	sprintf(output[MODULE_ID], "%s %02d%%", icon, battery);
}
