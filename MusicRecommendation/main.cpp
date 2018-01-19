#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define threshold 500
#define su 771
#define si 413
#define pick 6

double scoreaverage[296111]={0};
int countitem[296111]={0};
int seeduser[su]={0};
int seeditem[si]={0};
int seedscore[su][si]={{0}};

class String
{
private:
    char* s;
    int len;
public:
    String(const char* str)
    {
        int i;
        for(i=0;str[i]!='\0';i++)
            ;
        len=i;
        s=new char[len];
        for(i=0;i<len;i++)
            s[i]=str[i];
    }
    String()
    {
        s=nullptr;
        len=0;
    }
    String(const String& org)
    {
        len=org.len;
        s=new char[len];
        for(int i=0;i<len;i++)
            s[i]=org.s[i];
    }
    String(String&& org)
    {
        len=org.len;
        s=org.s;
        org.s=nullptr;
    }
    ~String()
    {
        delete [] s;
    }
    String& operator=(const String& org)
    {
        if(this!=&org)
        {
            len=org.len;
            delete [] s;
            s=new char[len];
            for(int i=0;i<len;i++)
                s[i]=org.s[i];
        }
        return *this;
    }
    int Getuser()
    {
        int i;
        for(i=0;i<len;i++)
        {
            if(s[i]=='|')
                break;
        }
        int user=0;
        for(int j=0;j<i;j++)
            user=user*10+(s[j]-'0');
        return user;
    }
    int Getitemnum()
    {
        int i;
        for(i=0;i<len;i++)
        {
            if(s[i]=='|')
                break;
        }
        i++;
        int num=0;
        for(;i<len;i++)
            num=num*10+(s[i]-'0');
        return num;
    }
    int Getuseritem()
    {
        int item=0;
        for(int i=0;i<len;i++)
            item=item*10+(s[i]-'0');
        return item;
    }
};

class Testidx
{
private:
    int user;
    int* track;
public:
    Testidx(String* a)
    {
        user=a[0].Getuser();
        track=new int [6];
        for(int i=0;i<6;i++)
            track[i]=a[i+1].Getuseritem();
    }
    Testidx()
    {
        user=0;
        track=nullptr;
    }
    Testidx(const Testidx& org)
    {
        user=org.user;
        track=new int [6];
        for(int i=0;i<6;i++)
            track[i]=org.track[i];
    }
    Testidx(Testidx&& org)
    {
        user=org.user;
        track=org.track;
        org.track=nullptr;
    }
    ~Testidx()
    {
        delete [] track;
    }
    Testidx& operator=(const Testidx& org)
    {
        if(this!=&org)
        {
            user=org.user;
            delete [] track;
            track=new int [6];
            for(int i=0;i<6;i++)
                track[i]=org.track[i];
        }
        return *this;
    }
    int& Getuser()
    {
        return user;
    }
    int*& Gettrack()
    {
        return track;
    }
};

class Trainidx
{
private:
    int user;
    int num;
    int* item;
    int* score;
public:
    Trainidx(String* a)
    {
        user=a[0].Getuser();
        num=a[0].Getitemnum();
        item=new int [num];
        score=new int [num];
        for(int i=0;i<num;i++)
        {
            item[i]=a[2*i+1].Getuseritem();
            score[i]=a[2*i+2].Getuseritem();
            if(score[i]==0)
                score[i]=1;
            countitem[item[i]]++;
            scoreaverage[item[i]]=(scoreaverage[item[i]]*(countitem[item[i]]-1)+score[i])/countitem[item[i]];
        }
    }
    Trainidx()
    {
        user=0;
        num=0;
        item=nullptr;
        score=nullptr;
    }
    Trainidx(const Trainidx& org)
    {
        user=org.user;
        num=org.num;
        item=new int [num];
        score=new int [num];
        for(int i=0;i<num;i++)
        {
            item[i]=org.item[i];
            score[i]=org.score[i];
        }
    }
    Trainidx(Trainidx&& org)
    {
        user=org.user;
        num=org.num;
        item=org.item;
        score=org.score;
        org.item=nullptr;
        org.score=nullptr;
    }
    ~Trainidx()
    {
        delete [] item;
        delete [] score;
    }
    Trainidx& operator=(const Trainidx& org)
    {
        if(this!=&org)
        {
            user=org.user;
            num=org.num;
            delete [] item;
            delete [] score;
            item=new int [num];
            score=new int [num];
            for(int i=0;i<num;i++)
            {
                item[i]=org.item[i];
                score[i]=org.score[i];
            }
        }
        return *this;
    }
    int& Getnum()
    {
        return num;
    }
    int*& Getitem()
    {
        return item;
    }
    int*& Getscore()
    {
        return score;
    }
};

