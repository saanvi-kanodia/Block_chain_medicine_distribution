/*#include <iostream>
#include <cstring>
#include <limits>
#include <cctype>
#include <cmath>
#include <vector>

using namespace std;
#include "blockchain.cpp"

const int MAX_CITIES = 50;
const double INF = numeric_limits<double>::infinity();

// Transport cost rates (Rs. per ton km)
const double AIR_COST = 18.0;
const double RAIL_COST = 1.36;
const double ROAD_COST = 2.75;

struct City {
    char name[30];
    double distanceFromMumbai;
};


vector<int> getSelectedPharmacies() {
    int n;
    cout << "\nEnter number of pharmacies you want to deliver to (max 12): ";
    cin >> n;

    vector<int> selected(n + 1);
    selected[0] = 0; // Mumbai

    cout << "Enter the pharmacy names (choose from list):\n";
    for (int i = 0; i < 12; i++) {
        cout << i + 1 << ". " << pharmacies[i] << endl;
    }

    for (int i = 0; i < n; i++) {
        string pname;
        cout << "Pharmacy " << i + 1 << ": ";
        cin >> ws;
        getline(cin, pname);

        bool found = false;
        for (int j = 0; j < 12; j++) {
            if (pname == pharmacies[j]) {
                selected[i + 1] = j + 1; // +1 because 0 is Mumbai
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Invalid pharmacy name. Try again.\n";
            i--;
        }
    }

    return selected;
}
void prim(double cost[50][50], int selected[], int n) {
    int visited[50] = {0}, edges = 0;
    visited[0] = 1; // Start from Mumbai

    double totalCost = 0;

    while (edges < n - 1) {
        double min = INT_MAX;
        int x = -1, y = -1;

        for (int i = 0; i < n; i++) {
            if (visited[i]) {
                for (int j = 0; j < n; j++) {
                    if (!visited[j] && cost[i][j] < min) {
                        min = cost[i][j];
                        x = i;
                        y = j;
                    }
                }
            }
        }

        if (x != -1 && y != -1) {
            visited[y] = 1;
            totalCost += cost[x][y];
            edges++;

            deliveryPath.push_back({selected[x], selected[y], cost[x][y]});
        }
    }

    cout << "\nOptimal Delivery Path (Single Truck using Prim's):\n";
    for (auto &e : deliveryPath) {
        cout << pharmacies[e.from] << " -> " << pharmacies[e.to]
             << " | Distance: " << e.distance << " km\n";
    }
    cout << "Total Minimum Distance: " << totalCost << " km\n";
}


void runPrims() {
    vector<int> selected = getSelectedPharmacies();
    int n = selected.size();

    double graph[50][50];
    buildGraph(graph, selected.data(), n);

    deliveryPath.clear();
    prim(graph, selected.data(), n);
}


void runDijkstra() {
    vector<int> selected = getSelectedPharmacies();
    int n = selected.size();

    double graph[50][50];
    buildGraph(graph, selected.data(), n);

    deliveryPath.clear();
    multipleTruckDistribution(graph, selected.data(), n);
}
*/