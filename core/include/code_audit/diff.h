#pragma once

#include <vector>
#include <string>
#include <functional>
#include <stack>
#include <iostream>
#include <cstdio>

namespace CodeAudit
{

using namespace std;

enum DiffChanges
{

    DIFF_ADD = 2,
    DIFF_DEL = 1,
    DIFF_KEP = 0,
    DIFF_RPL = DIFF_ADD | DIFF_DEL,
};

struct DiffTableNode
{
    DiffChanges changes = DIFF_KEP;
    int cost = INT32_MAX;
};

template <typename T>
vector<DiffChanges> diff(vector<T> src, vector<T> dst, vector<DiffChanges> &result, bool (*comparer)(const T*, const T*))
{
    return diff(&src[0], &dst[0], src.size(), dst.size(), result, comparer);
}

template <typename T>
vector<DiffChanges> diff(T *src, T *dst, int lenSrc, int lenDst, vector<DiffChanges> &result, bool (*comparer)(const T*, const T*))
{
    DiffTableNode *table[lenDst + 2];
    auto buffer = calloc((lenDst + 2) * (lenSrc + 2), sizeof(DiffTableNode));
    for (int i = 0; i < lenDst + 2; i++)
    {
        table[i] = (DiffTableNode *)(buffer + (sizeof(DiffTableNode) * (lenSrc + 2) * i));
        for (int j = 0; j < lenSrc + 2; j++)
        {
            table[i][j].cost = INT32_MAX;
        }
    }
    table[0][0].cost = 0;
    for (int j = 0; j < lenDst + 1; j++)
    {
        for (int i = 0; i < lenSrc + 1; i++)
        {
            // delete
            if (table[j][i].cost + 1 < table[j][i + 1].cost)
            {
                table[j][i + 1].changes = DIFF_DEL;
                table[j][i + 1].cost = table[j][i].cost + 1;
            }
            // add
            if (table[j][i].cost + 1 < table[j + 1][i].cost)
            {
                table[j + 1][i].changes = DIFF_ADD;
                table[j + 1][i].cost = table[j][i].cost + 1;
            }
            // keep
            if (i < lenSrc && j < lenDst && comparer(&src[i], &dst[j]) && table[j][i].cost < table[j + 1][i + 1].cost)
            {
                table[j + 1][i + 1].changes = DIFF_KEP;
                table[j + 1][i + 1].cost = table[j][i].cost;
            }
            // for (int y = 0; y < lenDst + 1; y++)
            // {
            //     for (int x = 0; x < lenSrc + 1; x++)
            //     {
            //         switch (table[y][x].changes)
            //         {
            //         case DIFF_ADD:
            //             cout << table[y][x].cost << "+\t";
            //             break;
            //         case DIFF_DEL:
            //             cout << table[y][x].cost << "-\t";
            //             break;
            //         case DIFF_KEP:
            //             cout << table[y][x].cost << "/\t";
            //             break;

            //         default:
            //             break;
            //         }
            //     }
            //     cout << endl;
            // }
            // getchar();
        }
    }
    int i = lenSrc, j = lenDst;
    auto t = calloc(sizeof(char), 1000);
    stack<DiffChanges> diffStack;
    while (i > 0 || j > 0)
    {
        switch (table[j][i].changes)
        {
        case DIFF_ADD:
            diffStack.push(DIFF_ADD);
            j--;
            break;
        case DIFF_DEL:
            diffStack.push(DIFF_DEL);
            i--;
            break;
        case DIFF_KEP:
            diffStack.push(DIFF_KEP);
            i--;
            j--;
            break;
        }
    }

    while (!diffStack.empty())
    {
        result.push_back(diffStack.top());
        diffStack.pop();
    }
    free(buffer);
    return result;
}

vector<DiffChanges> mergeChanges(vector<DiffChanges> &changes);

} // namespace CodeAudit