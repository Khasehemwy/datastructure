class City;
class Citys;
class Path;

class Path{
public:
    double lenth,cost,time;
};

class City{
public:
    string name;
    vector<Path>path;
};

class Citys{
    int cityNumber;
public:
    vector<City>city;

    void scanCityNumber();
    void addCityByNumber();
};