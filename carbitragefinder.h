#ifndef CARBITRAGEFINDER_H
#define CARBITRAGEFINDER_H
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <assert.h>

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
private:
    size_t currencyNumber;
    std::vector<std::vector<double> > exchangeRate;
    std::vector<size_t> restoreCycle(const std::vector<ssize_t> &predecessor, size_t inCycle) const;
};

#endif // CARBITRAGEFINDER_H
