#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "modules.h"

void
sb_volume(int sig)
{
	if (system("pamixer --get-mute >/dev/null") == 0) {
		sprintf(output[MODULE_ID], "ﱝ  Muted");
		return;
	}

	FILE *fp = popen("pamixer --get-volume", "r");
	if (!fp) {
		sprintf(output[MODULE_ID], "ERROR");
		return;
	}

	int volume;
	fscanf(fp, "%d", &volume);
	pclose(fp);

	char icon[16] = {0};
	if (volume > 50)
		strcat(icon, "墳");
	else if (volume > 0)
		strcat(icon, "奔");
	else
		strcat(icon, "奄");

	sprintf(output[MODULE_ID], "%s %02d%%", icon, volume);
}
