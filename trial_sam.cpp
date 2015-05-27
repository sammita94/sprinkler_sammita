#include<bits/stdc++.h>
using namespace std;


struct chunk_structure
{
    int no_of_packets;
    int packets_download_time[3000];
    int packets_present[3000];
    int chunk_present;
};

struct database_client
{
    chunk_structure chunk[100];
    int no_of_chunks_present_in_client;

};

struct client_structure
{
    int client_id;
    int path[100];
    int no_of_AP;
    int present_AP_id;
    struct database_client_structure database_client;
    pair <int,int> co_ordinates_client;
    pair <int,int> s_d;
    int state;
    int next_AP_id;

};

struct request_client_to_AP
{
    int client_id_to_AP;
    int status_client;
    int download_request;
    int download_chunk;
};

struct AP_structure
{
    int AP_id;
    request_client_to_AP request_sheet[300];
    chunk_structure chunks_present_in_AP[300];
    int no_of_chunks_present_in_AP;
};

void assign_path_to_client(client_structure &obj,int path_no)
{
    FILE *all_paths_handle=fopen("all_paths.txt","r");
    string line;
    int co=0,res,k=0;
    while(getline(all_paths_handle,line) && co<path_no-1)
        co++;
    getline(all_paths_handle,line);
    co=0;
    for(int i=0;line[i]!='\0';i++)
    {
        if(line[i]!=' ')
        {
            res=res*10 + line[i] - '0';
        }
        else
        {
            obj.path[k++]=res;
            res=0;
            co++;
        }
    }
    obj.no_of_AP=co;
    all_paths_handle.close();

}

void assign_chunks(AP_structure &obj,int id)
{
    obj.AP_id=id;
    int i=0,res=0;
    string line;
    FILE *ap_distribution=fopen("chunk_distribution","r");
    while(getline(ap_distribution,line) && i<id-1)
        i++;
    getline(ap_distribution,line);
    i=0;
    while(line[i]!=' ')
    {
        res=res*10 + line[i]-'0';
        i++;
    }
    obj.no_of_chunks_present_in_AP=res;
    i++;
    res=0;
    for(int j=i;line[j]!='\0';j++)
    {
        if(line[j]!=' ')
            res=res*10 + line[j]-'0';
        else
        {
            obj.chunks_present_in_AP[res].chunk_present=1;
            obj.chunks_present_in_AP[res].no_of_packets=2000;
            for(int j=1;j<=2000;j++)
            {
                obj.chunks_present_in_AP[res].packets_download_time[j]=5;
                obj.chunks_present_in_AP[res].packets_present[j]=1;
            }
            res=0;
        }

    }


}

void initialize_position(client_structure &obj,int i,int path_no)
{
    memset(obj.path,0,sizeof(obj.path));
    assign_path_to_client(obj,i,r);
    obj.client_id=i;
    obj.present_AP_id=-1;
    obj.database_client.no_of_chunks_present_in_client=0;
    obj.next_AP_id=obj.path[0];
}





int main(int argv, char *argv[])
{
    if(argv!=5)
        exit(0);
    float percent_set_up=0.15;
    float tick_time=0.000137;
    tick_time=(1+percent_set_up)*tick_time;
    int no_of_paths=stoi(argv[1],nullptr,10);
    int no_of_clients_per_path=stoi(argv[2],nullptr,10);
    float speed=stof(argv[3],nullptr,10);
    int tot_no_of_AP=stoi(argv[4],nullptr,10);
    int no_of_clients=no_of_clients_per_path*no_of_paths;
    float randomize=0.85;
    client_structure *clients=new client_structure[no_of_clients];
    AP_structure *APs=new AP_structure[tot_no_of_AP];
    FILE *all_paths_handle=fopen("all_paths.txt","r");
    string line;
    int no_of_all_paths=0;
    while(getline(all_paths_handle,line))
        no_of_all_paths++;
    all_paths_handle.close();
    int *random_paths=new int[no_of_paths];
    int countt=0,r;
    while(countt<no_of_paths)
    {
        r=rand() % no_of_paths + 1;
        for(int i=0;i<no_of_paths;i++)
        {
            if(random_paths[i]==r)
                break;
        }
        if(i==no_of_paths)
        {
            random_paths[countt++]=r;
        }
    }
    for(int i=0;i<no_of_clients;i++)
    {
        int k=0;
        k=i/no_of_paths;
        initialize_position(clients[i],i,random_paths[k]);
    }
    for(int i=0;i<tot_no_of_AP;i++)
    {
        assign_chunks(APs[i],i);
    }



