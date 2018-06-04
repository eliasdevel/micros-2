#ifndef LEDS_H
#define LEDS_H

extern void leds_config(void);

extern void leds_on(void);

extern void leds_off(void);

extern void rgb(int c);

extern void led_red_on(void);
extern void led_red_off(void);
extern void led_green_on(void);
extern void led_green_off(void);
extern void led_blue_on(void);
extern void led_blue_off(void);

#endif /* LEDS_H */

