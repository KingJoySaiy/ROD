/*
 * UVA 1591 (大模拟)
 * 题目大意：
 * 给定n篇文章和m个查询，共四种查询：
 * A: 查找有关键字A的文章
 * A AND B：查找包含A和B的文章
 * A OR B：查找包含A或B的文章
 * NOT A：查找不包含A的文章
 * 前三种输出满足条件的文章中包含某一关键字的行，NOT输出满足条件的整篇文章，查找时忽略大小写。
 */
#include<bits/stdc++.h>
#define hash mmp
using namespace std;

const int maxn=32676;
char line[maxn];
map<string,set<int> > hash;  //存储key单词出现在哪些行,key全为小写
vector<string> all;     //初始输入每一行，共nn行
int sline[maxn],nn;     //sline记录每个文章首行出现在哪一行
int n,m;

void store(const char *s){

    static char x[maxn];
    int len=strlen(s);
    for (int i=0;i<len;i++){
        if(isalpha(s[i])){
            int p=0;
            while(isalpha(s[i])) x[p++]=(char)tolower(s[i]),i++;
            i--;
            x[p]='\0';
            hash[x].insert(nn);
        }
    }
}
vector<string> change(char s[]) {

    static char x[maxn];
    vector<string> res;
    int len=strlen(s);
    for (int i=0;i<len;i++)
        if(isalpha(s[i])){
            int r=0;
            while (isalpha(s[i])) x[r++]=(char)tolower(s[i]),i++;
            i--;
            x[r]='\0';
            res.push_back(string(x));
        }
    return res;
}
void ini(){

    cin>>n;
    getchar();
    for(int i=0;i<n;i++){
        sline[i]=nn;
        for (int j=0;gets(line);j++){
            if(strcmp(line,"**********")==0) break;
            all.push_back(string(line));
            store(line),nn++;
        }
    }
    sline[n]=nn;
}
void solve(){

    gets(line);
    vector<string> args=change(line);
    bool flag=0;            //标记是否是第一次出现
    if(args.size()==1){     //find
        set<int> &t=hash[args[0]];
        auto p=t.begin();
        for(int j=0;j<n;j++){
            while(p!=t.end()&&(*p)<sline[j]) p++;
            if(p!=t.end()&&(*p)<sline[j+1]){
                if(flag) puts("----------");
                flag=true;
                while(p!=t.end()&&(*p)<sline[j+1]) puts(all[*p].c_str()),p++;
            }
        }
    }
    else if(args.size()==2){    //not
        set<int> &t=hash[args[1]];
        auto p=t.begin();
        for(int j=0;j<n;j++){
            while(p!=t.end()&&(*p)<sline[j]) p++;
            if(p==t.end()||(*p)>=sline[j+1]){
                if(flag) puts("----------");
                flag=true;
                //注意not这种情况是文章全部输出
                for(int k=sline[j];k<sline[j+1];k++) puts(all[k].c_str());
            }
        }
    }
    else if(args.size()==3){    //and 和 or
        set<int> &t1=hash[args[0]],&t2=hash[args[2]];
        auto p1=t1.begin(),p2=t2.begin();
        for(int j=0;j<n;j++){
            while(p1!=t1.end()&&(*p1)<sline[j]) p1++;
            while(p2!=t2.end()&&(*p2)<sline[j]) p2++;
            bool ok;    //若满足and或or中的条件,则标记ok
            if(args[1]=="and"){
                ok=true;
                ok&=(p1!=t1.end()&&(*p1)<sline[j+1]);
                ok&=(p2!=t2.end()&&(*p2)<sline[j+1]);
            }
            else{
                ok=false;
                ok|=(p1!=t1.end()&&(*p1)<sline[j+1]);
                ok|=(p2!=t2.end()&&(*p2)<sline[j+1]);
            }
            if(!ok) continue;
            if(flag) puts("----------");
            flag=true;
            while(1){
                int a=INT_MAX,b=INT_MAX;
                if(p1!=t1.end()&&(*p1)<sline[j+1]) a=*p1;
                if(p2!=t2.end()&&(*p2)<sline[j+1]) b=*p2;
                if(a==b&&a==INT_MAX) break;
                if(a<b) p1++;
                else if(a>b) p2++,a=b;
                else p1++,p2++;
                puts(all[a].c_str());
            }
        }
    }
    if(!flag) puts("Sorry, I found nothing.");  //没有满足条件的文章,flag为false
    puts("==========");
}
int main(){

    ini();
    cin>>m;
    getchar();
    while(m--) solve();

//    system("pause");
    return 0;
}
/*
4
A manufacturer, importer, or seller of
digital media devices may not (1) sell,
or offer for sale, in interstate commerce,
or (2) cause to be transported in, or in a
manner affecting, interstate commerce,
a digital media device unless the device
includes and utilizes standard security
technologies that adhere to the security
system standards.
**********
Of course, Lisa did not necessarily
intend to read his books. She might
want the computer only to write her
midterm. But Dan knew she came from
a middle-class family and could hardly
afford the tuition, let alone her reading
fees. Books might be the only way she
could graduate
**********
Research in analysis (i.e., the evaluation
of the strengths and weaknesses of
computer system) is essential to the
development of effective security, both
for works protected by copyright law
and for information in general. Such
research can progress only through the
open publication and exchange of
complete scientific results
**********
I am very very very happy!
What about you?
**********
6
computer
books AND computer
books OR protected
NOT security
very
slick
 */
