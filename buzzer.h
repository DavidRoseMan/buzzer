#ifndef _buzzer_h
#define _buzzer_h

typedef xdata struct buzzer_struct
{
    volatile struct buzzer_struct xdata *next;
    volatile unsigned int on;
    volatile unsigned int off;
    volatile unsigned int status;
    volatile unsigned char times;
    volatile unsigned char priority;
    volatile unsigned char always_on;
} Buzzer_type;

#define BUZZER_ON 1
#define BUZZER_OFF 0

void init_buzzer(Buzzer_type *buzzer_set, unsigned int on, unsigned int off, unsigned char priority);
unsigned char addto_buzzerlist(Buzzer_type *buzzer_add);
bit buzzer_running(void);
void buzz(Buzzer_type *buzzer_work, unsigned char times);
void buzz_always_on(Buzzer_type *buzzer_work, unsigned char mode); // mode: 1-----on  0-----off

// larger priority_number means higher priority

#endif 