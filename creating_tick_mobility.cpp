#include<bits/stdc++.h>
using namespace std;

int main(int arg, char *argv[])
{
    if(arg!=3)
        exit(0);

    int no_of_clients=stoi(argv[1],nullptr,10);
    int speed=stof(argv[3],nullptr);
    int present_client,no_of_lines;
    ifstream client_read_handle;
    string line;

    float percent_set_up=0.15;
    float tick_time=0.000137;
    tick_time=(1+percent_set_up)*tick_time;

    for(present_client=0;present_client<no_of_clients;present_client++)
    {
        string str="client_";
        str=str+to_string(present_client);
        str=str+".txt";

        string str2="client_mob_";
        str2=str2+to_string(present_client);
        str2=str2+".txt";

        ofstream client_write_handle;
        client_write_handle.open(str2.c_str(),ios_base::app);

        no_of_lines=0;
        client_read_handle.open(str.c_str());
        while(getline(client_read_handle,line))
            no_of_lines++;
        client_read_handle.close();
        client_read_handle.open(str.c_str());
        double start_time=0.0,finish_time;
        pair <double,double> co_or_start,co_or_finish,trial_point;
        double m=0.0,dist_total,dist,dist_check;;
        co_or_start.first=0.0;
        co_or_start.second=0.0;
        while(no_of_lines--)
        {
            getline(client_read_handle,line);
            finish_time=0.0;
            for(i=0;line[i]!=' ';i++)
                finish_time=finish_time*10+line[i]-'0';
            i++;
            while(line[i++]!=' ');
            i++;
            co_or_finish.first=0.0;
            co_or_finish.second=0.0;
            while(line[i++]!=' ')
            {
                co_or_finish.first=co_or_finish.first*10+line[i]-'0';
            }
            i++;
            while(line[i++]!=' ')
                co_or_finish.second=co_or_finish.second*10+line[i]-'0';
            m=(co_or_finish.second-co_or_start.second)/(co_or_finish.first-co_or_start.second);
            dist_total=pow((co_or_finish.second-co_or_start.second),2)+pow((co_or_finish.first-co_or_start.first),2);
            dist_total=sqrt(dist_total);
            dist=speed*tick_time;
            trial_point.first=dist/(1+m*m)+co_or_start.first;
            trial_point.second=dist/(1+m*m)+co_or_start.second;
            dist_check=pow((trial_point.second-co_or_start.second),2)+pow((trial_point.first-co_or_start.first),2);
            while(dist_check<=dist_total)
            {
                ios_
            }
        }irst


    }


}
