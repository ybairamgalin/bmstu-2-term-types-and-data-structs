#ifndef __ADDRESS__
#define __ADDRESS__

#define MAX_ADDRESS_FIELD_LNG 30

typedef struct {
    char city[MAX_ADDRESS_FIELD_LNG];
    char street[MAX_ADDRESS_FIELD_LNG];
    char house[MAX_ADDRESS_FIELD_LNG];
    char apartment[MAX_ADDRESS_FIELD_LNG];
} address_t;

int input_address(address_t *address);
void print_address(const address_t address);

#endif
