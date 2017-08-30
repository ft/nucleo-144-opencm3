/*
 * Copyright (c) 2017 Frank Terbeck <ft@bewatermyfriend.org>, All rights
 * reserved.
 *
 * Terms for redistribution and use can be found in LICENCE.
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#ifdef WITH_SEMIHOSTING

/* Couldn't find this defined in a header. I'll blame it on the nocturnal hour
 * I am trying to find out. Here's my shortcut for tonight. */
extern void initialise_monitor_handles(void);

#endif /* WITH_SEMIHOSTING */

static void
init_gpio(void)
{
    rcc_periph_clock_enable(RCC_GPIOB);
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO0);
}

int
main(void)
{
    size_t limit;

#ifdef WITH_SEMIHOSTING
    initialise_monitor_handles();
    limit = (1ull<<13ull);
#else
    limit = (1ull<<18ull);
#endif /* WITH_SEMIHOSTING */

    init_gpio();
    for (;;) {
        gpio_toggle(GPIOB, GPIO0);
        for (size_t i = 0; i < limit; ++i) {
            __asm__(" nop");
#ifdef WITH_SEMIHOSTING
            if ((i % (1ull<<11ull)) == 0)
                printf("Hey host! i is at %u.\n", i);
#endif /* WITH_SEMIHOSTING */
        }
    }
}
