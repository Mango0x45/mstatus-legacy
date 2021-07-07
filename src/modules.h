#ifndef __MODULES_H_
#define __MODULES_H_

#include <signal.h>

#define MODULE_COUNT ((int) (sizeof(modules) / sizeof(modules[0])))

#define MAX_SIGNALS SIGRTMAX - SIGRTMIN
#define MODULE_ID   (sig - SIGRTMIN)

extern char output[64][SIGBUF];

/*
 * MODULE CREATION 101
 * ===================
 *
 * Where you put your modules does not matter. For the sake of organisation I
 * like to put all my modules in `src/modules/`.
 *
 * Writing a module is quite simple. Being a C program, your modules must also
 * be written in C, however it is not very hard to call programs written in
 * other languages from C (see `man 3 system` and `man 3 popen`).
 *
 * All modules should start off as so:
 *
 *     #include "config.h"
 *     #include "modules.h"
 *
 *     void module_name(int sig)
 *     {
 *             <Your module code here>
 *     }
 *
 * The name of the function `module_name` should be the name of your module as
 * that is the name used in the configuration file. I like to prefix them with
 * `sb_`, for example, `sb_clock`. This is to avoid potential conflicts (as
 * `clock` would conflict with `clock(3)`) but it is not neccessary.
 *
 * To write to the statusbar, you need to edit the contents of the `output`
 * array at index `MODULE_ID` (this is a macro defined above). This will write
 * the data to the statusbar at your modules given location, defined by the
 * users configuration. Here is an example of a module that simply displays a
 * message:
 *
 *     #include <string.h>
 *
 *     #include "config.h"
 *     #include "modules.h"
 *
 *     void sb_hello(int sig)
 *     {
 *             (void) strcpy(output[MODULE_ID], "Hello, World!");
 *     }
 *
 * For the status bar to know about the existance of your module, you need to
 * supply a function prototype for the modules main function (in the case of the
 * example, that would be `sb_hello`) in either `config.h`, or this file. It is
 * better to put it here, as it is not something the user would really be
 * interested in configuring. You can see the prototypes for the included
 * example modules below.
 *
 *
 * QUICK NOTE
 * ==========
 * If you would like, you can compile the program with the `DEBUG` flag. This
 * will cause the statusbar to be written to STDOUT as opposed to DWM's
 * statusbar. This can be done easily by editing the `CFLAGS` variable in the
 * Makefile to include `-DDEBUG`.
 */

/* PUT YOUR MODULE PROTOTYPES HERE */
void sb_volume(int sig);
void sb_brightness(int sig);
void sb_battery(int sig);
void sb_clock(int sig);
void sb_date(int sig);

#endif /* __MODULES_H_ */
