#include "Include.h"

// void Citys::scanCityNumber()
// {
//     cin>>this->cityNumber;
// }

Citys::Citys() {
    // Let input start at 1
    City guard;
    citys.push_back(guard);
    //
}

void Citys::addCity(string name) {
    City city;
    city.name = name;
    this->citys.push_back(city);
    this->mp[city.name] = this->citys.size() - 1;
}

int Citys::reviseCityName(string oldname, string newname) {
    if (!mp[oldname]) {
        return 0;
    }
    this->citys[mp[oldname]].name = newname;
    mp[newname] = mp[oldname];
    mp.erase(mp.find(oldname));
    return 1;
}

int Citys::eraseCity(string name) {
    if (!mp[name]) {
        return 0;
    }
    mp.erase(mp.find(name));
    return 1;
}

int Citys::addPath(string start, string end, int mode, double dist, double cost,
                   double time) {
    if (!mp[start]) {
        return 0;
    }
    if (!mp[end]) {
        return 0;
    }
    int startIndex, endIndex;
    startIndex = mp[start];
    endIndex = mp[end];

    Path tmpPath;
    tmpPath.startingPoint = start;
    tmpPath.endingPoint = end;
    tmpPath.mode = mode;
    tmpPath.lenth = dist;
    tmpPath.cost = cost;
    tmpPath.time = time;

    citys[startIndex].path[mode].push_back(tmpPath);
    return 1;
}

int Citys::revisePath(string start, string end, int mode, double dist, double cost,
                      double time) {
    Path targetPath;
    targetPath.startingPoint=start;
    targetPath.endingPoint=end;
    targetPath.mode=mode;
    if (!mp[targetPath.startingPoint]) {
        return -1;
    }
    int indexOfCity = mp[targetPath.startingPoint];
    int indexOfPath = this->citys[indexOfCity].findPath(targetPath);
    if (indexOfPath == -1) {
        return -1;
    }
    targetPath.startingPoint=start;
    targetPath.endingPoint=end;
    targetPath.mode=mode;
    targetPath.lenth=dist;
    targetPath.cost=cost;
    targetPath.time=time;
    this->citys[indexOfCity].path[targetPath.mode][indexOfPath] = targetPath;
    return 1;
}

int Citys::erasePath(string start,string end,int mode) {
    Path targetPath;
    targetPath.startingPoint=start;
    targetPath.endingPoint=end;
    targetPath.mode=mode;
    if (!mp[targetPath.startingPoint]) {
        return -1;
    }
    int indexOfCity = mp[targetPath.startingPoint];
    int indexOfPath = this->citys[indexOfCity].findPath(targetPath);
    if (indexOfPath == -1) {
        return -1;
    }
    vector<Path>::iterator it =
        this->citys[indexOfCity].path[targetPath.mode].begin();
    for (int i = 1; i <= indexOfPath; i++) it++;
    this->citys[indexOfCity].path[targetPath.mode].erase(it);
    return 1;
}

struct Int {
    string name;
    int id;
    double dis;
};
bool operator<(const Int& aa, const Int& bb) { return aa.dis > bb.dis; }
vector<string> Citys::findCheapestPath(string start, string end, int mk) {
    vector<string> ans;
    if (!mp[start]) {
        return ans;
    }
    double transitTime[3] = {0, 2, 1};
    int n = this->citys.size() - 1;
    for (int i = 1; i <= n; i++) {
        this->citys[i].dis[mk] = INF;
        this->citys[i].vis = 0;
        this->citys[i].totalCost = this->citys[i].totalTime = 0;
    }
    this->citys[mp[start]].dis[mk] = 0;

    priority_queue<Int> q;
    q.push({start, mp[start], 0});
    while (!q.empty()) {
        Int now = q.top();
        q.pop();
        if (this->citys[now.id].vis) continue;
        this->citys[now.id].vis = 1;
        for (auto& to : this->citys[now.id].path[mk]) {
            if (this->citys[now.id].dis[mk] + to.cost <
                this->citys[mp[to.endingPoint]].dis[mk]) {
                this->citys[mp[to.endingPoint]].dis[mk] =
                    this->citys[now.id].dis[mk] + to.cost;
                this->citys[mp[to.endingPoint]].fromWhichCity = now.name;
                this->citys[mp[to.endingPoint]].totalCost =
                    this->citys[now.id].totalCost + to.cost;
                this->citys[mp[to.endingPoint]].totalTime =
                    this->citys[now.id].totalTime + to.time + transitTime[mk];
                q.push({to.endingPoint, mp[to.endingPoint],
                        this->citys[mp[to.endingPoint]].dis[mk]});
            }
        }
    }

    if (this->citys[mp[end]].dis[mk] == INF) {
        return ans;
    }

    queue<int> q1;
    q1.push(mp[end]);
    while (!q1.empty()) {
        int x = q1.front();
        q1.pop();
        ans.push_back(this->citys[x].name);
        if (this->citys[mp[this->citys[x].fromWhichCity]].dis[mk] != 0)
            q1.push(mp[this->citys[x].fromWhichCity]);
    }
    ans.push_back(start);
    ans.push_back(to_string(this->citys[mp[end]].totalCost));
    ans.push_back(to_string(this->citys[mp[end]].totalTime - transitTime[mk]));
    return ans;
}

