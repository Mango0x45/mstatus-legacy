#include <limits.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <X11/Xlib.h>

#include "config.h"
#include "modules.h"

char output[64][SIGBUF];

/* Write the statusbar */
static void write_status(void)
{
	char buffer[STATUSBUF] = {0};
	(void) strcat(buffer, output[0]);
	for (int i = 1, len = MODULE_COUNT; i < len; i++)
		(void) sprintf(buffer, "%s" MODULE_DELIMETER "%s", buffer,
		               output[i]);

#if RIGHTPAD
	(void) strcat(buffer, " ");
#endif

#ifdef DEBUG
	puts(buffer);
#else
	/* Xlib magic to set the DWM status */
	Display *dpy = XOpenDisplay(NULL);
	int screen = DefaultScreen(dpy);
	Window root = RootWindow(dpy, screen);
	(void) XStoreName(dpy, root, buffer);
	(void) XCloseDisplay(dpy);
#endif
}

/* Wait for a signal and loop */
static void main_loop(void)
{
	/*
	 * When the program is first launched we don't want to wait for a
	 * signal to be sent.
	 */
	for (int i = 0, len = MODULE_COUNT; i < len; i++)
		(*modules[i])(SIGRTMIN + i);
	write_status();

	while (true) {
		(void) sleep(UINT_MAX); /* Sleeps until the next signal */
		write_status();
	}
}

/* Initialize the signal handlers */
static void setup_signals(void)
{
	struct sigaction sa = {.sa_flags = 0};
	for (int i = 0; i < MODULE_COUNT; i++) {
		sa.sa_handler = modules[i];

		if (sigaction(SIGRTMIN + i, &sa, NULL) == -1) {
			perror("sigaction");
			exit(EXIT_FAILURE);
		}
	}
}

int main(void)
{
	if (MODULE_COUNT > MAX_SIGNALS) {
		(void) fprintf(stderr,
		               "mstatus: You cannot have more than %d "
		               "modules loaded at once\n",
		               MAX_SIGNALS);
		exit(EXIT_FAILURE);
	}

	setup_signals();
	main_loop();
	return EXIT_SUCCESS;
}
