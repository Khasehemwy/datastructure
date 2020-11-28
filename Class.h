class City;
class Citys;
class Path;

class Path{
public:
    int mode;
    string startingPoint,endingPoint;
    double lenth,cost,time;

    int inputInfo();
};

class City{
public:
    string name;
    map<int,vector<Path> >path;

    int findPath(Path&);
};

class Citys{
    int cityNumber;
    map<string,int>mp;
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
};