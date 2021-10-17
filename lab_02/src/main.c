#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <inttypes.h>
#include "../inc/subscriber.h"
#include "../inc/common.h"

#define MAX_INPUT_LNG 30
#define MAX_SUBS 100

#define FILE_ERR 6

void sort_keys(int *key, const subscriber_t *subs, const int sz)
{
    for (int i = 0; i < sz; i++)
        key[i] = i;

    for (int i = 0; i < sz - 1; i++)
        for (int j = 0; j < sz - i - 1; j++)
            if (sub_first_name_cmp(&subs[key[j]], &subs[key[j + 1]]) > 0)
            {
                int tmp = key[j];
                key[j] = key[j + 1];
                key[j + 1] = tmp;
            }
}

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
        print_subscriber(subs[i]);

    return EXIT_SUCCESS;
}

int qsort_print_subs(FILE *file)
{
    subscriber_t subs[MAX_SUBS];
    int sz;

    read_subs_from_file(file, subs, &sz);
    qsort(subs, sz, sizeof(subscriber_t), sub_first_name_cmp);

    for (int i = 0; i < sz; i++)
        print_subscriber(subs[i]);

    return EXIT_SUCCESS;
}



int qsort_keys_subs(FILE *file)
{
    subscriber_t subs[MAX_SUBS];
    int sz;

    read_subs_from_file(file, subs, &sz);



    return EXIT_SUCCESS;
}

int del_sub_from_file(FILE *file, subscriber_t *subs, const int cur_sz)
{
    printf("Введите id пользователя, которого необходимо удалить: ");

    return EXIT_SUCCESS;
}

void run_menu(FILE *file)
{
    int cont = 1;

    subscriber_t subs[MAX_SUBS];
    int sz = 0;
    read_subs_from_file(file, subs, &sz);

    while (cont)
    {
        char input[MAX_INPUT_LNG];
        printf("Доступные действия:\n"
               "1 - Добавить запись в таблицу\n"
               "2 - Удалить запись из таблицы\n"
               "3 - Вывести абонентов, не сортируя\n"
               "4 - Отсортировать по фамилии\n"
               "5 - Отсортировать по имени\n"
               "6 - Найти абонентов, у которых скоро день рождения\n"
               "7 - оценить эффективность сортировок\n"
               "0 - Завершение работы программы\n");

        if (input_string(input, MAX_INPUT_LNG) != EXIT_SUCCESS)
        {
            printf("Ошибка ввода действия\n");
            continue;
        }

        if (strcmp(input, "1") == 0)
        {
            if (add_sub_to_file(file, subs, sz++) != EXIT_SUCCESS)
                continue;
        }
        else if (strcmp(input, "2") == 0)
        {
            if (del_sub_from_file(file, subs, sz++) != EXIT_SUCCESS)
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
            int keys[MAX_SUBS];

            for (int i = 0; i < sz; i++)
                keys[i] = i;

            sort_keys(keys, subs, sz);

            for (int i = 0; i < sz; i++)
                printf("Для изначальной позиции %d индекс %d\n", i, (keys[i]));

            printf("\n");

            printf("Желаете вывести отсортированную по ключам таблицу? (Y/n): ");

            input_string(input, MAX_INPUT_LNG);

            if (strcmp(input, "Y") == 0 || strcmp(input, "y") == 0)
            {
                for (int i = 0; i < sz; i++)
                    print_subscriber(subs[keys[i]]);
            }

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
            printf("Оценка эффективности: \n");

            struct timeval start, end;
            int64_t elapsed_time_qsort = 0, elapsed_time_keys;

            gettimeofday(&start, NULL);
            gettimeofday(&end, NULL);

            for (int i = 0; i < 1000; i++)
            {
                read_subs_from_file(file, subs, &sz);
                gettimeofday(&start, NULL);
                qsort(subs, sz, sizeof(subscriber_t), sub_last_name_cmp);
                gettimeofday(&end, NULL);

                elapsed_time_qsort += (end.tv_sec - start.tv_sec) *
                                1000000LL + (end.tv_usec - start.tv_usec);
            }

            for (int i = 0; i < 1000; i++)
            {
                read_subs_from_file(file, subs, &sz);
                int keys[MAX_SUBS];

                for (int j = 0; i < sz; i++)
                    keys[j] = j;

                gettimeofday(&start, NULL);
                sort_keys(keys, subs, sz);
                gettimeofday(&end, NULL);

                elapsed_time_keys += (end.tv_sec - start.tv_sec) *
                                      1000000LL + (end.tv_usec - start.tv_usec);
            }

            printf("QSORT (1000 прогонов): %" PRId64 "\tmicroseconds (sec * (1e-6))\n", elapsed_time_qsort);
            printf("KEYS  (1000 прогонов): %" PRId64 "\tmicroseconds (sec * (1e-6))\n", elapsed_time_keys);
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

    FILE *file = fopen(input, "ab+");

    if (file == NULL)
        return FILE_ERR;

    printf("Файл открыт\n");
    run_menu(file);

    fclose(file);

    return EXIT_SUCCESS;
}
