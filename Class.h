#pragma once
#include <bits/stdc++.h>
using namespace std;

class Path
{
public:
    int mode;
    string start, end;
    double dist, cost, time;

    int inputInfo();
};

class City
{
public:
    string name;
    map<int, vector<Path>> path;

    double dist[5];
    double totalCost, totalTime;
    string fromWhichCity;
    int visited;

    int findPath(const Path &targetPath);
};

class Cities
{
    map<string, int> mp;
public:
    vector<City> cities;

    Cities();

    void addCity(string);
    int modifyCityName(string, string);
    int removeCity(string);

    int addPath(string, string, int, double, double, double);
    int modifyPath(string,string,int,double,double,double);
    int removePath(string,string,int);

    vector<string> findCheapestPath(string, string, int);
    vector<string> findFastestPath(string, string, int);

    friend std::ofstream& operator<<(std::ofstream&, Cities&);
    friend std::ifstream& operator>>(std::ifstream&, Cities&);
};

extern Cities cities;
