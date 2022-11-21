#include <iostream>

using namespace std;

const int N = 4;
int Visited[N] = { 0, 0, 0, 0};

void DFS(int s, int** M) {
    cout << s << endl;
    Visited[s - 1] = 1;
    for (int i = 1; i <= N; i++)
        if (M[s - 1][i - 1] == 1 && Visited[i-1] == 0)
        {
            //Visited[i - 1] = 1;
            DFS(i, M);
        }
}

int main()
{
    srand(time(NULL));
    int s = 1;
    int** M = (int**)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        M[i] = (int*)malloc(N * sizeof(int));
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

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << M[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    DFS(s, M);
}
