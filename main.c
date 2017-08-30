/*
 * Copyright (c) 2017 Frank Terbeck <ft@bewatermyfriend.org>, All rights
 * reserved.
 *
 * Terms for redistribution and use can be found in LICENCE.
 */

#include <stddef.h>
#include <stdint.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

static void
init_gpio(void)
{
    rcc_periph_clock_enable(RCC_GPIOB);
    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO0);
}

int
main(void)
{
    init_gpio();
    for (;;) {
        gpio_toggle(GPIOB, GPIO0);
        for (size_t i = 0; i < (1ull<<18ull); ++i)
            __asm__(" nop");
    }
}
