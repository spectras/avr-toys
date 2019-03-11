timer
=====

A simple 4-digit chronometer with start/stop/reset.

Physical layout is:

- 2 inbound ports for start/stop and reset switches.
- 4 outbound ports to select the digit.
- 4 outbound ports to write the value as 0-9 integer.

Value is decoded externally into 7-segment signals using a
[CD4511](https://www.ti.com/lit/ds/symlink/cd4511b.pdf) IC.

Note
----

If you try to rebuild this, the digit selection signal must be driven by a transistor,
the atmel µC cannot source enough current by itself.
