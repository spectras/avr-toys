hello
=====

A simple hello world program writing text on LCD1602 display.

It uses a 74HC595 shift register to reduce data lines count.

Physical layout is:

- 3 outbound ports to shift register (data, strobe and output enable).
- 1 outbound port to display's RS bit.
