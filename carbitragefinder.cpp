#include "carbitragefinder.h"

CArbitrageFinder::CArbitrageFinder()
{

}

CArbitrageFinder::~CArbitrageFinder()
{

}

bool CArbitrageFinder::readExchangeRate()
{
    if (!(std::cin >> currencyNumber))
    {
        return false;
    }
    exchangeRate.assign(currencyNumber, std::vector<double> (currencyNumber));
    for (size_t i = 0; i < currencyNumber; ++i)
    {
        for (size_t j = 0; j < currencyNumber; ++j)
        {
            if (i == j)
            {
                exchangeRate[i][j] = 1.0;
                continue;
            }
            std::cin >> exchangeRate[i][j];
        }
    }
    return true;
}

void CArbitrageFinder::printExchangeRate() const
{
    for (size_t i = 0; i < currencyNumber; ++i)
    {
        for (size_t j = 0; j < currencyNumber; ++j)
        {
            std::cout << exchangeRate[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

std::vector<size_t> CArbitrageFinder::restoreWay(const std::vector<ssize_t> &predecessor, size_t inCycle) const
{
    ssize_t current = inCycle;
    std::vector<bool> visited(currencyNumber, false);
    std::vector<size_t> cycle;
    for (size_t i = 0; i < currencyNumber; ++i)
    {
        current = predecessor[current];
    }
    while (true)
    {
        cycle.push_back(current);
        if (visited[current])
        {
            break;
        }
        visited[current] = true;
        current = predecessor[current];
    }
    std::reverse(cycle.begin(), cycle.end());
    return cycle;
}

bool CArbitrageFinder::algorithmBellmanFord(size_t startPoint, std::vector<size_t> &cycle) const
{
    std::vector<double> distance(currencyNumber);
    std::vector<ssize_t> predecessor(currencyNumber, -1);
    distance[startPoint] = 1;
    predecessor[startPoint] = -1;
    for (size_t step = 1; step < currencyNumber; ++step)
    {
        for (size_t edgeFrom = 0; edgeFrom < currencyNumber; ++edgeFrom)
        {
            for (size_t edgeTo = 0; edgeTo < currencyNumber; ++edgeTo)
            {
                if (distance[edgeFrom] * exchangeRate[edgeFrom][edgeTo] > distance[edgeTo])
                {
                    distance[edgeTo] = distance[edgeFrom] * exchangeRate[edgeFrom][edgeTo];
                    predecessor[edgeTo] = edgeFrom;
                }
            }
        }
    }
    for (size_t edgeFrom = 0; edgeFrom < currencyNumber; ++edgeFrom)
    {
        for (size_t edgeTo = 0; edgeTo < currencyNumber; ++edgeTo)
        {
            if (distance[edgeFrom] * exchangeRate[edgeFrom][edgeTo] > distance[edgeTo])
            {
                cycle = restoreWay(predecessor, edgeTo);
                return true;
            }
        }
    }
    return false;
}

std::vector<size_t> CArbitrageFinder::restoreWay(const std::vector<std::vector<ssize_t> > &next, size_t start, size_t finish) const
{
    size_t current = next[start][finish];
    std::vector<size_t> way;
    way.push_back(finish);
    while (current != start)
    {
        way.push_back(current);
        current = next[start][current];
    }
    way.push_back(start);
    std::reverse(way.begin(), way.end());
    return way;
}

bool CArbitrageFinder::algorithmFloydWarshall(std::vector<size_t> &cycle) const
{
    std::vector<std::vector<double> > distance(exchangeRate);
    std::vector<std::vector<ssize_t> > next(currencyNumber, std::vector<ssize_t>(currencyNumber));
    for (size_t i = 0; i < currencyNumber; ++i)
    {
        for (size_t j = 0; j < currencyNumber; ++j)
        {
            next[i][j] = i;
        }
    }
    for (size_t k = 0; k < currencyNumber; ++k)
    {
        for (size_t i = 0; i < currencyNumber; ++i)
        {
            for (size_t j = 0; j < currencyNumber; ++j)
            {
                if (distance[i][j] < distance[i][k] * distance[k][j])
                {
                    distance[i][j] = distance[i][k] * distance[k][j];
                    next[i][j] = next[k][j];
                }
            }
        }
    }
    for (size_t i = 0; i < currencyNumber; ++i)
    {
        if (distance[i][i] > 1)
        {
            cycle = restoreWay(next, i, i);
            return true;
        }
    }
    return false;
}

bool CArbitrageFinder::findArbitrageSequence(std::vector<size_t> &cycle, int algo) const
{
    if (algo == ALG_FORD_BELLMAN)
    {
        return algorithmBellmanFord(0, cycle);
    }
    if (algo == ALG_FLOYD_WARSHALL)
    {
        return algorithmFloydWarshall(cycle);
    }
    return false;
}

double CArbitrageFinder::checkArbitrage(const std::vector<size_t> &cycle, double start_sum) const
{
    assert(!cycle.empty());
    double money = start_sum;
    std::cout << "Take " << money << " (" << cycle[0] << ")\n";
    for (size_t i = 1; i < cycle.size(); ++i)
    {
        std::cout << "Exchange " << money << " (" << cycle[i - 1] << ") to " << money * exchangeRate[cycle[i - 1]][cycle[i]] << " (" << cycle[i] << ")\n";
        money *= exchangeRate[cycle[i - 1]][cycle[i]];
    }
    money *= exchangeRate[cycle[cycle.size() - 1]][cycle[0]];
    std::cout << "You get " << money << " (" << cycle[0] << ")\n";
    assert(money > start_sum);
    return money;
}
