#include <stdio.h>
#include <string.h>

#include "config.h"
#include "modules.h"

#define BRIGHTNESS_RATIO 1200

void
sb_brightness(int sig)
{
	FILE *fp = fopen("/sys/class/backlight/intel_backlight/brightness", "r");
	if (!fp) {
		strcat(output[MODULE_ID], "ERROR");
		return;
	}
	int brightness;
	fscanf(fp, "%d", &brightness);
	fclose(fp);

	brightness /= BRIGHTNESS_RATIO;

	sprintf(output[MODULE_ID], "ﯦ  %02d%%", brightness);
}
