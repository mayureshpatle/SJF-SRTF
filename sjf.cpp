// @@ its_me :->
// Mayuresh Patle
#include<iostream>
#include<algorithm>
#include<queue>
#define N 10000
#define tb "\t"
using namespace std;
struct prc
{
    int id,at,bt,wt,tat,pr;
};
typedef long long ll;
bool by_at(prc p1,prc p2)
{
    if(p1.at==p2.at) return p1.id<p2.id;
    return p1.at<p2.at;
}
bool by_id(prc p1,prc p2)
{
    return p1.id<p2.id;
}
ll f(prc p,ll i)
{
    return (p.bt*N+p.at)*N+i;
}
int main()
{
    ll n;
    cout<<"Total Processes : ";
    cin>>n;
    prc p[n];
    cout<<"Enter ID, AT & BT\n";
    for(auto &i:p) cin>>i.id>>i.at>>i.bt;
    priority_queue <ll,vector <ll>, greater <ll>> pq;
    sort(p,p+n,by_at);
    ll i=0,t=0;
    cout<<"\nGantt Chart\n";
    while(i<n)
    {
        while(i<n && p[i].at<=t) pq.push(f(p[i],i)),i++;
        if(pq.empty())
        {
            cout<<"Ideal ("<<t<<" -> "<<(t=p[i].at)<<")\n";
            continue;
        }
        ll c=pq.top()%N;
        pq.pop();
        cout<<p[c].id<<" ("<<t<<" -> "<<t+p[c].bt<<")\n";
        p[c].wt=t-p[c].at;
        t+=p[c].bt;
        p[c].tat=p[c].wt+p[c].bt;
    }
    while(!pq.empty())
    {
        ll c=pq.top()%N;
        pq.pop();
        cout<<p[c].id<<" ("<<t<<" -> "<<t+p[c].bt<<")\n";
        p[c].wt=t-p[c].at;
        t+=p[c].bt;
        p[c].tat=p[c].wt+p[c].bt;
    }
    sort(p,p+n,by_id);
    float wt=0,tat=0;
    cout<<"\nID\tWT\tTAT\n";
    for(auto i:p)
    {
        cout<<i.id<<tb<<i.wt<<tb<<i.tat<<endl;
        wt+=i.wt;
        tat+=i.tat;
    }
    cout<<"\nAverage waiting time : "<<wt/(float)n;
    cout<<"\nAverage turnaround time : "<<tat/(float)n;
    return 0;
}
