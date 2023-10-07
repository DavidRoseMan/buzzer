#include "buzzer.h"
#include "variable.h"

static struct buzzer_struct xdata *buzzerlist_head = NULL;

void init_buzzer(Buzzer_type *buzzer_set, unsigned int on, unsigned int off, unsigned char priority)
{
    buzzer_set->next = NULL;
    buzzer_set->status = 0;
    buzzer_set->times = 0;
    buzzer_set->on = on;
    buzzer_set->off = off;
    buzzer_set->priority = priority;
    buzzer_set->always_on = 0;
}

unsigned char addto_buzzerlist(Buzzer_type *buzzer_add)
{
    struct buzzer_struct xdata *buzzer_temp = buzzerlist_head;
    struct buzzer_struct xdata *buzzer_temp_bak = NULL;

    if (buzzerlist_head == NULL)
    {
        buzzerlist_head = buzzer_add;
        return 0;
    }
    while (buzzer_add->priority <= buzzer_temp->priority)
    {
        if (buzzer_temp->next == NULL)
        {
            buzzer_temp->next = buzzer_add;
            return 0;
        }
        buzzer_temp_bak = buzzer_temp;
        buzzer_temp = buzzer_temp->next;
    }
    buzzer_add->next = buzzer_temp;
    if (buzzer_temp_bak == NULL)
        buzzerlist_head = buzzer_add;
    else
        buzzer_temp_bak->next = buzzer_add;
    return 0;
}

bit buzzer_running(void)
{
    struct buzzer_struct xdata *buzzer_temp = buzzerlist_head;
    unsigned char buzzer_choose_flag = 0;
    unsigned char output_flag = BUZZER_OFF;

    if (buzzer_temp == NULL)
        return BUZZER_OFF;
    while (1)
    {
        if (buzzer_temp->times || buzzer_temp->always_on)
        {
            if (buzzer_temp->status < (buzzer_temp->on + buzzer_temp->off))
            {
                buzzer_temp->status++;
            }
            else
            {
                buzzer_temp->status = 0;
                if (buzzer_temp->times)
                    buzzer_temp->times--;
            }
            if (buzzer_choose_flag == 0)
            {
                buzzer_choose_flag = 1;
                if (buzzer_temp->status <= buzzer_temp->on && (buzzer_temp->times || buzzer_temp->always_on))
                    output_flag = BUZZER_ON;
            }
        }
        if (buzzer_temp->next == NULL)
            break;
        buzzer_temp = buzzer_temp->next;
    }
    return (bit)output_flag;
}

void buzz(Buzzer_type *buzzer_work, unsigned char times)
{
    buzzer_work->status = 0;
    buzzer_work->times = times;
}

void buzz_always_on(Buzzer_type *buzzer_work, unsigned char mode)
{
    if (mode)
    {
        buzzer_work->times = 0;
        buzzer_work->always_on = 1;
    }
    else
        buzzer_work->always_on = 0;
}

unsigned char mute(void)
{
    struct buzzer_struct xdata *buzzer_temp = buzzerlist_head;

    if (buzzer_temp == NULL)
        return 0;
    while (1)
    {
        buzzer_temp->times = 0;
        buzzer_temp->status = 0;
        buzzer_temp->always_on = 0;
        if (buzzer_temp->next == NULL)
            break;
        buzzer_temp = buzzer_temp->next;
    }
    return 0;
}
