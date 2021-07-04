#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<memory.h>
#include<iomanip>
using namespace std;

map<string,int> mp_p,mp_s; //进程-序号，资源-序号
vector<vector<int>> Max,Need,Alloc;
vector<int> Tot,Ava,Req;
vector<string> pname;
bool Finish[10005];

void Set(){
    int sn,pn,num;
    string source,proc;
    cout<<"Input the number of source kind:";
    cin>>sn;
    Tot.resize(sn);
    Ava.resize(sn);
    Req.resize(sn);
    for(int i=0;i<sn;i++){
        cout<<"Input the source name:";
        cin>>source;
        cout<<"Input the number of source:";
        cin>>num;
        Tot[i] = num;
        Ava[i] = num;
        mp_s[source] = i;
    }
    cout<<"Input the number of Process:";
    cin>>pn;
    Max.resize(pn,vector<int>(sn));
    Need.resize(pn,vector<int>(sn));
    Alloc.resize(pn,vector<int>(sn));
    for(int i=0;i<pn;i++){
        cout<<"Input the process name:";
        cin>>proc;
        pname.push_back(proc);
        cout<<"Input the maximum number of process using source:"<<endl;
        for(map<string,int>::iterator it=mp_s.begin();it!=mp_s.end();it++){
            cout<<it->first<<" ";
        }
        cout<<endl;
        for(int j=0;j<sn;j++){
            cin>>num;
            Max[i][j] = num;
        }
        cout<<"Input the Allocated number of process using source:"<<endl;
        for(map<string,int>::iterator it=mp_s.begin();it!=mp_s.end();it++){
            cout<<it->first<<" ";
        }
        cout<<endl;
        for(int j=0;j<sn;j++){
            cin>>num;
            Alloc[i][j] = num;
            Ava[j] -= num;
        }
        mp_p[proc] = i;
    }
}

void Init(){
    Need.resize(Max.size(),vector<int>(Max[0].size()));
    for(int i=0;i<Max.size();i++){
        for(int j=0;j<Max[0].size();j++){
            Need[i][j] = Max[i][j]-Alloc[i][j];
        }
    }
}

vector<int> Work;
bool judge(int p_num){
    int sn = mp_s.size();
    for(int i=0;i<sn;i++){
        if(Work[i] < Need[p_num][i])
            return false;
    }
    for(int i=0;i<sn;i++){
        Work[i] = Work[i] + Alloc[p_num][i];
    }
    return true;
}

vector<int> link;
bool SafeLink(){
    Work.clear();
    link.clear();
    memset(Finish,false,sizeof(Finish));
    int pn = mp_p.size();
    Work.resize(mp_s.size());
    for(int i=0;i<mp_s.size();i++){
        Work[i] = Ava[i];
    }
    bool flag = true;
    while(flag){
        flag = false;
        for(int i=0;i<pn;i++){
            if(Finish[i] == true)
                continue;
            if(judge(i)){
                link.push_back(i);
                Finish[i] = true;
                flag = true;
                break;
            }
        }
    }
    return (link.size()==pn);
}

string p_name;
bool Request(){
    cout<<"Input the Request Process name:";
    cin>>p_name;
    cout<<"Input the Request number of process using source:"<<endl;
    for(map<string,int>::iterator it=mp_s.begin();it!=mp_s.end();it++){
        cout<<it->first<<" ";
    }
    cout<<endl;
    int sn = mp_s.size();
    int proc_num = mp_p[p_name];
    for(int i=0;i<sn;i++){
        cin>>Req[i];
    }
    for(int i=0;i<sn;i++){
        if(Ava[i]<Req[i])
            return false;
    }
    for(int i=0;i<sn;i++){
        Ava[i] -= Req[i];
        Alloc[proc_num][i] += Req[i];
    }
    return true;
}

void Back_Req(){
    int proc_num = mp_p[p_name];
    int sn = mp_s.size();
    for(int i=0;i<sn;i++){
        Ava[i] += Req[i];
        Alloc[proc_num][i] -= Req[i];
    }
}

void print(){
    cout<<setw(4)<<" ";
    cout<<setw(4*mp_s.size())<<"Max";
    cout<<setw(4*mp_s.size())<<"Alloc";
    cout<<setw(4*mp_s.size())<<"Need"<<endl;
    cout<<setw(4)<<" ";
    for(map<string,int>::iterator it=mp_s.begin();it!=mp_s.end();it++){
        cout<<setw(4)<<it->first;
    }
    for(map<string,int>::iterator it=mp_s.begin();it!=mp_s.end();it++){
        cout<<setw(4)<<it->first;
    }
    for(map<string,int>::iterator it=mp_s.begin();it!=mp_s.end();it++){
        cout<<setw(4)<<it->first;
    }
    cout<<endl;
    for(int i=0;i<mp_p.size();i++){
        cout<<setw(4)<<pname[i];
        for(int j=0;j<mp_s.size();j++){
            cout<<setw(4)<<Max[i][j];
        }
        for(int j=0;j<mp_s.size();j++){
            cout<<setw(4)<<Alloc[i][j];
        }
        for(int j=0;j<mp_s.size();j++){
            cout<<setw(4)<<Need[i][j];
        }
        cout<<endl;
    }
}

void print_link(){
    for(int i=0;i<link.size();i++){
        cout<<pname[i]<<" ";
    }
    cout<<endl;
}

int main(){
    freopen("test.txt","r",stdin);
    char cs;
    bool lk = true;
    Set();
    while(1){
        cout<<"Request?(Y/N)";
        cin>>cs;
        if(cs == 'Y')
            lk &= Request();
        Init();
        print();
        lk &= SafeLink();
        if(lk){
            cout<<"Safe!"<<endl;
            print_link();
        }
        else{
            cout<<"Unsafe!"<<endl;
            Back_Req();
        }
    }
}