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

const char *argv0;
char output[64][SIGBUF];

/* Write the statusbar */
static void
write_status(void)
{
	char buffer[STATUSBUF] = {0};
	strcat(buffer, output[0]);
	for (int i = 1, len = MODULE_COUNT; i < len; i++)
		sprintf(buffer, "%s" MODULE_DELIMETER "%s", buffer, output[i]);

#if RIGHTPAD
	strcat(buffer, " ");
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
static void
main_loop(void)
{
	/*
	 * When the program is first launched we don't want to wait for a
	 * signal to be sent.
	 */
	sleep(1U);
	for (int i = 0, len = MODULE_COUNT; i < len; i++)
		(*modules[i])(SIGRTMIN + i);
	write_status();

	while (true) {
		sleep(UINT_MAX); /* Sleeps until the next signal */
		write_status();
	}
}

/* Initialize the signal handlers */
static void
setup_signals(void)
{
	struct sigaction sa = {.sa_flags = 0};
	for (int i = 0; i < MODULE_COUNT; i++) {
		sa.sa_handler = modules[i];

		if (sigaction(SIGRTMIN + i, &sa, NULL) == -1) {
			perror(argv0);
			exit(EXIT_FAILURE);
		}
	}
}

int
main(int argc, char **argv)
{
	(void) argc;
	argv0 = argv[0];

	if (MODULE_COUNT > MAX_SIGNALS) {
		fprintf(stderr, "%s: You cannot have more than %d modules loaded at once\n", argv0,
		        MAX_SIGNALS);
		exit(EXIT_FAILURE);
	}

	if (daemon(0, 0) == -1) {
		perror(argv0);
		exit(EXIT_FAILURE);
	}

	setup_signals();
	main_loop();
	return EXIT_SUCCESS;
}
