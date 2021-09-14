#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int i, j;
bool eulerCircuit = true;
bool eulerPath = true;
bool directed = false;
int start, finish, vertex, startNode, finishNode;

void hasEulerPath(int node[vertex][vertex], int in[vertex], int out[vertex])
{
    int odd = 0;
    int even = 0;
    if (vertex < 2)
    {
        eulerCircuit = false;
        eulerPath = false;
    }
    else if (vertex == 2 && (node[0][1] == 1 || node[1][0] == 1))
    {
        eulerCircuit = false;
        eulerPath = true;
        if (node[0][1] == 1 && node[1][0] == 0)
            startNode = 0;
        else
            startNode = 1;
    }
    else
    {
        if (directed == false)
        {
            for (int i = 0; i < vertex; i++)
            {
                if (in[i] % 2 != 0)
                {
                    odd++;
                    if (odd == 1)
                        startNode = i;
                    if (odd == 2)
                        finishNode = i;
                    if (odd > 2)
                    {
                        eulerCircuit = false;
                        eulerPath = false;
                        break;
                    }
                }
            }
            if (odd == 0)
            {
                startNode = 0;
                finishNode = 0;
            }
            if (odd > 2 || odd == 1)
                eulerPath = false;
            if (odd > 0)
                eulerCircuit = false;
        }

        else
        {
            for (int i = 0; i < vertex; i++)
            {
                if (out[i] - in[i] == 1)
                {
                    start++;
                    if (start = 1)
                        startNode = i;

                    if (start > 1)
                    {
                        eulerPath = false;
                        eulerCircuit = false;
                        break;
                    }
                }
                if (in[i] - out[i] == 1)
                {
                    finish++;
                    if (finish == 1)
                        finishNode = i;

                    if (finish > 1)
                    {
                        eulerPath = false;
                        eulerCircuit = false;
                        break;
                    }
                }
                if (in[i] == out[i])
                    even++;
                if (even != vertex && start == 1)
                    eulerCircuit = false;
            }
        }
    }
    if (eulerPath == true)
    {
        printf("\t Jalur Euler Ditemukan\n");
        printf("\t Start Node : %d\n", startNode + 1);
        printf("\t Finish Node: %d\n", finishNode + 1);
    }
    else
        printf("\t Jalur Euler Tidak Ditemukan\n");
    if (eulerCircuit == true)
        printf("\t Sirkuit Euler Ditemukan\n");
    else
        printf("\t Sirkuit Euler Tidak Ditemukan\n");
}

int main()
{
    int i, j;
    int allVisited = 0;
    printf("Masukkan Banyak Node/Vertex: ");
    scanf("%d", &vertex);
    printf("JUMLAH NODE: %d\n", vertex);
    int node[vertex][vertex];
    for (i = 0; i < vertex; i++)
    {
        for (j = 0; j < vertex; j++)
        {
            if (i != j)
            {

                printf("Masukkan 1 apabila %d dan %d terhubung, 0 jika tidak: ", i + 1, j + 1);
                scanf("%d", &node[i][j]);
            }
            else
            {
                node[i][j] = 0;
            }
        }
    }

    printf("-----------------------------------------------------------------------------\n");
    printf("DISPLAY MATRIKS: \n");
    for (i = 0; i < vertex; i++)
    {
        for (j = 0; j < vertex; j++)
        {
            printf("%d ", node[i][j]);
        }
        printf("\n");
    }

    if (vertex < 2)
        printf("Tidak Ada Graph yang terbentuk!\n");
    else
    {
        int outdegree[vertex];
        for (i = 0; i < vertex; i++)
        {
            outdegree[i] = 0;
            for (j = 0; j < vertex; j++)
            {
                if (node[i][j] == 1)
                {
                    outdegree[i]++;
                }
            }
        }
        int indegree[vertex];
        for (j = 0; j < vertex; j++)
        {
            indegree[j] = 0;
            for (i = 0; i < vertex; i++)
            {
                if (node[i][j] == 1)
                {
                    indegree[j]++;
                }
            }
        }

        if (directed == true)
            printf("BERARAH!\n");
        else
            printf("TIDAK BERARAH!\n");

        hasEulerPath(node, indegree, outdegree);
        if (eulerPath == true)
        {
            printf("-----------------------------------------------------------------------------");
            printf("\nRUTE EULER:\n");
            j = startNode;
            while (allVisited != 1)
            {
                for (i = vertex - 1; i >= 0; i--)
                {
                    if (node[j][i] == 1)
                    {
                        if (startNode > -1)
                        {
                            printf("%d --> %d", j + 1, i + 1);
                            startNode = -1;
                        }
                        else
                            printf(", %d --> %d", j + 1, i + 1);
                        node[j][i] = 0;
                        node[i][j] = 0;
                        j = i;
                        break;
                    }
                    else if (j == finishNode && i == 0 && node[j][i] == 0)
                    {
                        allVisited = 1;
                        break;
                    }
                }
            }
        }
    }
    return 0;
}