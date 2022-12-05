#include <iostream>
#include <queue>

using namespace std;

const int N = 5;
bool Used[N];

void BFS(int s, int** M)
{
    queue <int> Q;
    Q.push(s);
    Used[s] = true;
    while (!Q.empty())
    {
        s = Q.front();
        Q.pop();
        cout << s + 1 << endl;
        for (int i = 0; i < N; i++)
        {
            if (M[s][i] == 1 and Used[i] == false) {
                Q.push(i);
                Used[i] = true;
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    int** M = (int**)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        M[i] = (int*)malloc(N * sizeof(int));
        Used[i] = false;
    }
    for (int i = 0; i < N; i++)                     //Заполнение
    {
        for (int j = 0; j < N; j++)
        {
            M[i][j] = rand() % 2;
            M[j][i] = M[i][j];
            if (i == j)
                M[i][j] = 0;
        }
    }

    for (int i = 0; i < N; i++)                     //Вывод
    {
        for (int j = 0; j < N; j++)
        {
            cout << M[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    system("pause");

    for (int i = 0; i < N; i++)
    {
        if (Used[i] == false) {
            BFS(i, M);
        }
    }

    free(M);
}