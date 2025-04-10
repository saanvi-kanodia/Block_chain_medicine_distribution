//#include <cstring> 
//#include <cctype> 
#include <iostream>
#include <limits>
#include <cmath> 
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int MAX_CITIES = 50;
const double INF = numeric_limits<double>::infinity();

// Transport cost rates (Rs. per ton km)
const double AIR_COST = 18.0;
const double RAIL_COST = 1.36;
const double ROAD_COST = 2.75;

struct City {
    char Cityname[30];
    double distanceFromMumbai;
    string pharmacy;
};

City pharmacies[MAX_CITIES] = {
    {"Mumbai", 0, "Arogya Pharmacy"}, {"Delhi", 1417, "Capital Cure"}, {"Bangalore", 984, "South Meds"},
    {"Kolkata", 1960, "EastWell Pharma"}, {"Chennai", 1338, "Chennai Chemists"}, {"Pune", 148, "Sahyadri Drugs"},
    {"Hyderabad", 711, "Nizam Meds"}, {"Ahmedabad", 524, "Ahmed Medico"}, {"Jaipur", 1156, "Pink City Pharma"},
    {"Lucknow", 1366, "Lucknow Life"}, {"Kanpur", 1278, "KanHealth"}, {"Nagpur", 816, "Orange City Pharma"},
    {"Indore", 585, "IndoMeds"}, {"Thane", 23, "Thane Tablets"}, {"Bhopal", 777, "Bhopal Biotech"},
    {"Visakhapatnam", 1339, "Vizag Vitals"}, {"Patna", 1754, "Patna Pharma"}, {"Vadodara", 432, "Baroda Meds"},
    {"Ghaziabad", 1420, "GZB Pharma"}, {"Ludhiana", 1520, "LudhMed"}, {"Agra", 1210, "Taj Pharma"},
    {"Nashik", 167, "NashWell"}, {"Faridabad", 1372, "FaridMed"}, {"Meerut", 1442, "Meerut Medico"},
    {"Rajkot", 698, "Raj Reliefs"}, {"Kalyan", 40, "Kalyan Care"}, {"Vasai-Virar", 50, "VV Pharma"},
    {"Varanasi", 1620, "Kashi Meds"}, {"Srinagar", 2030, "Srinagar Supps"}, {"Aurangabad", 335, "Aurora Pharmacy"},
    {"Dhanbad", 1840, "Dhan Wellness"}, {"Amritsar", 1845, "AmritLife"}, {"Navi Mumbai", 22, "Navi Medico"},
    {"Allahabad", 1450, "Prayagraj Meds"}, {"Howrah", 1960, "Howrah Health"}, {"Gwalior", 1086, "Gwalior Cure"},
    {"Jabalpur", 1143, "Jabal Relief"}, {"Coimbatore", 1190, "Coimb Meds"}, {"Vijayawada", 1150, "Vijay Pharma"},
    {"Jodhpur", 935, "Jodhpur Jiva"}, {"Madurai", 1460, "Madurai Medico"}, {"Raipur", 1130, "Raipur Remedies"},
    {"Kota", 911, "Kota Cure"}, {"Guwahati", 2700, "Guwahati Health"}, {"Chandigarh", 1650, "Chandi Pharma"},
    {"Solapur", 400, "Solapur Supps"}, {"Hubli", 580, "Hubli Health"}, {"Mysore", 840, "Mysore Meds"},
    {"Tiruchirappalli", 1500, "Trichy Pharma"}, {"Bareilly", 1400, "Bareilly Biotech"}
};

double getTransportCost(double distance) {
    return distance * min({AIR_COST, RAIL_COST, ROAD_COST});
}

void buildGraph(double graph[50][50], const int selected[], int n) {
    for (int i = 0; i < n; ++i) {
        int from = selected[i];
        for (int j = 0; j < n; ++j) {
            int to = selected[j];
            if (i == j) graph[i][j] = 0;
            else {
                double distance = fabs(pharmacies[from].distanceFromMumbai - pharmacies[to].distanceFromMumbai);
                graph[i][j] = getTransportCost(distance);
            }
        }
    }
}
void displayPharmacies(){
    cout << "List of Pharmacies:\n";
    for (size_t i = 0; i < MAX_CITIES; ++i) {
        cout << i + 1 << ") " << pharmacies[i].pharmacy << ", " << pharmacies[i].Cityname << endl;
    }
}

void getSelectedCities(int& numCities, int selected[]) {
    cout << "Enter number of pharmacies to distribute to(excluding Mumbai): ";
    cin >> numCities;
    cin.ignore();

    selected[0] = 0; // Mumbai is always included
    int count = 1;

    
    displayPharmacies();
    cout << "Select pharmacies by number:\n";
    while (count <= numCities) {
        string pharmacy;
        cout << "Enter pharmacy number #" << count << ": ";
        int index;
        cin>> index;

        //int index = findCityByPharmacy(pharmacy);
        if (index == -1) {
            cout << "Pharmacy not found. Try again.\n";
        } else {
            bool duplicate = false;
            for (int i = 0; i < count; ++i)
                if (selected[i] == index) duplicate = true;

            if (duplicate) cout << "Pharmacy already entered.\n";
            else {
                selected[count] = index;
                count++;
            }
        }
    }
}

vector<string> runPrims() {
    int numCities, selected[50];
    double graph[50][50];

    getSelectedCities(numCities, selected);
    buildGraph(graph, selected, numCities + 1);

    int parent[50];
    double key[50];
    bool mstSet[50];

    for (int i = 0; i <= numCities; ++i) {
        key[i] = INF;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < numCities; ++count) {
        double min = INF;
        int u = -1;
        for (int v = 0; v <= numCities; ++v)
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                u = v;
            }

        mstSet[u] = true;

        for (int v = 0; v <= numCities; ++v)
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
    }

    double totalCost = 0;
    vector<string> path;

    cout << "\nPrim's MST (Route for Single Truck):\n";
    for (int i = 1; i <= numCities; ++i) {
        cout << pharmacies[selected[parent[i]]].pharmacy << " -> " << pharmacies[selected[i]].pharmacy
             << " | Cost: Rs. " << graph[i][parent[i]] << endl;

        totalCost += graph[i][parent[i]];
        path.push_back(pharmacies[selected[parent[i]]].pharmacy);
        path.push_back(pharmacies[selected[i]].pharmacy);
    }

    cout << "Total transport Cost: Rs. " << totalCost << endl;
    return path;
}

vector<string> runDijkstra() {
    int numCities, selected[50];
    double graph[50][50];

    getSelectedCities(numCities, selected);
    buildGraph(graph, selected, numCities + 1);

    vector<string> path;
    double dist[50];
    bool visited[50];
    int src = 0;

    for (int i = 0; i <= numCities; ++i) {
        dist[i] = INF;
        visited[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count <= numCities; ++count) {
        double min = INF;
        int u = -1;
        for (int i = 0; i <= numCities; ++i)
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }

        visited[u] = true;

        for (int v = 0; v <= numCities; ++v)
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
    }

    cout << "\nDijkstra's Shortest Paths (Route for Multiple Trucks):\n";
    double totalCost = 0;
    for (int i = 1; i <= numCities; ++i) {
        cout << "Mumbai -> " << pharmacies[selected[i]].pharmacy << " | Cost: Rs. " << dist[i] << endl;
        path.push_back("Mumbai");
        path.push_back(pharmacies[selected[i]].pharmacy);
        totalCost += dist[i];
    }

    cout << "Total Transport Cost: Rs. " << totalCost << endl;
    return path;
}
