#ifndef ROUTE_OPTIMIZATION_H
#define ROUTE_OPTIMIZATION_H

#include<vector>
#include<string>
#include<iostream>
using namespace std;

double getTransportCost(double);
void buildGraph(double [][50], int const*, int);
void displayPharmacies();
void getSelectedCities(int*, int*);
vector<string> runPrims();
vector<string> runDijkstra();

#endif
