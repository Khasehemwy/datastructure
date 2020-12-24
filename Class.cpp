#include "Include.h"

int City::findPath(const Path &targetPath)
// Returns the index of the target path, if it does not exist, return -1.
{
    int mode = targetPath.mode;
    for (int i = 0; i < this->path[mode].size(); i++)
    {
        auto &tempPath = path[mode][i];
        if (tempPath.end == targetPath.end)
        {
            return i;
        }
    }
    return -1;
}

Cities::Cities()
{
    // Let index start at 1
    City guard;
    cities.push_back(guard);
}

void Cities::addCity(string name)
{
    City city;
    city.name = name;
    this->cities.push_back(city);
    this->mp[city.name] = this->cities.size() - 1;
}

int Cities::modifyCityName(string oldname, string newname)
{
    if (!mp[oldname])
    {
        return 0;
    }
    this->cities[mp[oldname]].name = newname;
    mp[newname] = mp[oldname];
    mp.erase(mp.find(oldname));
    return 1;
}

int Cities::removeCity(string name)
{
    if (!mp[name])
    {
        return 0;
    }
    mp.erase(mp.find(name));
    return 1;
}

int Cities::addPath(string start, string end, int mode, double dist, double cost, double time)
{
    if (!mp[start])
    {
        return 0;
    }
    if (!mp[end])
    {
        return 0;
    }
    int startIndex = mp[start];

    Path tmpPath;
    tmpPath.start = start;
    tmpPath.end = end;
    tmpPath.mode = mode;
    tmpPath.dist = dist;
    tmpPath.cost = cost;
    tmpPath.time = time;

    cities[startIndex].path[mode].push_back(tmpPath);
    return 1;
}

int Cities::modifyPath(string start, string end, int mode, double dist, double cost,
                      double time) {
    Path targetPath;
    targetPath.start=start;
    targetPath.end=end;
    targetPath.mode=mode;
    if (!mp[targetPath.start]) {
        return -1;
    }
    int indexOfCity = mp[targetPath.start];
    int indexOfPath = this->cities[indexOfCity].findPath(targetPath);
    if (indexOfPath == -1) {
        return -1;
    }
    targetPath.start=start;
    targetPath.end=end;
    targetPath.mode=mode;
    targetPath.dist=dist;
    targetPath.cost=cost;
    targetPath.time=time;
    this->cities[indexOfCity].path[targetPath.mode][indexOfPath] = targetPath;
    return 1;
}

int Cities::removePath(string start,string end,int mode) {
    Path targetPath;
    targetPath.start=start;
    targetPath.end=end;
    targetPath.mode=mode;
    if (!mp[targetPath.start]) {
        return -1;
    }
    int indexOfCity = mp[targetPath.start];
    int indexOfPath = this->cities[indexOfCity].findPath(targetPath);
    if (indexOfPath == -1) {
        return -1;
    }
    vector<Path>::iterator it =
        this->cities[indexOfCity].path[targetPath.mode].begin();
    for (int i = 1; i <= indexOfPath; i++)
        ++it;
    this->cities[indexOfCity].path[targetPath.mode].erase(it);
    return 1;
}

