#ifndef __SUBSCRIBER_INFO__
#define __SUBSCRIBER_INFO__

#define MAX_COMPANY_INFO_LNG 30

typedef enum {
    personal,
    company
} status_t;

typedef struct {
    int day;
    int month;
    int year;
} date_t;

typedef struct {
    char name[MAX_COMPANY_INFO_LNG];
    char position[MAX_COMPANY_INFO_LNG];
} company_info_t;

typedef struct {
    date_t birth_date;
} personal_info_t;

typedef union {
    personal_info_t person_info;
    company_info_t company_info;
} subscriber_info_t;

#endif