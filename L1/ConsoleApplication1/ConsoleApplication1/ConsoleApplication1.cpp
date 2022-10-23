#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

/*int main()  // 1, 2, 3 задания
{
    srand(time(NULL));

    int size = 10;
    printf_s("Vvedite razmer massiva: ");
    scanf_s("%d", &size);

    int* arr = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100;
        printf_s("%d ", arr[i]);
    }

    int min = arr[0], max = arr[0];

    for (int i = 0; i < size; i++)
    {
        if (arr[i] < min)
            min = arr[i];
        if (arr[i] > max)
            max = arr[i];
    }

    printf_s("\nmin: %d, max: %d", min, max);
    int r = max - min;
    printf_s("\nraznica: %d", r);

    free(arr);
}*/

/*int main()  // 4 задание
{
    srand(time(NULL));
    int x = 5, y = 5;
    cout << "Vvedite razmeri 2-mernogo massiva: ";
    cin >> x;
    cin >> y;

    int* res = (int*)malloc(x * sizeof(int));

    int** arr = (int**)malloc(x * sizeof(int));
    for (int i = 0; i < x; i++)
    {
        arr[i] = (int*)malloc(y * sizeof(int));
    }

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            arr[i][j] = rand() % 100;
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }

    for (int i = 0; i < x; i++)
    {
        res[i] = 0;
        for (int j = 0; j < y; j++)
        {
            res[i] = res[i] + arr[i][j];
        }
        cout << "\n" << res[i] << " ";
    }

    for (int i = 0; i < x; i++)
    {
        free(arr[i]);
    }
    free(arr);
}*/

int main()  // 5 задание
{
    struct stud {
        char name[20];
        char surname[20];
        int age;
    };
    stud studs[5];

    stud search;

    for (int i = 0; i < 5; i++)
    {
        cout << "Vvedite name, surname, age:";
        cin >> studs[i].name;
        cin >> studs[i].surname;
        cin >> studs[i].age;
    }

    cout << "Vvedite name, surname, age:";
    cin >> search.name >> search.surname >> search.age;
    for (int i = 0; i < 5; i++)
    {
        if (strcmp(studs[i].name, search.name) == 0)
            if (strcmp(studs[i].surname, search.surname) == 0)
                if (studs[i].age == search.age)
                    cout << studs[i].name << " " << studs[i].surname << " " << studs[i].age;
    }
}