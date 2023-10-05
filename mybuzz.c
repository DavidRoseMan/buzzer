#include "buzzer.h"

Buzzer_type buzzer_key;
Buzzer_type buzzer_workend;
Buzzer_type buzzer_error;

void mybuzzer_init(void)
{
    init_buzzer(&buzzer_key, 2000, 1000, 10);
    init_buzzer(&buzzer_workend, 2500, 3500, 0xfe);
    init_buzzer(&buzzer_error, 2000, 1000, 0xff);
    addto_buzzerlist(&buzzer_key);
    addto_buzzerlist(&buzzer_workend);
    addto_buzzerlist(&buzzer_error);
}

void my_buzzkey(void)
{
    buzz(&buzzer_key, 1);
}

void my_buzzworkend(void)
{
    buzz(&buzzer_workend, 3);
}

void my_buzzerror(unsigned char mode)
{
    buzz_always_on(&buzzer_error, mode);
}
