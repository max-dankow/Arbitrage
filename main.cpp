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
        std::cout << "Ford-Bellman:\n";
        if (solver.findArbitrageSequence(cycle, ALG_FORD_BELLMAN))
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

        std::cout << "Floyd-Warshall:\n";
        if (solver.findArbitrageSequence(cycle, ALG_FLOYD_WARSHALL))
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

