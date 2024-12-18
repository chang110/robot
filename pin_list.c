 #include <stddef.h>
 #include <malloc.h>
#include "pin_list.h"
#include "config.h"

pin_list* add_pin(pin_list **list, unsigned int pin)
{
    pin_list *new_pin = create_pin(pin);
    if (new_pin == NULL) return NULL;
    new_pin->next = *list;
    *list = new_pin;
    return new_pin;
}

pin_list* create_pin(unsigned int pin)
{
    pin_list *new_pin = malloc(sizeof(pin_list));
    if (new_pin == NULL) return NULL;
    new_pin->state = 1;
    new_pin->pin = pin;
    new_pin->step = FREQ_UNCOUNTER;
    new_pin->next = NULL;
    return new_pin;
}

void delete_pin(pin_list **list, unsigned int pin)
{
    pin_list* temp = *list; // 临时指针指向头节点
    pin_list* prev = NULL; // 前一个节点的指针，初始化为NULL

    // 如果头节点就是要删除的节点
    if (temp != NULL && temp->pin == pin) {
        *list = temp->next; // 更新头节点为下一个节点
        free(temp); // 释放要删除的节点
        return;
    }

    // 查找要删除的节点，并记录前一个节点
    while (temp != NULL && temp->pin != pin) {
        prev = temp;
        temp = temp->next;
    }

    // 如果没有找到要删除的节点
    if (temp == NULL) {
        return;
    }

    // 修改前一个节点的指针以跳过要删除的节点
    prev->next = temp->next;

    // 释放要删除的节点
    free(temp);
}

void free_pin_list(pin_list **list)
{
    pin_list *temp = *list;
    while (temp != NULL) {
        pin_list *next = temp->next;
        free(temp);
        temp = next;
    }
}

pin_list* find_pin(pin_list **list, unsigned int pin)
{
    pin_list *temp = *list;
    while (temp != NULL) {
        if (temp->pin == pin) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}