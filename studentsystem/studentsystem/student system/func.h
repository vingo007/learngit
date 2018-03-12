#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


typedef struct user_data{
	char user_name[20];
	char pwd[20];
	int  auth;
	int user_ID;
	struct user_data *next;
}user_data,*puser_data;

typedef struct student_data{
	int ID;
	char name[20];
	char sex;
	float score_1;
	float score_2;
	float score_3;
	struct student_data *next;
}student_data,*pstudent_data;


void user_data_list(puser_data* ,puser_data*);
void student_data_list(pstudent_data*,pstudent_data*);
void student_list_print(pstudent_data);//---------student print
void list_print(puser_data);
void login(puser_data,puser_data);
void student_login(int);
void admin_login();
void search_score(int);
//---------------------------------------admin operate
void search_student_information();
void add_student_information();
void update_student_information();
void delete_student_information();
void add_user_account();
void update_user_account();
void delete_user_account();
void search_user_account();