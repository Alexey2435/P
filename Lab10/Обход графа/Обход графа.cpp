#include <iostream>
#include <queue>

using namespace std;

const int N = 5;
int** M = (int**)malloc(N * sizeof(int));
int Dist[N];

void BFSD(int s)
{
    queue <int> Q;
    Q.push(s);
    Dist[s] = 0;
    while (!Q.empty())
    {
        s = Q.front();
        Q.pop();
        cout << s + 1 << endl;
        for (int i = 0; i < N; i++)
        {
            if (M[s][i] != 0 and Dist[i] > Dist[s] + M[s][i]) {
                Q.push(i);
                Dist[i] = Dist[s] + M[s][i];
            }
        }
    }
}

int main()
{
    int start = 0;
    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        M[i] = (int*)malloc(N * sizeof(int));
        Dist[i] = 99;
    }
    for (int i = 0; i < N; i++)                     //Заполнение
    {
        for (int j = 0; j < N; j++)
        {
            M[i][j] = rand() % 6;
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

    cin >> start;

    cout << "\n";

    //system("pause");

    BFSD(start - 1);
    for (int i = 0; i < N; i++)
    {
        if (Dist[i] == -1) {
            BFSD(i);
        }
    }

    cout << endl;
    for (int i = 0; i < N; i++)
    {
        cout << Dist[i] << endl;
    }

    free(M);
}