#ifndef __PIN_LIST_H__
#define __PIN_LIST_H__

typedef struct pin_list
{
    unsigned int pin;
    int state;
    int step;
    struct pin_list *next;
} pin_list;

pin_list* create_pin(unsigned int pin);
pin_list* add_pin(pin_list **list, unsigned int pin);
pin_list* find_pin(pin_list **list, unsigned int pin);
void delete_pin(pin_list **list, unsigned int pin);
void free_pin_list(pin_list **list);


#endif // !__PIN_LIST_H__