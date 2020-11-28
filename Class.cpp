#include "Includes.h"

// void Citys::scanCityNumber()
// {
//     cin>>this->cityNumber;
// }

Citys::Citys()
{
    //Let input start at 1
    City guard;
    citys.push_back(guard);
    //
}

void Citys::addCityByNumber()
{
    printf("Enter the number of cities:");
    cin>>this->cityNumber;
    for(int i=1;i<=cityNumber;i++){
        this->addCity();
    }
}
void Citys::addCity()
{
    City city;
    printf("Enter city name:");
    cin>>city.name;
    this->citys.push_back(city);
    this->mp[city.name]=this->citys.size()-1;
}

int Citys::reviseCityName()
{
    printf("Enter the name of the city to be modified:");
    string originalName;cin>>originalName;
    if(!mp[originalName]){printf("Error. Input error\n");return 0;}
    printf("Enter the modified name:");
    string reviseName;cin>>reviseName;
    this->citys[mp[originalName]].name=reviseName;
    mp[reviseName]=mp[originalName];
    mp.erase(mp.find(originalName));
    return 1;
}

int Citys::eraseCity()
{
    printf("Enter the name of the deleted city:");
    string name;cin>>name;
    if(!mp[name]){printf("Error. Input error\n");return 0;}
    mp.erase(mp.find(name));
    return 1;
}

int Citys::addPath()
{
    printf("Enter the start and end of the path:\n(Separate with spaces or newlines)\n");
    string startingPoint,endingPoint;
    cin>>startingPoint>>endingPoint;
    if(!mp[startingPoint]){
        printf("Error. Starting point does not exist.\n");return 0;
    }
    if(!mp[endingPoint]){
        printf("Error. Ending point does not exist.\n");return 0;
    }
    int startingIndex,endingIndex;
    startingIndex=mp[startingPoint];
    endingIndex=mp[endingPoint];

    printf("Enter the travel mode (1 for airplane and 2 for train)\n");
    int mode;cin>>mode;

    printf("Enter the [distance, cost, time] of the path:\n(Separate with spaces or newlines)\n");
    double distance,cost,time;
    cin>>distance>>cost>>time;

    Path tmpPath;
    tmpPath.startingPoint=startingPoint;tmpPath.endingPoint=endingPoint;
    tmpPath.mode=mode;
    tmpPath.lenth=distance;tmpPath.cost=cost;tmpPath.time=time;

    citys[startingIndex].path[mode].push_back(tmpPath);
}

int Citys::revisePath()
{
    printf("Enter the information of the path to be modified:\n");
    Path tmpPath;
    tmpPath.inputInfo();
}

/*------------------------------City-------------------------------------*/
int City::findPath(Path& targetPath)
{
    int mode=targetPath.mode;
    for(int i=0;i<this->path[mode].size();i++){
        auto &checkingPath=path[mode][i];
        if(checkingPath.endingPoint==targetPath.endingPoint
            && checkingPath.lenth==targetPath.lenth
            && checkingPath.cost==targetPath.cost
            && checkingPath.time==targetPath.time
            ){
                return i;
            }
    }
    return -1;
}



/*-----------------------------------------------------------------------*/

/*------------------------------Path-------------------------------------*/
int Path::inputInfo()
{
    printf("Enter the startingPoint:\n");
    cin>>this->startingPoint;
    printf("Enter the endingPoint:\n");
    cin>>this->endingPoint;
    printf("Enter the travel mode (1 for airplane and 2 for train):\n");
    cin>>this->mode;
    printf("Enter the lenth:\n");
    cin>>this->lenth;
    printf("Enter the cost of money:\n");
    cin>>this->cost;
    printf("Enter the time:\n");
    cin>>this->time;
    return 0;
}
/*-----------------------------------------------------------------------*/