struct Node
{
    string name;
    int index;
    double dist;
};
bool operator<(const Node &a, const Node &b) { return a.dist > b.dist; }
vector<string> Cities::findCheapestPath(string start, string end, int mode)
{
    vector<string> ans;
    if (!mp[start])
    {
        return ans;
    }
    double transitTime[3] = {0, 2, 1};
    int n = this->cities.size() - 1;
    for (int i = 1; i <= n; i++)
    {
        this->cities[i].dist[mode] = INF;
        this->cities[i].visited = 0;
        this->cities[i].totalCost = this->cities[i].totalTime = 0;
    }
    this->cities[mp[start]].dist[mode] = 0;

    priority_queue<Node> pq;
    pq.push({start, mp[start], 0});
    while (!pq.empty())
    {
        Node now = pq.top();
        pq.pop();
        if (this->cities[now.index].visited)
            continue;
        this->cities[now.index].visited = 1;
        for (auto &to : this->cities[now.index].path[mode])
        {
            if (this->cities[now.index].dist[mode] + to.cost <
                this->cities[mp[to.end]].dist[mode])
            {
                this->cities[mp[to.end]].dist[mode] =
                    this->cities[now.index].dist[mode] + to.cost;
                this->cities[mp[to.end]].fromWhichCity =
                    now.name;
                this->cities[mp[to.end]].totalCost =
                    this->cities[now.index].totalCost + to.cost;
                this->cities[mp[to.end]].totalTime =
                    this->cities[now.index].totalTime + to.time +
                    transitTime[mode];
                pq.push({to.end, mp[to.end],
                        this->cities[mp[to.end]].dist[mode]});
            }
        }
    }

    if (this->cities[mp[end]].dist[mode] == INF)
    {
        return ans;
    }

    queue<int> q;
    q.push(mp[end]);
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        ans.push_back(this->cities[x].name);
        if (this->cities[mp[this->cities[x].fromWhichCity]].dist[mode] != 0)
            q.push(mp[this->cities[x].fromWhichCity]);
    }
    ans.push_back(start);
    ans.push_back(to_string(this->cities[mp[end]].totalCost));
    ans.push_back(to_string(this->cities[mp[end]].totalTime - transitTime[mode]));
    return ans;
}

std::ifstream& operator>>(std::ifstream& istr, Cities& c) {
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

std::ofstream& operator<<(std::ofstream& ostr, Cities& c) {
    ostr<<c.cities.size()-1<<endl;
    for(int i=1;i<c.cities.size();i++) {
        ostr<<c.cities[i].name<<endl;
    }
    for(int i=0;i<c.cities.size();i++) {
        for(int j=0;j<c.cities[i].path.size();j++) {
            for(int k=0;k<c.cities[i].path[j].size();k++) {
                ostr<<c.cities[i].path[j][k].start<<" "
                   <<c.cities[i].path[j][k].end<<" "
                   <<c.cities[i].path[j][k].mode<<" "
                   <<c.cities[i].path[j][k].dist<<" "
                   <<c.cities[i].path[j][k].cost<<" "
                   <<c.cities[i].path[j][k].time<<endl;
            }
        }
    }
    return ostr;
}

vector<string> Cities::findFastestPath(string start, string end, int mode)
{
    vector<string> ans;
    if (!mp[start])
    {
        return ans;
    }
    double transitTime[3] = {0, 2, 1};
    int n = this->cities.size() - 1;
    for (int i = 1; i <= n; i++)
    {
        this->cities[i].dist[mode] = INF;
        this->cities[i].visited = 0;
        this->cities[i].totalCost = this->cities[i].totalTime = 0;
    }
    this->cities[mp[start]].dist[mode] = 0;

    priority_queue<Node> pq;
    pq.push({start, mp[start], 0});
    while (!pq.empty())
    {
        Node now = pq.top();
        pq.pop();
        if (this->cities[now.index].visited)
            continue;
        this->cities[now.index].visited = 1;
        for (auto &to : this->cities[now.index].path[mode])
        {
            if (this->cities[now.index].dist[mode] + to.time +
                    transitTime[mode] <
                this->cities[mp[to.end]].dist[mode])
            {
                this->cities[mp[to.end]].dist[mode] =
                    this->cities[now.index].dist[mode] + to.time +
                    transitTime[mode];
                this->cities[mp[to.end]].fromWhichCity =
                    now.name;
                this->cities[mp[to.end]].totalCost =
                    this->cities[now.index].totalCost + to.cost;
                this->cities[mp[to.end]].totalTime =
                    this->cities[now.index].totalTime + to.time +
                    transitTime[mode];
                pq.push({to.end, mp[to.end],
                        this->cities[mp[to.end]].dist[mode]});
            }
        }
    }

    if (this->cities[mp[end]].dist[mode] == INF)
    {
        return ans;
    }

    queue<int> q;
    q.push(mp[end]);
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        ans.push_back(this->cities[x].name);
        if (this->cities[mp[this->cities[x].fromWhichCity]].dist[mode] != 0)
            q.push(mp[this->cities[x].fromWhichCity]);
    }
    ans.push_back(start);
    ans.push_back(to_string(this->cities[mp[end]].totalCost));
    ans.push_back(to_string(this->cities[mp[end]].totalTime - transitTime[mode]));
    return ans;
}