# 概述

```c
void init_buzzer(Buzzer_type *buzzer_set, unsigned int on, unsigned int off, unsigned char priority);
//on: the period the buzzer is on, off: the period the buzzer is off, priority: the priority of the buzzer,larger priority_number means higher priority.
unsigned char addto_buzzerlist(Buzzer_type *buzzer_add);
//add a buzzer to the buzzerlist.
bit buzzer_running(void);
//every 100us run once.
void buzz(Buzzer_type *buzzer_work, unsigned char times);
//let the buzzer buzz times.
void buzz_always_on(Buzzer_type *buzzer_work, unsigned char mode);
//let the buzzer always buzz on or buzz off. mode: 1: buzzer is on, 0: buzzer is off.
unsigned char mute(void);
//mute all the buzzers.
```
