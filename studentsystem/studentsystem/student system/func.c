#include "func.h"

//------------------------------------------------------------student_List_printf

void student_list_print(pstudent_data student_data_phead)
{
	while(student_data_phead!=NULL){
		printf("%d  %10s  %c  %6.2f  %6.2f  %6.2f\n",student_data_phead->ID,student_data_phead->name,student_data_phead->sex,student_data_phead->score_1,student_data_phead->score_2,student_data_phead->score_3);
		student_data_phead=student_data_phead->next;
	}
}

//---------------------------------------------------------------user_List_printf

void user_list_print(puser_data user_data_phead)
{
	while(user_data_phead!=NULL){
		printf("%8s  %8s  %3d  %3d\n",user_data_phead->user_name,user_data_phead->pwd,user_data_phead->auth,user_data_phead->user_ID);
		user_data_phead=user_data_phead->next;
	}
}

//---------------------------------------------------------------user数据串成链表

void user_data_list(puser_data* user_data_phead,puser_data* user_data_ptail)
{
	FILE *fp;
	puser_data pnew=(puser_data)malloc(sizeof(user_data));
	memset(pnew,0,sizeof(user_data));
	pnew->next=NULL;
	fp=fopen("userdata.txt","r");
	if(fp==NULL){
		perror("fopen");
		return;
	}
	fscanf(fp,"%s%s%d%d",pnew->user_name,pnew->pwd,&(pnew->auth),&(pnew->user_ID));//这里pnew->user_name与pnew->pwd表示的是地址，因为它们是字符数组，代表的是首地址
	*user_data_phead=pnew;
	*user_data_ptail=pnew;
	while(feof(fp)==0){
		puser_data pnew=(puser_data)malloc(sizeof(user_data));
		memset(pnew,0,sizeof(user_data));
		pnew->next=NULL;
		fscanf(fp,"%s%s%d%d",pnew->user_name,pnew->pwd,&(pnew->auth),&(pnew->user_ID));
		if(pnew->user_ID==0){
			goto lab;
		} 
		(*user_data_ptail)->next=pnew;
		*user_data_ptail=pnew;
	}
lab:
	fclose(fp);
	fp=NULL;
}
//------------------------------------------------------------student数据串成链表

void student_data_list(pstudent_data* student_data_phead,pstudent_data* student_data_ptail)
{
	FILE *fp;
	pstudent_data pcur;
	pstudent_data ppre;
	pstudent_data pnew=(pstudent_data)malloc(sizeof(student_data));
	memset(pnew,0,sizeof(student_data));
	pnew->next=NULL;
	*student_data_phead=pnew;
	*student_data_ptail=pnew;
	pcur=pnew;
	ppre=pnew;
	fp=fopen("studentdata.txt","r");
	if(fp==NULL){
		perror("fopen");
		return;
	}
	fscanf(fp,"%d%s %c%f%f%f",&(pnew->ID),pnew->name,&(pnew->sex),&(pnew->score_1),&(pnew->score_2),&(pnew->score_3));//特别注意fcanf百分号获取的是地址
	while(feof(fp)==0){
		pstudent_data pnew=(pstudent_data)malloc(sizeof(student_data));
		memset(pnew,0,sizeof(student_data));
		pnew->next=NULL;
		fscanf(fp,"%d%s %c%f%f%f",&(pnew->ID),pnew->name,&(pnew->sex),&(pnew->score_1),&(pnew->score_2),&(pnew->score_3));
		if(pnew->ID==0){
			goto lab;
		}                     //由于update和delete的原因没有这一判断会造成多申请初始化的节点
		//ID没有重复不用判别等号
		if(pnew->ID<pcur->ID){
			pnew->next=*student_data_phead;
			*student_data_phead=pnew;
			pcur=*student_data_phead;
		}else if(pnew->ID>pcur->ID){
				ppre=pcur;
				pcur=pcur->next;
			while(pcur!=NULL){
				if(pnew->ID<pcur->ID){
					ppre->next=pnew;
					pnew->next=pcur;
					pcur=*student_data_phead;
					break;
				}
				ppre=pcur;
				pcur=pcur->next;
			}
		}
		if(pnew->ID>(*student_data_ptail)->ID){
			(*student_data_ptail)->next=pnew;
			*student_data_ptail=pnew;
			pcur=*student_data_phead;
		}
	}
lab:
	fclose(fp);
	fp=NULL;
}

