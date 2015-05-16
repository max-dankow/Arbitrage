#include <iostream>
#include <vector>
#include "carbitragefinder.h"

int main()
{
    freopen("rate.txt", "r", stdin);
    while (true)
    {
        CArbitrageFinder solver;
        if (!solver.readExchangeRate())
        {
            break;
        }
        std::vector<size_t> cycle;
        solver.algorithmFloydWarshall(cycle);
        if (solver.algorithmBellmanFord(0, cycle))
        {
            for (size_t point : cycle)
            {
                std::cout << point + 1 << ' ';
            }
            std::cout << '\n';
            solver.checkArbitrage(cycle, 1);
        }
        else
        {
            std::cout << "no arbitrage sequence exists";
        }
        std::cout << '\n';
    }
    return 0;
}

