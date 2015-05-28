#include<bits/stdc++.h>
using namespace std;


struct chunk_structure
{
    int no_of_packets;
    float packets_download_time[3000];
    int packets_present[3000];
    int chunk_present;
};

struct database_client_structure
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
    pair <float,float>  AP_coordinates;
    request_client_to_AP request_sheet[300];
    int chunks_present_in_AP[300];
    int no_of_chunks_present_in_AP;
};

void assign_path_to_client(client_structure &obj,int path_no)
{
    fstream all_paths_handle;
    all_paths_handle.open("all_paths.txt");
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
    fstream ap_distribution;
    ap_distribution.open("chunk_distribution");
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
            obj.chunks_present_in_AP[res]=1;
            res=0;
        }

    }
    ap_distribution.close();
}

void initialize_position(client_structure &obj,int i,int path_no)
{
    memset(obj.path,0,sizeof(obj.path));
    assign_path_to_client(obj,path_no);
    obj.client_id=i;
    obj.present_AP_id=-1;
    obj.database_client.no_of_chunks_present_in_client=0;
    obj.next_AP_id=obj.path[0];
}

void assign_coordinates(AP_structure &obj,int id)
{
    fstream ap_coordinate_handle;
    ap_coordinate_handle.open("ap_co-ordinate_List_File");
    int no_of_lines=0;
    string line,res;
    while(getline(ap_coordinate_handle,line) && no_of_lines<id-1)
        no_of_lines++;
    getline(ap_coordinate_handle,line);
    ap_coordinate_handle.close();
    int i1,i2;
    for(i1=0;line[i1]!=' ';i1++)
        res+=line[i1];
    obj.AP_coordinates.first=stof(res,nullptr);
    res="";
    for(i2=i1+1;line[i2]!=' ';i2++)
        res+=line[i2];
    obj.AP_coordinates.second=stof(res,nullptr);

}



int main(int arg, char *argv[])
{
    if(arg!=5)
        exit(0);

    float percent_set_up=0.15;
    float tick_time=0.000137;
    tick_time=(1+percent_set_up)*tick_time;

    float randomize=0.85;

    int no_of_paths=stoi(argv[1],nullptr,10);
    int no_of_clients_per_path=stoi(argv[2],nullptr,10);
    float speed=stof(argv[3],nullptr);
    int tot_no_of_AP=stoi(argv[4],nullptr,10);
    int no_of_clients=no_of_clients_per_path*no_of_paths;
    int no_of_chunks=stoi(argv[5],nullptr,10);

    client_structure *clients=new client_structure[no_of_clients];
    AP_structure *APs=new AP_structure[tot_no_of_AP];
    chunk_structure *chunks=new chunk_structure[no_of_chunks];

    /*randomly selecting paths*/
    fstream all_paths_handle;
    all_paths_handle.open("all_paths.txt");
    string line;
    int no_of_all_paths=0;
    while(getline(all_paths_handle,line))
        no_of_all_paths++;
    all_paths_handle.close();
    int *random_paths=new int[no_of_paths];
    int countt=0,r,i,k;
    while(countt<no_of_paths)
    {
        srand(time(NULL));
        r=rand() % no_of_paths + 1;
        for(i=0;i<no_of_paths;i++)
        {
            if(random_paths[i]==r)
                break;
        }
        if(i==no_of_paths)
        {
            random_paths[countt++]=r;
        }
    }
    /*initializing clients structure*/
    for(i=0;i<no_of_clients;i++)
    {

        k=i/no_of_paths;
        initialize_position(clients[i],i,random_paths[k]);
    }

    /*Initializing AP with chunks and co-ordinates*/
    for(i=0;i<tot_no_of_AP;i++)
    {
        assign_chunks(APs[i],i);
        assign_coordinates(APs[i],i);

    }

    /*Writing the faulty AP file*/
    float ran;
    ofstream faulty_ap_handle("faulty_ap_list.txt", ios_base::app | ios_base::out);
    for(i=0;i<no_of_clients;i++)
    {
        for(int j=0;j<clients[i].no_of_AP;j++)
        {
            srand(time(NULL));
            ran=(float)(rand() % 100);
            ran=ran/100;
            if(ran<=randomize)
            {
               faulty_ap_handle<<j<<" ";
            }
        }
        faulty_ap_handle<<"\n";
    }
    faulty_ap_handle.close();

    /*Initialize the download time of the chunks*/
    fstream chunk_handle("chunk_packet.txt", ios_base::in);
    for(i=1;i<=no_of_chunks;i++)
    {
        getline(chunk_handle,line);
        string res="";k=0;
        for(int j=0;line[j]!='\0';j++)
        {
            while(line[j]!=' ')
                res+=line[j];
            chunks[i].packets_download_time[k++]=stof(res,nullptr);
        }
    }
    return 0;

}


