#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <inttypes.h>
#include "../inc/subscriber.h"
#include "../inc/common.h"

#define MAX_INPUT_LNG 30
#define MAX_SUBS 1200

#define FILE_ERR 6

void read_subs_from_file(FILE *file, subscriber_t *subs, int *sz)
{
    *sz = 0;

    subscriber_t sub;
    fseek(file, 0, SEEK_SET);

    while (fread(&sub, sizeof(sub), 1, file) == 1)
    {
        sub.key = *sz;
        subs[(*sz)++] = sub;
    }
}

int add_sub_to_file(FILE *file, subscriber_t *subs, const int cur_sz)
{
    subscriber_t sub;

    if (input_subscriber(&sub) != EXIT_SUCCESS)
    {
        printf("Ошибка ввода\n");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);

    if (fwrite(&sub, sizeof(subscriber_t), 1, file) == 1)
    {
        sub.key = cur_sz;
        subs[cur_sz] = sub;
        printf("Записано успешно\n");
    }
    else
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int print_subs_from_file(FILE *file)
{
    subscriber_t subs[MAX_SUBS];
    int sz;

    read_subs_from_file(file, subs, &sz);

    for (int i = 0; i < sz; i++)
    {
        printf("Абонент %d\n", i);
        print_subscriber(subs[i]);
    }

    return EXIT_SUCCESS;
}

int qsort_print_subs(FILE *file)
{
    subscriber_t subs[MAX_SUBS];
    int sz;

    read_subs_from_file(file, subs, &sz);
    qsort(subs, sz, sizeof(subscriber_t), sub_last_name_cmp);

    for (int i = 0; i < sz; i++)
        print_subscriber(subs[i]);

    return EXIT_SUCCESS;
}

int qsort_keys_subs(FILE *file)
{
    subscriber_t subs[MAX_SUBS];
    int sz;

    read_subs_from_file(file, subs, &sz);

    int keys[MAX_SUBS];

    for (int i = 0; i < sz; i++)
        keys[i] = i;

    qsort_keys(subs, keys, sz, sizeof(subscriber_t), sub_first_name_cmp);

    for (int i = 0; i < sz; i++)
        printf("%d. Id %d\n", i, keys[i]);

    printf("\n");

    char input[MAX_INPUT_LNG];
    printf("Желаете вывести отсортированную по ключам таблицу? (Y/n): ");

    input_string(input, MAX_INPUT_LNG);

    if (strcmp(input, "Y") == 0 || strcmp(input, "y") == 0)
    {
        for (int i = 0; i < sz; i++)
            print_subscriber(subs[keys[i]]);
    }

    return EXIT_SUCCESS;
}

int del_sub_from_file(FILE *file)
{
    subscriber_t subs[MAX_SUBS];
    int sz;

    read_subs_from_file(file, subs, &sz);

    printf("Введите фамилию пользователя, которого необходимо удалить: ");
    int to_del = -1;

    char surname[128];

    if (input_string(surname, 128) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    for (int i = 0; i < sz; i++)
    {
        if (strcmp(surname, subs[i].last_name) == 0)
        {
            to_del = i;
            break;
        }
    }

    if (to_del == -1)
    {
        printf("Пользователь не найден\n");
        return EXIT_FAILURE;
    }

    for (int i = to_del; i < sz - 1; i++)
        subs[i] = subs[i + 1];

    fseek(file, 0, SEEK_SET);

    if (fwrite(subs, sizeof(subscriber_t), sz - 1, file) != sz - 1)
        return EXIT_FAILURE;

    fseek(file, 0, SEEK_SET);
    ftruncate(fileno(file), sizeof(subscriber_t) * (sz - 1));

    printf("Удалено успешно\n");

    return EXIT_SUCCESS;
}

int64_t get_sort_time(void *arr, size_t count, size_t sz,
    comparator cmp,
    void (*sort)(void *, size_t, size_t size, comparator),
    const int runs)
{
    int64_t elapsed_time = 0;
    struct timeval start, end;

    gettimeofday(&start, NULL);
    gettimeofday(&end, NULL);

    for (int i = 0; i < runs; i++)
    {
        gettimeofday(&start, NULL);
        sort(arr, count, sz, cmp);
        gettimeofday(&end, NULL);
        elapsed_time += (end.tv_sec - start.tv_sec) *
                        1000000LL + (end.tv_usec - start.tv_usec);
    }

    return elapsed_time;
}

int64_t get_keys_sort_time(void *arr, size_t count, size_t sz,
    comparator cmp,
    void (*sort)(void *, int*, size_t, size_t, comparator),
    const int runs)
{
    int64_t elapsed_time = 0;
    struct timeval start, end;

    gettimeofday(&start, NULL);
    gettimeofday(&end, NULL);

    for (int i = 0; i < runs; i++)
    {
        int keys[MAX_SUBS];

        for (int j = 0; j < MAX_SUBS; j++)
            keys[j] = j;

        gettimeofday(&start, NULL);
        sort(arr, keys, count, sz, cmp);
        gettimeofday(&end, NULL);
        elapsed_time += (end.tv_sec - start.tv_sec) *
                        1000000LL + (end.tv_usec - start.tv_usec);
    }

    return elapsed_time;
}

int measure_sort_by_file(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
        return EXIT_FAILURE;

    subscriber_t subs[MAX_SUBS];
    int sz;

    read_subs_from_file(file, subs, &sz);

    int64_t elapsed_time_qsort  = get_sort_time(subs, sz, sizeof(subscriber_t), sub_last_name_cmp, qsort, 1000);
    int64_t elapsed_time_bubble = get_sort_time(subs, sz, sizeof(subscriber_t), sub_last_name_cmp, my_sort, 1000);

    int64_t elapsed_time_keys_qsort =  get_keys_sort_time(subs, sz, sizeof(subscriber_t), sub_last_name_cmp, qsort_keys, 1000);
    int64_t elapsed_time_keys_bubble = get_keys_sort_time(subs, sz, sizeof(subscriber_t), sub_last_name_cmp, my_sort_key, 1000);

    printf("%-10d|%15lld\t|%15lld\t|%15lld\t|%15lld\n", sz, elapsed_time_keys_qsort, elapsed_time_bubble,
           elapsed_time_qsort, elapsed_time_keys_bubble);

    fclose(file);

    return EXIT_SUCCESS;
}

int measure_sort_time()
{
    printf("Оценка эффективности (1000 интераций): \n");

    printf("  COUNT   |%15s\t|%15s\t|%15s\t|%15s\n", "QSORT", "BUBBLE", "QSORT KEY", "BUBBLE KEY");

    measure_sort_by_file("../lab_02/data/test_45");
    measure_sort_by_file("../lab_02/data/test_100");
    measure_sort_by_file("../lab_02/data/test_500");
    measure_sort_by_file("../lab_02/data/test_1000");

    return EXIT_SUCCESS;
}

void print_menu()
{
    printf("Доступные действия:\n"
           "1 - Добавить запись в таблицу\n"
           "2 - Удалить запись из таблицы\n"
           "3 - Вывести абонентов, не сортируя\n"
           "4 - Отсортировать по фамилии\n"
           "5 - Отсортировать по имени\n"
           "6 - Найти абонентов, у которых скоро день рождения\n"
           "7 - оценить эффективность сортировок\n"
           "0 - Завершение работы программы\n");
}

void run_menu(FILE *file)
{
    int cont = 1;

    subscriber_t subs[MAX_SUBS];
    int sz = 0;
    read_subs_from_file(file, subs, &sz);
    char input[MAX_INPUT_LNG];
    int menu_needed = 1;

    while (cont)
    {
        if (menu_needed)
            print_menu();

        int error;

        if ((error = input_string(input, MAX_INPUT_LNG)) != EXIT_SUCCESS)
        {
            if (error == 10)
            {
                printf("Введите действие: ");
                menu_needed = 0;
            }

            if (strcmp(input, "") == 0)
                continue;

            printf("Ошибка ввода действия\n");
            continue;
        }

        menu_needed = 1;

        if (strcmp(input, "1") == 0)
        {
            if (add_sub_to_file(file, subs, sz++) != EXIT_SUCCESS)
                continue;
        }
        else if (strcmp(input, "2") == 0)
        {
            if (del_sub_from_file(file) != EXIT_SUCCESS)
                continue;
        }
        else if (strcmp(input, "3") == 0)
        {
            if (print_subs_from_file(file) != EXIT_SUCCESS)
                continue;
        }
        else if (strcmp(input, "4") == 0)
        {
            if (qsort_print_subs(file) != EXIT_SUCCESS)
                continue;
        }
        else if (strcmp(input, "5") == 0)
        {
            if (qsort_keys_subs(file) != EXIT_SUCCESS)
                continue;
        }
        else if (strcmp(input, "6") == 0)
        {
            printf("Вот абоненты, у которых скоро день рождения:\n\n");

            for (int i = 0; i < sz; i++)
            {
                if (has_birthday_soon(subs[i]))
                    print_subscriber(subs[i]);
            }
        }
        else if (strcmp(input, "7") == 0)
        {
            measure_sort_time();
        }
        else if (strcmp(input, "0") == 0)
            cont = 0;
        else
            printf("Неверный ввод\n");
    }
}

int main(void)
{
    setbuf(stdout, NULL);
    int error;

    char input[MAX_INPUT_LNG];

    printf("Для создания нового файла или открытия существующего введите имя файла: ");

    if ((error = input_string(input, MAX_INPUT_LNG)) != EXIT_SUCCESS)
    {
        printf("Ошибка ввода имени файла\n");
        return error;
    }

    FILE *file = fopen(input, "r+b");

    if (file == NULL)
    {
        file = fopen(input, "w+b");

        if (file == NULL)
            return FILE_ERR;
    }

    printf("Файл открыт\n");
    run_menu(file);

    fclose(file);

    return EXIT_SUCCESS;
}
