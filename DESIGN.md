hardware debounce
+ simplest - no code
- loads of extra parts (per button (x14, not incl. power): 2 resistors + 1 capacitor + (possibly) 1 diode)
- not flexible (fixed RC time constants)
- possibly loads of input delay - test it

pio debounce
+ fancy
+ simple software interface (once pio is configured)
+ no parts
+ no delay
- can pio handle debouncing that many inputs at once?
- i'd have to learn pio

irq debounce
+ would work for sure
+ no delay
- complex code
- messy?

gpio_set_input_hysteresis_enabled?
