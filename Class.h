#pragma once
#include<bits/stdc++.h>
using namespace std;

class Path {
   public:
    int mode;
    string startingPoint, endingPoint;
    double lenth, cost, time;

    int inputInfo();
};

class City {
   public:
    string name;
    map<int, vector<Path> > path;
    // map[mode,paths];

    double dis[5];
    double totalCost, totalTime;
    string fromWhichCity;
    int vis;

    int findPath(Path& targetPath);
};

class Citys {
    int cityNumber;
    map<string, int> mp;
    int floydFinished = 0;
    // int changed=0;
   public:
    vector<City> citys;

    Citys();

    void addCity(string);
    int reviseCityName(string, string);
    int eraseCity(string);

    int addPath(string,string,int,double,double,double);
    int revisePath(string,string,int,double,double,double);
    int erasePath(string,string,int);

    vector<string> findCheapestPath(string,string,int);
    vector<string> findFastestPath(string,string,int);
    // int  floyd();

    friend std::ofstream& operator<<(std::ofstream&, Citys&);
    friend std::ifstream& operator>>(std::ifstream&, Citys&);
};

extern Citys cities;
