#ifndef __CONFIG_H_
#define __CONFIG_H_

/* 1 to add a space to the right of the bar. 0 for no pad. */
#define RIGHTPAD 1

/* The delimeter between modules */
#define MODULE_DELIMETER " | "

#define SIGBUF    256 /* This is how many bytes any given module can hold */
#define STATUSBUF 256 /* This is how many bytes the statusbar can hold */

#include "modules.h"

/*
 * THIS IS THE FILE WHERE ALL THE MODULE CONFIGURATION GOES.
 * ==========================================================
 *
 * Below is the "modules" array. In this array you should put the names of all
 * the modules you would like loaded in your statusbar, in the order in which
 * you would like to have them loaded.
 *
 * Since this statusbar is completely signal based, you will need to find ways
 * to signal to each module that it needs to update. An easy way to do so is as
 * follows:
 *
 *     $ kill -XX mstatus
 *
 * In the above command, you must replace "XX" with the correct signal number.
 * The signal number you need to send is the modules position in the statusbar
 * plus 33. For example, if your statusbar contains a clock, battery health
 * meter, and date in that order, then to signal to the clock to update you need
 * to send the signal 34. This is because the clock is the first item in the
 * status bar, and 33 + 1 = 34. Likewise, to signal to the battery meter and
 * date modules, you need to send the signals 35 and 36 respectively.
 *
 * If you would like to send a signal on a set cycle (such as once a minute for
 * a clock), you could look into using cronjobs. To detect something such as a
 * charger being plugged in, udev might be of use to you (see `man 3 udev`).
 *
 * For more information on how to create your own modules, check out the comment
 * in `src/modules.h`.
 *
 *
 * IMPORTANT
 * =========
 * After ANY change to the program, configuration, or modules, you MUST
 * recompile the program. You can do so as follows:
 *
 *     # make clean install
 */

static void (*modules[])(int) = {sb_example_clock, sb_example_date};

#endif /* __CONFIG_H_ */
