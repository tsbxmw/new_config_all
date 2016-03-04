
#include "server.h"

string path_test;

/*
	localfile[0]="echo Y | ";
	localfile[1]="copy  ";//��������
	localfile[2]=" configfile_all\\";//all_config dir
	localfile[3]=" config_not_read\\";//config not read dir
	localfile[4]=" config_read\\";//config already read dir
	localfile[5]="move  ";//�ƶ�����
	localfile[6]="E:\\version\\P809V50\\P809V50.zip";//���ذ汾����ļ���(Ĭ��)
	localfile[7]=" config_not_test\\";//δ���Եİ汾·��
	localfile[8]="10.63.220.2";
	localfile[9]="mw1101";
	localfile[10]="mw1101";
	localfile[11]="..\\Config_upload\\";
	localfile[12]="del ";
	localfile[13]="\\CI_version\\config_files";
	localfile[14]="M_P809V50*";
	localfile[15]="infofile.info";
	localfile[16]="infofile_open.info";
	localfile[17]="-";
	localfile[18]="";

*/


void server_delay_time(int time)
{
	for(int i=0;i<=time;i++)
	{
		system("@ping -n 2 127.0.0.1 > null");
		cout<<i;
	}
	cout<<endl;
}


bool info_file_copy_file(string localfile[100])
{

	string command = localfile[0] + localfile[1] + localfile[15] + " " + localfile[16];
	int erronum = system(command.c_str());
	cout<<erronum<<endl;
	if(erronum)
		return true;
	else
		return false;
}

bool info_file_del_file(string localfile[100])
{
	string command = localfile[0] + localfile[12] + " " + localfile[16];
	int erronum = system(command.c_str());
	//cout<<erronum<<endl;
	if(erronum)
		return true;
	else
		return false;
}

void system_info_display(string info_line_get[1000][10],int info_line_number)
{
	cout<<"|----- ip -----|---phone--|---  id  --|--sta--|--pc--|"<<endl;
	for(int i=0;i<info_line_number;i++)
	{
		for(int j=0;j<STR_NUMBER;j++)
		{
			cout<<"| "<<info_line_get[i][j]<<" |";
		}
		cout<<endl;
	}
}
//read the info file to get the new status
int info_file_read(string localfile[100],string info_line_get[1000][10])
{
	fstream info_file_open;
	char info_read[300];
	int info_line_str_number,info_line_number = 0;
	
	info_file_open.open(localfile[16]);
	while(info_file_open.getline(info_read,300,'\n'))//��ȡ�ļ��е�ÿһ��
	{
		//cout<<info_read<<endl;
		info_line_str_number = 0;
		info_line_get[info_line_number][0]=strtok(info_read,localfile[17].c_str());
		for(int i=1;i<STR_NUMBER;i++)
		{
			info_line_get[info_line_number][i]=strtok(NULL,localfile[17].c_str());
			//cout<<info_line_get[info_line_number][i]<<endl;
		}
		info_line_number++;
	}
	info_file_open.close();
	return info_line_number;
}
//�����ȡ����ļ���Ϣ��
int  system_info_deal(string info_line_get[1000][10],int info_line_number,string project,string path_file)
{
	cout<< "<-- debug : i am in pc_info_deal function -->"<<endl;
	string project_info_of_pc[1000][10];
	char get_project_name[30];
	int length = project.length()-8;
	cout<<length<<endl;
	for(int i=0;i<length;i++)
	{
		get_project_name[i]=project[i+8];
	}
	cout<<get_project_name<<endl;
	cout<<project<<endl;
	int j=0;
	for(int i=0;i<info_line_number;i++)
	{
		if(info_line_get[i][1]==get_project_name)
		{
			if(info_line_get[i][3]=="NULL")
			{
				for(int k=0;k<STR_NUMBER;k++)
				{
					if(k==0 || k==3)
						project_info_of_pc[j][k/2]=info_line_get[i][k];
				}
				j++;
			}
		}
	}
	system_info_display(project_info_of_pc,j);


	return pc_info_find(info_line_get,project_info_of_pc,info_line_number,j,get_project_name,path_file);

}
//�ҵ����еĻ���ip��д��pc����info
int  pc_info_find(string info_line_get[1000][10],string project_info_of_pc[1000][10],int info_line_number,int info_line_pc_number,char project[30],string path_file)
{
	cout<< "<-- debug : i am in pc_info_find function -->"<<endl; 
	int pc_info[1000],pc_status[1000];
	int temp = 0;
	for(int i=0;i<info_line_pc_number;i++)
	{
		for(int j=0;j<info_line_number;j++)
		{
			if(info_line_get[j][0]==project_info_of_pc[i][0])
			{
				if(info_line_get[j][3]=="NULL")
				{
					pc_info[temp] = 0;
					temp ++;
				}
				else
				{
					//here is 1 sad that is busy
					pc_info[temp] = 1;
					temp ++;
				}
			}

		}
		for(int k=0;k<temp;k++)
		{
			if(pc_info[k]==1)
			{
				pc_status[i]=0;
				break;
			}
			else
			{
				pc_status[i]=1;
			}
		}
		cout<<"<-- the status : "<<project_info_of_pc[i][0]<<" -- "<<pc_status[i]<<"  -->"<<endl;
	}
	
	int x = write_client_status(info_line_get,project_info_of_pc,pc_status,project,info_line_pc_number,info_line_number,path_file);

	cout << path_file <<endl;
	cout << path_test <<endl;

	return x;


}
//дpc info
int write_client_status(string info_line_get[1000][10],string project_info_of_pc[1000][10],int pc_status[1000],char project_1[30],int temp,int info_line_number,string path_file)
{
	cout<< "<-- debug : i am in pc_info_write function -->"<<endl;
	int xdd=0;
	string project = project_1;
	for(int i=0;i<temp;i++)
	{
		if(pc_status[i]==1)
		{
			cout<< "<-- debug : writing the pc info to the client file  -->"<<endl;
			//string commadn = "echo "+project;
			if(xdd==0)
			{
				system(("echo NULL > PROJECT\\"+project+"\\pc_status\\"+project+"_"+project_info_of_pc[i][0]+"_client_read.info").c_str());
				cout<< "<-- create the "+project+"_"+project_info_of_pc[i][0]+"_client_read.info"<<endl;
				path_file = "PROJECT\\"+project+"\\pc_status\\"+project+"_"+project_info_of_pc[i][0]+"_client_read.info";
				cout << "<-- debug : file path is : " << path_file <<" -->"<<endl;
				path_test = path_file;
				rewrite_info(i,info_line_get,info_line_number,project,project_info_of_pc[i][0]);
				xdd++;
				system_info_display(info_line_get,info_line_number);
				return 1;
				break;
			}
				//system(("echo "+project+"-"+project_info_of_pc[i][0]+"-NULL >> PROJECT\\"+project+"\\client_read.info").c_str());
		}
	}
	return 0;
}

