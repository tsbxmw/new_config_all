/* 

*client and server do the double check on the ftp server.
*server will do the commander
*client to check the new file and start test
*author : mw10192582


*/

#include "config.h"

int  main()
{
	string localfile[100],project;
	string temp = "PROJECT\\";
	string path_file;
	int pro_num=18;
	int control = 0;
	

	localfile[0]="echo Y | ";
	localfile[1]="copy  ";//��������
	localfile[2]=" "+project+"\\configfile_all\\";//all_config dir
	localfile[3]=" "+project+"\\config_not_read\\";//config not read dir
	localfile[4]=" "+project+"\\config_read\\";//config already read dir
	localfile[5]="move  ";//�ƶ�����
	localfile[6]="E:\\version\\P809V50\\P809V50.zip";//���ذ汾����ļ���(Ĭ��)
	localfile[7]=" "+project+"\\config_not_test\\";//δ���Եİ汾·��
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


	while(1)
	{
		open_project_config_ini(localfile);
		pro_num=18;
		control = open_project_config_ini(localfile);
		while(control >= 0){//if has the project name
			cout<<"<-- This is the "+localfile[pro_num]+" Project !"<<endl;
			project = temp + localfile[pro_num];
			localfile[2]=" "+project+"\\configfile_all\\";//all_config dir
			localfile[3]=" "+project+"\\config_not_read\\";//config not read dir
			localfile[4]=" "+project+"\\config_read\\";//config already read dir
			localfile[7]=" "+project+"\\config_not_test\\";//δ���Եİ汾·��
			config_ftp_mail(localfile,project,path_file);
			pro_num ++;
			control--;
			delay_time(10);
		}
		

		cout<<"<-- in this 100s , you can add the new project in the PROJECT dir -->"<<endl;
		delay_time(DELAY_TIME);
		
	}
	return 0;
}

