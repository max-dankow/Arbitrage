#ifndef CARBITRAGEFINDER_H
#define CARBITRAGEFINDER_H
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <assert.h>

const int ALG_FORD_BELLMAN = 0;
const int ALG_FLOYD_WARSHALL = 1;

class CArbitrageFinder
{
public:
    CArbitrageFinder();
    ~CArbitrageFinder();
    bool readExchangeRate();
    void printExchangeRate() const;
    bool algorithmBellmanFord(size_t startPoint, std::vector<size_t> &cycle) const;
    bool algorithmFloydWarshall(std::vector<size_t> &cycle) const;
    double checkArbitrage(const std::vector<size_t> &cycle, double start_sum) const;
    bool findArbitrageSequence(std::vector<size_t> &cycle, int algo) const;
private:
    size_t currencyNumber;
    std::vector<std::vector<double> > exchangeRate;
    std::vector<size_t> restoreWay(const std::vector<ssize_t> &predecessor, size_t inCycle) const;
    std::vector<size_t> restoreWay(const std::vector<std::vector<ssize_t> > &next, size_t start, size_t finish) const;
};

#endif // CARBITRAGEFINDER_H