vector<string> Citys::findFastestPath(string start, string end, int mk) {
    vector<string> ans;
    if (!mp[start]) {
        return ans;
    }
    if (this->floydFinished) {
        // TODO
    } else {
        double transitTime[3] = {0, 2, 1};
        int n = this->citys.size() - 1;
        for (int i = 1; i <= n; i++) {
            this->citys[i].dis[mk] = INF;
            this->citys[i].vis = 0;
            this->citys[i].totalCost = this->citys[i].totalTime = 0;
        }
        this->citys[mp[start]].dis[mk] = 0;

        priority_queue<Int> q;
        q.push({start, mp[start], 0});
        while (!q.empty()) {
            Int now = q.top();
            q.pop();
            if (this->citys[now.id].vis) continue;
            this->citys[now.id].vis = 1;
            for (auto& to : this->citys[now.id].path[mk]) {
                if (this->citys[now.id].dis[mk] + to.time + transitTime[mk] <
                    this->citys[mp[to.endingPoint]].dis[mk]) {
                    this->citys[mp[to.endingPoint]].dis[mk] =
                        this->citys[now.id].dis[mk] + to.time + transitTime[mk];
                    this->citys[mp[to.endingPoint]].fromWhichCity = now.name;
                    this->citys[mp[to.endingPoint]].totalCost =
                        this->citys[now.id].totalCost + to.cost;
                    this->citys[mp[to.endingPoint]].totalTime =
                        this->citys[now.id].totalTime + to.time +
                        transitTime[mk];
                    q.push({to.endingPoint, mp[to.endingPoint],
                            this->citys[mp[to.endingPoint]].dis[mk]});
                }
            }
        }

        if (this->citys[mp[end]].dis[mk] == INF) {
            return ans;
        }

        queue<int> q1;
        q1.push(mp[end]);
        while (!q1.empty()) {
            int x = q1.front();
            q1.pop();
            ans.push_back(this->citys[x].name);
            if (this->citys[mp[this->citys[x].fromWhichCity]].dis[mk] != 0)
                q1.push(mp[this->citys[x].fromWhichCity]);
        }
        ans.push_back(start);
        ans.push_back(to_string(this->citys[mp[end]].totalCost));
        ans.push_back(
            to_string(this->citys[mp[end]].totalTime - transitTime[mk]));
        return ans;
    }
}

std::ifstream& operator>>(std::ifstream& istr, Citys& c) {
    int n;
    string name;
    string start,end;
    int mode;
    double dist, cost, time;
    istr>>n;
    for(int i=0;i<n;i++) {
        istr>>name;
        c.addCity(name);
    }
    while(istr>>start>>end>>mode>>dist>>cost>>time) {
        c.addPath(start,end,mode,dist,cost,time);
    }
    return istr;
}

std::ofstream& operator<<(std::ofstream& ostr, Citys& c) {
    ostr<<c.citys.size()-1<<endl;
    for(int i=1;i<c.citys.size();i++) {
        ostr<<c.citys[i].name<<endl;
    }
    for(int i=0;i<c.citys.size();i++) {
        for(int j=0;j<c.citys[i].path.size();j++) {
            for(int k=0;k<c.citys[i].path[j].size();k++) {
                ostr<<c.citys[i].path[j][k].startingPoint<<" "
                   <<c.citys[i].path[j][k].endingPoint<<" "
                   <<c.citys[i].path[j][k].mode<<" "
                   <<c.citys[i].path[j][k].lenth<<" "
                   <<c.citys[i].path[j][k].cost<<" "
                   <<c.citys[i].path[j][k].time<<endl;
            }
        }
    }
    return ostr;
}

// int Citys::floyd()
// {
//     int a[100][100];
//     for(int k=1;k<=n;k++){
//         for(int i=1;i<=n;i++){
//             for(int j=1;j<=n;j++){
//                 a[i][j] = min(a[i][j],a[i][k]+a[k][j]);
//             }
//         }
//     }
//     return 1;
// }

//*-----------------------------------------------------------------------*/

//************************************************************************/
//*------------------------------City-------------------------------------*/
int City::findPath(Path& targetPath)
// Returns the index of the target path, if it does not exist, return -1.
{
    for (int i = 0; i < this->path[targetPath.mode].size(); i++) {
        auto& checkingPath = path[targetPath.mode][i];
        if (checkingPath.endingPoint == targetPath.endingPoint) {
            return i;
        }
    }
    return -1;
}

//*-----------------------------------------------------------------------*/

//*************************************************************************/
//*------------------------------Path-------------------------------------*/
int Path::inputInfo() {
    printf("Enter the startingPoint : \n");
    cin >> this->startingPoint;
    printf("Enter the endingPoint : \n");
    cin >> this->endingPoint;
    printf("Enter the travel mode (1 for airplane and 2 for train) : \n");
    cin >> this->mode;
    printf("Enter the lenth : \n");
    cin >> this->lenth;
    printf("Enter the cost of money : \n");
    cin >> this->cost;
    printf("Enter the time : \n");
    cin >> this->time;
    return 0;
}

//*-----------------------------------------------------------------------*/
