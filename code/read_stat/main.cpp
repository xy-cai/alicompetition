#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int gn_mdays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

class LOG{
public:
    int mn_usr_id;
    int mn_brand_id;
    int mn_type;
    int mn_days;
};

bool comp_usr(LOG a, LOG b)
{
    return (a.mn_usr_id<b.mn_usr_id);
}

bool comp_brd(LOG a, LOG b)
{
    return (a.mn_brand_id<b.mn_brand_id);
}

bool comp_day(LOG a, LOG b)
{
    return (a.mn_days<b.mn_days);
}

class USR{
public:
    int mn_id;
    vector <LOG> m_logdata;
};

class BRD{
public:
    int mn_id;
    vector <LOG> m_logdata;
};

vector <LOG> gVC_logdata;
vector <USR> gVC_usrdata;
vector <BRD> gVC_brddata;

//class UsrxBrd
//{
//public:
//    getUsrxBrd(int usr, int brd, int type)
//    {
//        return
//    }
//private:
//    int stat[][][];
//};

void parse_sztime(char *str, int &n_month, int &n_day)
{
    int n_len = strlen(str);
    int i;
    n_month = 0;
    for (i=0;i<n_len;++i)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            n_month *= 10;
            n_month += str[i]-'0';
        }
        else break;
    }
    n_day = 0;
    for (;i<n_len;++i)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            n_day *= 10;
            n_day += str[i]-'0';
        }
        else continue;
    }
    return ;
}