class Trackdata
{
private:
    int len;
    int count;
    int* item;
public:
    Trackdata(const char* str)
    {
        int i;
        for(i=0;str[i]!='\0';i++)
            ;
        len=i;
        count=0;
        for(i=0;i<len;i++)
            if(str[i]=='|')
                count++;
        int* c=new int [count+2];
        item=new int [count+1];
        for(i=0;i<count+1;i++)
            item[i]=0;
        c[0]=-1;
        c[count+1]=len;
        int j=1;
        for(i=0;i<len;i++)
            if(str[i]=='|')
            {
                c[j]=i;
                j++;
            }
        for(j=0;j<=count;j++)
        {
            for(i=c[j]+1;i<c[j+1];i++)
            {
                if(str[i]=='N')
                    break;
                else
                {
                    item[j]=item[j]*10+str[i]-'0';
                }
            }
        }
        delete [] c;
    }
    Trackdata()
    {
        len=0;
        count=0;
        item=nullptr;
    }
    Trackdata(const Trackdata& org)
    {
        len=org.len;
        count=org.count;
        item=new int [count+1];
        for(int i=0;i<count+1;i++)
            item[i]=org.item[i];
    }
    Trackdata(Trackdata&& org)
    {
        len=org.len;
        count=org.count;
        item=org.item;
        org.item=nullptr;
    }
    ~Trackdata()
    {
        delete [] item;
    }
    Trackdata& operator=(const Trackdata& org)
    {
        if(this!=&org)
        {
            len=org.len;
            count=org.count;
            delete [] item;
            item=new int [count+1];
            for(int i=0;i<count+1;i++)
                item[i]=org.item[i];
        }
        return *this;
    }
    int& Getcount()
    {
        return count;
    }
    int*& Getitem()
    {
        return item;
    }
};

struct sim
{
    int no=0;
    double index=0;
};

