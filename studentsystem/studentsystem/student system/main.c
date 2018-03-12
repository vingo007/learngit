#include"func.h"

int main(){
	int i=0;
	puser_data user_data_phead=NULL;
	puser_data user_data_ptail=NULL;
	pstudent_data student_data_phead=NULL;
	pstudent_data student_data_ptail=NULL;
	user_data_list(&user_data_phead,&user_data_ptail);
	while(i<3){
		login(user_data_phead,user_data_ptail);
		i++;
	}
	printf("wrong beyond three times ! \n");
	return 0;
}