//rewrite the pc_info.info file
void rewrite_info(int line_number,string info_line_get[1000][10],int info_line_number,string project,string project_info_of_pc)
{
	for(int i=0;i<info_line_number;i++)
	{

		cout<<"<-- debug : i am in rewrite_info to write ! -->"<<endl;
		if(i==0){
			if(project_info_of_pc == info_line_get[i][0])
			{
				if(project == info_line_get[i][1])
				{
					system(("echo "+info_line_get[i][0]+"-"+info_line_get[i][1]+"-"+info_line_get[i][2]+"-BUSY-"+info_line_get[i][4]+">infofile.info").c_str());
				}
				else
				{
					system(("echo "+info_line_get[i][0]+"-"+info_line_get[i][1]+"-"+info_line_get[i][2]+"-"+info_line_get[i][3]+"-"+info_line_get[i][4]+">infofile.info").c_str());
				}
			}
			else
				system(("echo "+info_line_get[i][0]+"-"+info_line_get[i][1]+"-"+info_line_get[i][2]+"-"+info_line_get[i][3]+"-"+info_line_get[i][4]+">infofile.info").c_str());
		}
		else
		{
			if(project_info_of_pc == info_line_get[i][0])
			{
				if(project == info_line_get[i][1])
				{
					system(("echo "+info_line_get[i][0]+"-"+info_line_get[i][1]+"-"+info_line_get[i][2]+"-BUSY-"+info_line_get[i][4]+">>infofile.info").c_str());
				}
				else
				{
					system(("echo "+info_line_get[i][0]+"-"+info_line_get[i][1]+"-"+info_line_get[i][2]+"-"+info_line_get[i][3]+"-"+info_line_get[i][4]+">>infofile.info").c_str());
				}
			}
			else
				system(("echo "+info_line_get[i][0]+"-"+info_line_get[i][1]+"-"+info_line_get[i][2]+"-"+info_line_get[i][3]+"-"+info_line_get[i][4]+">>infofile.info").c_str());
	

		}
	}
}