//-------------------------------------------------------------------------登录

void login(puser_data user_data_phead,puser_data user_data_ptail)
{
	int ID;
	char user_name[20]={0};
	char pwd[20]={0};
	char test[1]={0};
	int i=0,j=0,k=0,flag_1,flag_2;
	puser_data pcur=user_data_phead;
	printf("\n\n\n--------------------------------Student System----------------------------------\n\n\n\n");
lab:
	printf("user name:");
	pcur=user_data_phead;
	test[0]=getch();	
	if(test[0]=='\r'||test[0]=='\b'){
		memset(user_name,0,20);
		system("cls");
		goto lab;
	}else{
	printf("%c",test[0]);
	memset(user_name,0,20);
	memset(pwd,0,20);
	i=0,j=0,k=0;
	user_name[i++]=test[0];
	}
user:
	while((user_name[i]=getch())!='\r'){
		if(i==12 && user_name[i]!='\b'){
			printf("");
			goto user;
		}
		if(user_name[i]=='\b'){
			if(i==0){
				printf("");
				goto user;
			}
			printf("\b \b");
			i--;
		}else{
			printf("%c",user_name[i]);
			i++;
		}
	}
	//------------------------------------------------分割点
	printf("\npassword :");
pwd:	
	test[0]=getch();
	if(test[0]=='\r'){
		printf("user name or password are wrong !\n\n\n");
		goto lab;
	}else{
	printf("*");
	memset(pwd,0,20);
	j=0;
	pwd[j++]=test[0];
	}
	while((pwd[j]=getch())!='\r'){
		if(j==12 && pwd[j]!='\b'){
			printf("");
			goto pwd;
		}
		if(pwd[j]=='\b'){
			if(j==0){
				printf("");
				goto pwd;
			}
			printf("\b \b");
			j--;
		}else{
			printf("*");
			j++;
		}
	}
	printf("\n");
	//-------------------------匹配文件数据

	while(pcur!=NULL){
		for(k=0;k<i;k++){
			if(pcur->user_name[k]==user_name[k]){
				flag_1=1;
			}else{
				flag_1=0;
				break;
			}
		}
		for(k=0;k<j;k++){
			if(pcur->pwd[k]==pwd[k]){
				flag_2=1;
			}else{
				flag_2=0;
				break;
			}
		}
		if(flag_1 && flag_2){
			//匹配权限,进入下一界面
			if(pcur->auth==2){
				admin_login();//--------------admin
				goto lab;
			}else{
				ID=pcur->user_ID;
				student_login(ID);//---------student
				goto lab;
			}
			//printf("进入下一界面");
		}else{
			pcur=pcur->next;		
		}
	}
	printf("user name or password are wrong !\n\n\n");
	goto lab;
	return;
}

//--------------------------------------------------------------------admin登录

void admin_login()

{
	int botton;
lab:
	printf("1.search   student information\n");
	printf("2.add      student information\n");
	printf("3.delete   student information\n");
	printf("4.update   student information\n");
	printf("5.add             user account\n");
	printf("6.update          user account\n");
	printf("7.delete          user account\n");
	printf("8.search          user account\n");
	printf("9.exit\n");
	printf("\n\n\n\n");
	printf("select number : ");
	scanf("%d",&botton);
	switch (botton)
	{
	case 1:search_student_information();  goto lab;      break;
	case 2:add_student_information();     goto lab;      break;
	case 3:delete_student_information();  goto lab;      break;
	case 4:update_student_information();  goto lab;      break;
	case 5:add_user_account();            goto lab;      break;
	case 6:update_user_account();         goto lab;      break;
	case 7:delete_user_account();         goto lab;      break;
	case 8:search_user_account();         goto lab;      break;
	case 9:                               return;        break;
	default:printf("invalid botton");     goto lab;      break;
	}
}
//------------------------------------------------------------------student登录

void student_login(int ID)
{
	
	int botton;
lab:
	printf("1.search score\n");
	printf("2.exit\n");
	printf("\n\n\n\n");
	printf("select number : ");
	scanf("%d",&botton);
	switch (botton)
	{
	case 1:search_score(ID);                 goto lab;  break;
	case 2:                                    return;  break;
	default:printf("invalid botton");        goto lab;  break;
	}
}

