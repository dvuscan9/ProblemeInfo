#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct muchie
{
    int x, y, c;
};


ifstream fin("apm.in");
ofstream fout("apm.out");
const int NMAX = 200001;
int n, m, dad[NMAX], rang[NMAX], sum;
vector<muchie> g;
vector<pair<int, int>> rez;

int FindSet(int k){
    if(dad[k] != k){
        int repr = FindSet(dad[k]);
        dad[k] = repr;
        return repr;
    }
    return k;
}

void DoUnion(int x, int y){
    if(rang[x] < rang[y]) dad[x] = y;
    else if(rang[x] > rang[y]) dad[y] = x;
    else dad[y] = x, rang[y]++;
}

bool cmp(muchie a, muchie b){
    return a.c < b.c;
}

int main(){
    fin >> n >> m;
    for(int i = 1; i <= n; i++) dad[i] = i, rang[i] = 1;
    for(int i = 1; i <= m; i++){
        int x, y, c;
        fin >> x >> y >> c;
        g.push_back({x, y, c});
    }
    sort(g.begin(), g.end(), cmp);
    for(int i = 0; i < g.size(); i++){
        int s1 = FindSet(g[i].x), s2 = FindSet(g[i].y);
        if(s1 != s2){
            rez.push_back({g[i].x, g[i].y});
            sum += g[i].c;
            DoUnion(s1, s2);
        }
    }
    fout << sum << '\n' << rez.size() << '\n';
    for(int i = 0; i < rez.size(); i++) fout << rez[i].first << ' ' << rez[i].second << '\n';
    fin.close();
    fout.close();
    return 0;
}