int main()
{
    char a[10];
    ifstream fin1("testIdx2.txt");
    String b;
    String* c;
    Testidx* test=new Testidx [15715];
    cout<<"loading testIdx2.txt..."<<endl;
    for(int k=0;k<15715;k++)
    {
        fin1>>a;
        b=String(a);
        c=new String [7];
        c[0]=String(a);
        for(int i=1;i<7;i++)
        {
            fin1>>a;
            c[i]=String(a);
        }
        test[k]=Testidx(c);
        delete [] c;
    }
    fin1.close();

    ifstream fin2("trainIdx2.txt");
    Trainidx* train=new Trainidx [40265];
    cout<<"loading trainIdx2.txt..."<<endl;
    for(int k=0;k<40265;k++)
    {
        fin2>>a;
        b=String(a);
        int num=b.Getitemnum()*2+1;
        c=new String [num];
        c[0]=String(a);
        for(int i=1;i<num;i++)
        {
            fin2>>a;
            c[i]=String(a);
        }
        train[k]=Trainidx(c);
        delete [] c;
    }
    fin2.close();

    char a1[200];
    ifstream fin3("trackData2.txt");
    Trackdata d;
    Trackdata* track=new Trackdata [296111];
    int j=0;
    cout<<"loading trackData2.txt..."<<endl;
    while(j<296110)
    {
        fin3>>a1;
        d=Trackdata(a1);
        j=d.Getitem()[0];
        track[j]=d;
    }
    fin3.close();

    int ii=0;
    for(int i=0;i<40265;i++)
        if(train[i].Getnum()>threshold)
            seeduser[ii++]=i;
    cout<<"seeduser: "<<ii<<endl;
    ii=0;
    for(int i=0;i<296111;i++)
        if(countitem[i]>threshold)
            seeditem[ii++]=i;
    cout<<"seeditem: "<<ii<<endl;
    cout<<"building similarity database......"<<endl;
    int num0=0;
    for(int i=0;i<su;i++)
    {
        num0=train[seeduser[i]].Getnum();
        for(int j=0;j<si;j++)
        {
            for(int k=0;k<num0;k++)
            {
                if(seeditem[j]==train[seeduser[i]].Getitem()[k])
                {
                    seedscore[i][j]=train[seeduser[i]].Getscore()[k];
                    break;
                }
                else
                    seedscore[i][j]=1;
            }
        }
    }

    cout<<"recommending......"<<endl;
    int count=0;
    int num=0;
    sim similar[su];
    double testscore[si]={0};
    double numerator=0;
    double denominator1=0;
    double denominator2=0;
    double trackscore=0;
    double albumscore=0;
    double trackscore2=0;
    sim* similarcount;
    double* tempscore;
    double genrescore=0;
    sim score[6];
    char rec[6]={'0','0','0','0','0','0'};
    ofstream fout("result.txt");
    for(int k=0;k<15715;k++)
    {
        num=train[test[k].Getuser()].Getnum();
        for(int j=0;j<si;j++)
        {
            for(int n=0;n<num;n++)
            {
                if(seeditem[j]==train[test[k].Getuser()].Getitem()[n])
                {
                    testscore[j]=train[test[k].Getuser()].Getscore()[n];
                    break;
                }
                else
                    testscore[j]=0;
            }
        }
        for(int i=0;i<su;i++)
        {
            for(int j=0;j<si;j++)
            {
                numerator+=testscore[j]*seedscore[i][j];
                denominator1+=testscore[j]*testscore[j];
                denominator2+=seedscore[i][j]*seedscore[i][j];
            }
            similar[i].no=i;
            similar[i].index=numerator/sqrt(denominator1*denominator2);
            if(denominator1==0||denominator2==0)
                similar[i].index=0;
            numerator=denominator1=denominator2=0;
        }
        for(int p=0;p<pick;p++)
        {
            for(int q=su-1;q>p;q--)
                if(similar[q].index>similar[q-1].index)
                    swap(similar[q],similar[q-1]);
        }

        for(int l=0;l<6;l++)
        {
            for(int j=0,p=0,q=0;j<pick;j++)
            {
                if(similar[j].index!=0)
                {
                    num0=train[seeduser[similar[j].no]].Getnum();
                    for(int n=0;n<num0;n++)
                    {
                        if(test[k].Gettrack()[l]==train[seeduser[similar[j].no]].Getitem()[n])
                        {
                            p++;
                            trackscore=(trackscore*(p-1)+train[seeduser[similar[j].no]].Getscore()[n])/p;
                        }
                        if(track[test[k].Gettrack()[l]].Getitem()[1]==train[seeduser[similar[j].no]].Getitem()[n])
                        {
                            q++;
                            albumscore=(albumscore*(q-1)+train[seeduser[similar[j].no]].Getscore()[n])/q;
                        }
                    }
                }
            }

            count=track[test[k].Gettrack()[l]].Getcount();
            similarcount=new sim [num];
            for(int n=0;n<num;n++)
            {
                similarcount[n].index=0;
                similarcount[n].no=0;
            }
            for(int n=0;n<num;n++)
            {
                similarcount[n].no=n;
                if(track[train[test[k].Getuser()].Getitem()[n]].Getcount()>0)
                {
                    if(track[test[k].Gettrack()[l]].Getitem()[1]==track[train[test[k].Getuser()].Getitem()[n]].Getitem()[1]&&track[test[k].Gettrack()[l]].Getitem()[1]!=0)
                        similarcount[n].index++;
                    if(track[test[k].Gettrack()[l]].Getitem()[2]==track[train[test[k].Getuser()].Getitem()[n]].Getitem()[2]&&track[test[k].Gettrack()[l]].Getitem()[2]!=0)
                        similarcount[n].index++;
                }
                for(int m=3;m<=count;m++)
                {
                    for(int p=3;p<=track[train[test[k].Getuser()].Getitem()[n]].Getcount();p++)
                    {
                        if(track[test[k].Gettrack()[l]].Getitem()[m]==track[train[test[k].Getuser()].Getitem()[n]].Getitem()[p])
                            similarcount[n].index++;
                    }
                }
            }
            for(int m=0;m<9;m++)
            {
                for(int n=num-1;n>m;n--)
                {
                    if(similarcount[n].index>similarcount[n-1].index)
                        swap(similarcount[n],similarcount[n-1]);
                }
            }
            for(int m=0;m<9;m++)
            {
                if(similarcount[m].index>0)
                    trackscore2=trackscore2+train[test[k].Getuser()].Getscore()[similarcount[m].no]*similarcount[m].index/count;
                else
                    break;
            }

            tempscore=new double [count];
            for(int m=0;m<count;m++)
                tempscore[m]=0;
            for(int m=1;m<=count;m++)
            {
                for(int n=0;n<num;n++)
                {
                    if(track[test[k].Gettrack()[l]].Getitem()[m]==train[test[k].Getuser()].Getitem()[n])
                    {
                        tempscore[m-1]=train[test[k].Getuser()].Getscore()[n];
                        break;
                    }
                    else
                        tempscore[m-1]=0;
                }
            }
            score[l].no=l;
            if(count<=2)
                score[l].index=tempscore[0]*100+tempscore[1]*10+trackscore*20+trackscore2*2.5;
            else
            {
                for(int o=2;o<count;o++)
                    genrescore+=tempscore[o];
                genrescore=genrescore/(count-2);
                score[l].index=tempscore[0]*100+tempscore[1]*10+genrescore*0.5+trackscore*3.5+trackscore2*2.5;
            }
            if(score[l].index==0)
                score[l].index=albumscore*1;
            delete [] tempscore;
            delete [] similarcount;
            genrescore=0;
            trackscore=0;
            albumscore=0;
            trackscore2=0;
        }

        for(int p=0;p<3;p++)
        {
            for(int q=5;q>p;q--)
                if(score[q].index>score[q-1].index)
                    swap(score[q],score[q-1]);
            rec[score[p].no]='1';
        }
        for(int p=0;p<6;p++)
        {
            fout<<rec[p]<<endl;
            rec[p]='0';
        }
        cout<<"progress: "<<(k/15714.0)*100<<"%"<<endl;
    }
    cout<<"complete!"<<endl;
}