//------------------------------------------------------admin_search_student

void search_student_information()
{
		pstudent_data student_data_phead=NULL;
		pstudent_data student_data_ptail=NULL;
		pstudent_data pcur;
		int botton,id;
		char name[20];
		student_data_list(&student_data_phead,&student_data_ptail);
		pcur=student_data_phead;
lab:
		student_data_phead=pcur;
		printf("1.search all student\n");
		printf("2.search by ID\n");
		printf("3.search by name\n");
		printf("4.last menu\n\n\n\n\n");
		printf("select number : ");
		scanf("%d",&botton);
		switch(botton)
		{
		case 1 :printf("\n\n\n");student_list_print(student_data_phead); printf("\n\n\n"); goto lab;  break;//有待改进？
		case 2 :printf("input ID : ");
			scanf("%d",&id);
			while(student_data_phead!=NULL){
				if(student_data_phead->ID==id){
					printf("%d%10s %c %.2f %.2f %.2f \n\n\n\n",student_data_phead->ID,student_data_phead->name,student_data_phead->sex,student_data_phead->score_1,student_data_phead->score_2,student_data_phead->score_3);
					                                                                        goto lab;  break;
				}
				student_data_phead=student_data_phead->next;
			};printf("\n\n\nNO FOUND THE STUDENT\n\n\n");setbuf(stdin,NULL);                goto lab;  break;//如果不清空缓存区会死循环
		case 3 :printf("input name : ");
			scanf("%s",&name);
			while(student_data_phead!=NULL){
				if(strcmp(student_data_phead->name,name)==0){
					printf("%d%10s %c %.2f %.2f %.2f \n\n\n\n",student_data_phead->ID,student_data_phead->name,student_data_phead->sex,student_data_phead->score_1,student_data_phead->score_2,student_data_phead->score_3);
					                                                                        goto lab;  break;
				}
				student_data_phead=student_data_phead->next;
			};
			printf("\n\n\nNO FOUND THE STUDENT\n\n\n");
			setbuf(stdin,NULL);//如果不清空缓存区会死循环
			                                                                                goto lab;  break;
		case 4 :                                                                              return;  break;
		default:printf("invalid botton\n\n\n");                                             goto lab;  break;
		}
}

//---------------------------------------------------add_student_information

void add_student_information()
{
	pstudent_data student_data_phead=NULL;
    pstudent_data student_data_ptail=NULL;
	pstudent_data pcur;
	FILE *fp;
	int ID,rec;
	char name[20];
	char sex;
	float score_1,score_2,score_3;
	student_data_list(&student_data_phead,&student_data_ptail);
	pcur=student_data_phead;
	printf("input the student information : \n");
	printf("ID \\ name \\ sex \\ score1 \\ score2 \\ score3\n");
	rec=scanf("%d%s %c%f%f%f",&ID,name,&sex,&score_1,&score_2,&score_3);
	if(rec!=6){
		printf("\n\n\nInvalid data , please input again.\n\n\n");
		return;
	}
	while(pcur!=NULL){
		if(pcur->ID==ID){
			printf("\n\n\n add fault    !\n");
			printf("the ID exist !\n\n\n");
			return;
		}
	pcur=pcur->next;
	}
	fp=fopen("studentdata.txt","a");
	fprintf(fp,"\n%d %s %c %.2f %.2f %.2f",ID,name,sex,score_1,score_2,score_3);//可能会有的地方既\n放的位置
	fclose(fp);
	fp=NULL;
	printf("\n\n\nadd success !\n\n\n");
}

//---------------------------------------------------delete_student_information

