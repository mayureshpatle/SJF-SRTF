// @@ its_me :->
// Mayuresh Patle
#include<iostream>
#include<queue>
#include<algorithm>
#define N 10000
#define tb "\t"
using namespace std;
typedef long long ll;
struct prc
{
    int id,wt,bt,tat,at,pr;
    int init()
    {
        wt=0;
        tat=bt;
    }
};
ll f(prc p,ll i)
{
    return (p.bt*N+p.at)*N+i;
}
bool by_time(prc p1,prc p2)
{
    if(p1.at==p2.at)
    {
        return p1.id<p2.pr;
    }
    return p1.at<p2.at;
}
bool by_id(prc p1,prc p2)
{
    return p1.id<p2.id;
}
int main()
{
    int n;
    cout<<"Total Processes : ";
    cin>>n;
    prc p[n];
    cout<<"Enter ID, BT & AT for each process:\n";
    for(auto &i:p) cin>>i.id>>i.bt>>i.at,i.init();
    sort(p,p+n,by_time);
    priority_queue <ll,vector <ll>, greater <ll>> pq;
    ll i=0,t=p[0].at,c=-1;
    cout<<"\nGantt Chart\n";
    while(i<n)
    {
        while(i<n && p[i].at==t) pq.push(f(p[i],i)),i++;
        if(pq.empty())
        {
            cout<<t<<")\nIdeal ("<<t<<" -> ";
            cout<<(t=p[i].at)<<")\n";
            continue;
        }
        ll x=pq.top();
        pq.pop();
        if((x%N)!=c)
        {
            if(c!=-1) cout<<t<<")\n";
            c=x%N;
            cout<<p[c].id<<" ("<<t<<" -> ";
        }
        if(i==n)
        {
            t+=p[c].bt;
            p[c].bt=0;
        }
        else
        {
            p[c].bt-=p[i].at-t;
            t=p[i].at;
        }
        if(p[c].bt<=0)
        {
            t+=p[c].bt;
            p[c].bt=0;
            p[c].wt=t-p[c].at-p[c].tat;
            p[c].tat+=p[c].wt;
        }
        else pq.push(f(p[c],c));
    }
    cout<<t<<")\n";
    while(!pq.empty())
    {
        ll c=pq.top()%N;
        pq.pop();
        cout<<p[c].id<<" ("<<t<<" -> ";
        t+=p[c].bt;
        p[c].bt=0;
        p[c].wt=t-p[c].at-p[c].tat;
        p[c].tat+=p[c].wt;
        cout<<t<<")\n";
    }
    sort(p,p+n,by_id);
    cout<<"\nID\tWT\tTAT\n";
    float wt=0,tat=0;
    for(auto i:p)
    {
        cout<<i.id<<tb<<i.wt<<tb<<i.tat<<endl;
        wt+=i.wt;
        tat+=i.tat;
    }
    cout<<"Average WT : "<<wt/(float)n<<endl;
    cout<<"Average TAT : "<<tat/(float)n<<endl;
    return 0;
}
