
/*
version  :    2.0
author   :    MW10192582
function :    build-function,send mail
date     :    2016.1.12
COR      :    ZTE
new      :    ������û���µ�config�ļ�ʱ�Ĵ��������
new      :    �����˶Եݹ�������ջ�Ĵ����Ƴ��ݹ���ã�����β�ݹ�ʹ�ã���ֹ����Ӧ������crash��
*/

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>

#include "config.h"

using namespace std;


int config_ftp_mail(string localfile[100])
{
	cout<<"[1]----##---- This is the Success-Mail function ----##----[1]"<<endl;
	int have_new_config=0,				//have new config or not
		length;							//�жϷ���������û���µ�config�ļ�

	char local_not_read[1000],
		 local_internal[1000];                  

	string temp,						//the internal string which used to save the temp string like hello or world em...
		   PATH;						//to save the path string int the config file
	string path_file_test;

	string info_line_get[1000][10];
	int info_line_number = 0;

	fstream config_all,					//input or output file to open the configfile to read the internal
			config_not_read,
			config_read,
			config_internal,
			config_not_test;

	bool ip_status_local;

	
	open_config_ini(localfile);			//open the config_ini ,to read the config

	mkdir_project_onserver(localfile);

	get_pc_status_from_server(localfile);

	ip_status_local = read_server_status(localfile);


	refresh_configname();
	if( ip_status_local)
	{
		config_not_read.open("filename_not_read.txt");
		if(config_not_read.getline(local_not_read,300,'\n'))//��ȡconfig_not_read name�����1�У�Ȼ������ж�Ӧ��config�ļ���
		{                 
				config_not_read.close();
				refresh_configname();
				temp=local_not_read;
				cout<<temp<<endl;
				length = localfile[8].length();
				cout<<"length="<<length<<endl;
				system((localfile[0]+localfile[5]+localfile[3]+temp+localfile[4]+temp).c_str());
				system((localfile[0]+localfile[1]+localfile[4]+temp+" "+localfile[11]+temp).c_str());
				//����config��������config_read�ļ���
				config_internal.open("config_read\\"+temp);//�򿪶�Ӧ��config�ļ�
				config_internal.getline(local_internal,300,' ');

				if(config_internal.getline(local_internal,300,' '))//���ļ���һ
				{
					del_pc_status_on_server(localfile);
			
					system("echo copy_begin_time=%date:~0,10% %time% >..\\config.config");

					PATH = local_internal;//��þ���·��PATH
					//PATH = local_internal;
					cout<<"<-- the path is : "<<PATH<<" -->"<<endl;


					//��������õ���copy�����ȡconfig�ļ�������
					//system((localfile[0]+localfile[1]+PATH+localfile[6]).c_str());
					//�ӷ�������copy�ļ�������,�˴�ʹ��ftp
					//system((localfile[12]+localfile[6]).c_str());
					//�� ɾ������֮ǰ�������ļ��汾��
					/*
					system("cd ..\\Config_upload");
					system("call upload.bat");
					system("cd ..\\01VersionDown");
					*/
					string newpath="echo get "+PATH+" "+localfile[6]+">>autoftp.cfg";
					cout << newpath <<endl;
					system(("echo open "+localfile[8]+"> autoftp.cfg").c_str());
					system(("echo "+localfile[9]+">> autoftp.cfg").c_str());
					system(("echo "+localfile[10]+">> autoftp.cfg").c_str());
					system((newpath).c_str());
					system("echo bye>> autoftp.cfg");
					system("ftp -s:autoftp.cfg");

					system("echo copy_end_time=%date:~0,10% %time% >>..\\config.config");

					system("call SuccessEmail.bat");
					cout<<"<-- iam read the path and into the next step! -->"<<endl;
					//��SuccessEmail.bat : ������ѹ���غ���ļ�
					return 1;
				}
				else
				{
					set_server_status_null(localfile);
					return 0;

				}
			}
			else
			{
				set_server_status_null(localfile);
				cout<<"<-- Wrong config file ! -->"<<endl;
				return 0;
			}
	}
	else
	{
		set_server_status_null(localfile);
		cout<< "<-- the pc is busy ,please wait for null -->" <<endl;
		return 0;
	}
	
}