void delete_student_information()
{
	pstudent_data student_data_phead=NULL;
    pstudent_data student_data_ptail=NULL;
	pstudent_data pcur,ppre;
	FILE *fp=NULL;
	int ID;
	student_data_list(&student_data_phead,&student_data_ptail);
	pcur=student_data_phead;
	ppre=student_data_phead;
	student_list_print(student_data_phead);
	printf("\n\n\n");
	printf("delete student ID : ");
	scanf("%d",&ID);
	while(pcur!=NULL){
		if(pcur->ID==ID){
			if(pcur==student_data_phead && pcur!=student_data_ptail){
				student_data_phead=student_data_phead->next;
			}else if(pcur==student_data_ptail){
				student_data_ptail=ppre;//待测试释放pcur
				student_data_ptail->next=NULL;
			}else{
				ppre->next=pcur->next;//待测试释放pcur
			}
			pcur=student_data_phead;
			fp=fopen("studentdata.txt","w+");
			while(pcur!=NULL){
			fprintf(fp,"%d %s %c %.2f %.2f %.2f\n",pcur->ID,pcur->name,pcur->sex,pcur->score_1,pcur->score_2,pcur->score_3);
			pcur=pcur->next;
			}
			fclose(fp);
			printf("\n\n\n");
			student_list_print(student_data_phead);
			printf("\n\n\n");
			printf("\n\n\n delete success ! \n\n\n");
			goto lab;
		}
		ppre=pcur;
		pcur=pcur->next;
	}	
	printf("\n\n\nInvalid ID , please check again \n\n\n");
lab:;
}

//---------------------------------------------------update_student_information

void update_student_information()
{
	pstudent_data student_data_phead=NULL;
    pstudent_data student_data_ptail=NULL;
	pstudent_data pcur,ppre;
	FILE *fp=NULL;
	int ID,rec;
	float score_1,score_2,score_3;
	student_data_list(&student_data_phead,&student_data_ptail);
	pcur=student_data_phead;
	ppre=student_data_phead;
	printf("update student ID : ");
	scanf("%d",&ID);
	while(pcur!=NULL){
		if(pcur->ID==ID){
			printf("%d %s %c %.2f %.2f %.2f\n",pcur->ID,pcur->name,pcur->sex,pcur->score_1,pcur->score_2,pcur->score_3);
			printf("please input the : \nscore 1   score 2   score 3\n");
			rec=scanf("%f%f%f",&score_1,&score_2,&score_3);
			if(rec!=3){
				printf("\n\n\nInvalid data , please input again.\n\n\n");
				return;
			}
			pcur->score_1=score_1;
			pcur->score_2=score_2;
			pcur->score_3=score_3;
			pcur=student_data_phead;
			fp=fopen("studentdata.txt","w+");
			while(pcur!=NULL){
				fprintf(fp,"%d %s %c %.2f %.2f %.2f\n",pcur->ID,pcur->name,pcur->sex,pcur->score_1,pcur->score_2,pcur->score_3);
				pcur=pcur->next;
			}
			fclose(fp);
			printf("\n\n\n update success ! \n\n\n");
			goto lab;
		}
		ppre=pcur;
		pcur=pcur->next;
	}	
	printf("\n\n\nInvalid ID , please check again \n\n\n");
lab:;//注意--------------------跳转
}

//-----------------------------------------------------------------search_score

void search_score(int ID)
{
	pstudent_data student_data_phead=NULL;
	pstudent_data student_data_ptail=NULL;
	student_data_list(&student_data_phead,&student_data_ptail);
	while(student_data_phead!=NULL){
		if(student_data_phead->ID==ID){
			printf("%d%10s %c %.2f %.2f %.2f \n\n\n\n",student_data_phead->ID,student_data_phead->name,student_data_phead->sex,student_data_phead->score_1,student_data_phead->score_2,student_data_phead->score_3);
		}
		student_data_phead=student_data_phead->next;
	}
}



//-------user-------user-------user-------user-------user-------user-------user-------user-------user
//-------user-------user-------user-------user-------user-------user-------user-------user-------user
//-------user-------user-------user-------user-------user-------user-------user-------user-------user




//---------------------------------------------------------add_user_information

void add_user_account()
{
	puser_data user_data_phead=NULL;
    puser_data user_data_ptail=NULL;
	puser_data pcur;
	FILE *fp;
	int ID,rec;
	char user[20];
	char pwd[20];
	int auth;
	user_data_list(&user_data_phead,&user_data_ptail);
	pcur=user_data_phead;
	printf("input the user information : \n");
	rec=scanf("%s%s%d%d",user,pwd,&auth,&ID);//注意这里的取地址
	if(rec!=4){
		printf("\n\n\nInvalid data , please input again.\n\n\n");
		return;
	}
	while(pcur!=NULL){
		if(strcmp(pcur->user_name,user)==0){
			printf("\n\n\n add fault    !\n");
			printf("the user exist !\n\n\n");
			return;
		}
	pcur=pcur->next;
	}
	fp=fopen("userdata.txt","a");
	fprintf(fp,"\n%s %s %d %d",user,pwd,auth,ID);//可能会有改的地方既\n放的位置
	fclose(fp);
	fp=NULL;
	printf("\n\n\nadd success !\n\n\n");
}

