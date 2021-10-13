#ifndef __SUBSCRIBER_H__
#define __SUBSCRIBER_H__

#define MAX_NAME_LNG 30
#define MAX_PHONE_LNG 15

#include "subscriber_info.h"
#include "address.h"
#include <wchar.h>

typedef struct {
    char first_name[MAX_NAME_LNG];
    char last_name[MAX_NAME_LNG];
    char phone[MAX_PHONE_LNG];
    address_t address;
    status_t status;
    subscriber_info_t subscriber_info;
    int key;
} subscriber_t;

int input_subscriber(subscriber_t *sub);
void print_subscriber(const subscriber_t sub);
int sub_last_name_cmp(const void *sub_1, const void *sub_2);
int sub_first_name_cmp(const void *sub_1, const void *sub_2);
int has_birthday_soon(const subscriber_t subscriber);

#endif
