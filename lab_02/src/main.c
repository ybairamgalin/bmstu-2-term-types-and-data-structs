#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

void run_menu(FILE *file)
{
    int cont = 1;

    subscriber_t subs[MAX_SUBS];
    int sz = 0;

    {
        subscriber_t sub;
        fseek(file, 0, SEEK_SET);

        while (fread(&sub, sizeof(sub), 1, file) == 1)
        {
            sub.key = sz;
            subs[sz++] = sub;
        }
    }



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
               "0 - Завершение работы программы\n");

        if (input_string(input, MAX_INPUT_LNG) != EXIT_SUCCESS)
        {
            printf("Ошибка ввода действия\n");
            continue;
        }

        if (strcmp(input, "1") == 0)
        {
            subscriber_t sub;

            if (input_subscriber(&sub) != EXIT_SUCCESS)
            {
                printf("Ошибка ввода\n");
                continue;
            }

            fseek(file, 0, SEEK_END);

            if (fwrite(&sub, sizeof(subscriber_t), 1, file) == 1)
            {
                sub.key = sz;
                subs[sz++] = sub;
                printf("Записано успешно\n");
            }
            else
                return;
        }
        else if (strcmp(input, "2") == 0)
        {
            // DEL
        }
        else if (strcmp(input, "3") == 0)
        {
            fseek(file, 0, SEEK_SET);
            subscriber_t sub;

            while (fread(&sub, sizeof(sub), 1, file) == 1)
            {
                print_subscriber(sub);
            }
        }
        else if (strcmp(input, "4") == 0)
        {
            qsort(subs, sz, sizeof(subscriber_t), sub_last_name_cmp);

            for (int i = 0; i < sz; i++)
                print_subscriber(subs[i]);
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
        else if (strcmp(input, "0") == 0)
            cont = 0;
        else
            printf("Неверный ввод");
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