int main()
{
    freopen("../../data/t_alibaba_data.csv","r",stdin);
    gVC_logdata.clear();
    gVC_usrdata.clear();
    gVC_brddata.clear();
    LOG tC_log;
    USR tC_usr;
    BRD tC_brd;
    map <string, int> brd2ind;
    brd2ind.clear();
    int n_month;
    int n_day;
    char psz_time[1000];
    gets(psz_time);
    while(~scanf("%d", &tC_log.mn_usr_id))
    {
        scanf(",%d,%d,%s", &tC_log.mn_brand_id, &tC_log.mn_type, psz_time);
        parse_sztime(psz_time, n_month, n_day);
        //printf("%d %d %d %s %d %d\n", tC_log.mn_usr_id, tC_log.mn_brand_id, tC_log.mn_type, psz_time, n_month, n_day);
        tC_log.mn_days = (n_month-4)*gn_mdays[n_month-1] + n_day;
        gVC_logdata.push_back(tC_log);
    }

    sort(gVC_logdata.begin(), gVC_logdata.end(), comp_usr);
//    freopen("test.txt", "w", stdout);
//    for (int i=0;i<gVC_logdata.size();++i)
//        printf("%d %d %d %d\n", gVC_logdata[i].mn_usr_id,
//               gVC_logdata[i].mn_brand_id,
//               gVC_logdata[i].mn_type,
//               gVC_logdata[i].mn_days);
    tC_usr.mn_id = gVC_logdata[0].mn_usr_id;
    tC_usr.m_logdata.clear();
    tC_usr.m_logdata.push_back(gVC_logdata[0]);
    gVC_usrdata.push_back(tC_usr);
    int t_cnt = 0;
    for (int i=1;i<gVC_logdata.size();++i)
    {
        if (gVC_logdata[i].mn_usr_id == gVC_logdata[i-1].mn_usr_id)
        {
            gVC_usrdata[t_cnt].m_logdata.push_back(gVC_logdata[i]);
        }
        else
        {
            t_cnt ++;
            tC_usr.mn_id = gVC_logdata[i].mn_usr_id;
            tC_usr.m_logdata.clear();
            tC_usr.m_logdata.push_back(gVC_logdata[i]);
            gVC_usrdata.push_back(tC_usr);
        }
        //printf("%d %d %d %d\n", it->mn_usr_id, it->mn_brand_id, it->mn_type, it->mn_days);
    }
    cout<<t_cnt<<endl;

    sort(gVC_logdata.begin(), gVC_logdata.end(), comp_brd);
    tC_brd.mn_id = gVC_logdata[0].mn_brand_id;
    tC_brd.m_logdata.clear();
    tC_brd.m_logdata.push_back(gVC_logdata[0]);
    gVC_brddata.push_back(tC_brd);
    t_cnt = 0;
    for (int i=1;i<gVC_logdata.size();++i)
    {
        if (gVC_logdata[i].mn_brand_id == gVC_logdata[i-1].mn_brand_id)
        {
            gVC_brddata[t_cnt].m_logdata.push_back(gVC_logdata[i]);
        }
        else
        {
            t_cnt ++;
            tC_brd.mn_id = gVC_logdata[i].mn_brand_id;
            tC_brd.m_logdata.clear();
            tC_brd.m_logdata.push_back(gVC_logdata[i]);
            gVC_brddata.push_back(tC_brd);
        }
        //printf("%d %d %d %d\n", it->mn_usr_id, it->mn_brand_id, it->mn_type, it->mn_days);
    }
    cout<<t_cnt<<endl;

    vector <LOG> tVC_log;

    freopen("../../result/read_stat/user_sort_by_days.txt", "w", stdout);
    printf("%d\n\n", gVC_usrdata.size());
    for (int i=0;i<gVC_usrdata.size();++i)
    {
        tVC_log.clear();
        printf("%d\n", gVC_usrdata[i].mn_id);
        tVC_log = gVC_usrdata[i].m_logdata;
        sort(tVC_log.begin(), tVC_log.end(), comp_day);
        for (int j=0;j<tVC_log.size();++j)
        {
            printf("\t%d\t%d\t%d\n", tVC_log[j].mn_brand_id, tVC_log[j].mn_type, tVC_log[j].mn_days);
        }
        printf("\n");
    }

    freopen("../../result/read_stat/user_sort_by_brd.txt", "w", stdout);
    printf("%d\n\n", gVC_usrdata.size());
    for (int i=0;i<gVC_usrdata.size();++i)
    {
        tVC_log.clear();
        printf("%d\n", gVC_usrdata[i].mn_id);
        tVC_log = gVC_usrdata[i].m_logdata;
        sort(tVC_log.begin(), tVC_log.end(), comp_brd);
        for (int j=0;j<tVC_log.size();++j)
        {
            printf("\t%d\t%d\t%d\n", tVC_log[j].mn_brand_id, tVC_log[j].mn_type, tVC_log[j].mn_days);
        }
        printf("\n");
    }

    freopen("../../result/read_stat/brand_sort_by_days.txt", "w", stdout);
    printf("%d\n\n", gVC_brddata.size());
    for (int i=0;i<gVC_brddata.size();++i)
    {
        tVC_log.clear();
        printf("%d\n", gVC_brddata[i].mn_id);
        tVC_log = gVC_brddata[i].m_logdata;
        sort(tVC_log.begin(), tVC_log.end(), comp_day);
        for (int j=0;j<tVC_log.size();++j)
        {
            printf("\t%d\t%d\t%d\n", tVC_log[j].mn_usr_id, tVC_log[j].mn_type, tVC_log[j].mn_days);
        }
        printf("\n");
    }

    freopen("../../result/read_stat/brand_sort_by_usr.txt", "w", stdout);
    printf("%d\n\n", gVC_brddata.size());
    for (int i=0;i<gVC_brddata.size();++i)
    {
        tVC_log.clear();
        printf("%d\n", gVC_brddata[i].mn_id);
        tVC_log = gVC_brddata[i].m_logdata;
        sort(tVC_log.begin(), tVC_log.end(), comp_usr);
        for (int j=0;j<tVC_log.size();++j)
        {
            printf("\t%d\t%d\t%d\n", tVC_log[j].mn_usr_id, tVC_log[j].mn_type, tVC_log[j].mn_days);
        }
        printf("\n");
    }


    int mat[2][900][10000][4];
    memset(mat, 0, sizeof(mat));
    for(int i=0;i<gVC_usrdata.size();++i)
    {
        for (int j=0;j<gVC_usrdata[i].m_logdata.size();++j)
        {
            LOG tmp = gVC_usrdata[i].m_logdata[j];
            if (tmp.mn_days>106)
            {
                mat[1][i][]
            }
        }
    }

    return 0;
}