//------------------------------------------------------update_user_information

void update_user_account()
{
	puser_data user_data_phead=NULL;
    puser_data user_data_ptail=NULL;
	puser_data pcur,ppre;
	FILE *fp=NULL;
	int ID,rec;
	char user[20];
	char pwd[20];
	int auth;
	user_data_list(&user_data_phead,&user_data_ptail);
	pcur=user_data_phead;
	ppre=user_data_phead;
	printf("user       pwd       auth      ID\n");
	printf("---------------------------------\n");
	user_list_print(user_data_phead);
	printf("\n\n\n\n");
	printf("witch student ID update  : ");
	scanf("%d",&ID);//注意这里的取地址
	while(pcur!=NULL){
		if(pcur->user_ID==ID){
			printf("please input the : user \\  password  \\  auth\n\n");
			printf("the   ID   %d   : ",ID);
			rec=scanf("%s%s%d",user,pwd,&auth);
			if(rec!=3){
				printf("\n\n\nInvalid data , please input again.\n\n\n");
				return;
			}
			strcpy(pcur->user_name,user);
			strcpy(pcur->pwd,pwd);
			pcur->auth=auth;
			pcur=user_data_phead;
			fp=fopen("userdata.txt","w+");
			while(pcur!=NULL){
				fprintf(fp,"%s %s %d %d\n",pcur->user_name,pcur->pwd,pcur->auth,pcur->user_ID);
				pcur=pcur->next;
			}
			fclose(fp);
			printf("\n\n\n update success ! \n\n\n");
			goto lab;
		}
		ppre=pcur;
		pcur=pcur->next;
	}	
	printf("\n\n\nInvalid ID , please check again \n\n\n");
lab:;//注意--------------------跳转
}

//------------------------------------------------------delete_user_information

void delete_user_account()
{
	puser_data user_data_phead=NULL;
	puser_data user_data_ptail=NULL;
	puser_data pcur,ppre;
	FILE *fp=NULL;
	int ID;
	user_data_list(&user_data_phead,&user_data_ptail);
	pcur=user_data_phead;
	ppre=user_data_phead;
    printf("    user      pwd   auth  ID\n");
	printf("------------------------------\n");
	user_list_print(user_data_phead);
	printf("\n\n\n\n");
	printf("witch student ID delete  : ");
	scanf("%d",&ID);//注意这里的取地址
	if(ID==0){
		printf("\n\n\n\nyou can't delete yourself !\n\n\n\n");
		return;
	}
	while(pcur!=NULL){
		if(pcur->user_ID==ID){
			if(pcur==user_data_phead && pcur!=user_data_ptail){
				user_data_phead=user_data_phead->next;
			}else if(pcur==user_data_ptail){
				user_data_ptail=ppre;//待测试释放pcur
				user_data_ptail->next=NULL;
			}else{
				ppre->next=pcur->next;//待测试释放pcur
			}
			pcur=user_data_phead;
			fp=fopen("userdata.txt","w+");
			while(pcur!=NULL){
				fprintf(fp,"%s %s %d %d\n",pcur->user_name,pcur->pwd,pcur->auth,pcur->user_ID);
				pcur=pcur->next;
              //删除用户是否连同学生信息一起删除？
			}
			fclose(fp);
			printf("\n\n\n delete success ! \n\n\n");
			goto lab;
		}
		ppre=pcur;
		pcur=pcur->next;
	}	
	printf("\n\n\nInvalid ID , please check again \n\n\n");
lab:;//注意--------------------跳转
}

//------------------------------------------------------search_user_information

void search_user_account()
{
	puser_data user_data_phead=NULL;
	puser_data user_data_ptail=NULL;
	puser_data pcur,ppre;
	FILE *fp=NULL;
	user_data_list(&user_data_phead,&user_data_ptail);
	pcur=user_data_phead;
	ppre=user_data_phead;
	printf("    user      pwd   auth  ID\n");
	printf("------------------------------\n");
	user_list_print(user_data_phead);
	printf("\n\n\n\n");
}