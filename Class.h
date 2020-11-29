#pragma once
// #include<bits/stdc++.h>
// using namespace std;

class City;
class Citys;
class Path;

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
    map<int, vector<Path> >path;
    //map[mode,paths];

    double dis[5];
    string fromWhichCity;
    int vis;

    int findPath(Path& targetPath);
};

class Citys {
    int cityNumber;
    map<string, int>mp;
    int floydFinished = 0;
    // int changed=0;
public:
    vector<City>citys;

    Citys();

    // void scanCityNumber();
    void addCityByNumber();
    void addCity();
    int  reviseCityName();
    int  eraseCity();

    int  addPath();
    int  revisePath();
    int  erasePath();

    int  findFastestPath();
    int  findCheapestPath();
    // int  floyd();
};