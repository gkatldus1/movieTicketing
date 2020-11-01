#include <stdio.h>
#include <string.h>
#define XSIZE 5

int print_seats(int s_array[3][5]);
int reserve(int s_array[][5], int row, int col, struct user_info ID);
int cancel(int s_array[][5], int row, int col, struct user_info ID);
int check_login(struct user_info user[], struct user_info ID, int size);
int load_user_info(struct user_info user[],int size);
int load_reservation_info(int s[][XSIZE]);
int save_reservation_info(int s[][XSIZE]);



struct user_info {
	int id_num;
	char id[10];
	char password[10];
};



int main(void)
{
	struct user_info user[10];
	int select;
	char row;
	int	col;
	int s[3][5] = { 0, };
	struct user_info log_ID;
	int c = 0;
	int call;
	if (call=load_user_info(user, 10) < 0) {
		printf("error");
		return 0;
	}
	load_reservation_info(s);
	



	printf("로그인을 하세요\n");
	while (1) {

		printf("id:");
		fflush(stdin);
		scanf("%s", log_ID.id);
		printf("password:");
		scanf("%s", &log_ID.password);
		if ((log_ID.id_num = check_login(user, log_ID, 10)) > 0) {
			printf("%s님 반갑습니다\n", log_ID.id);
			break;
		}
		else if (check_login(user, log_ID, 10) == -2)
		{
			printf("해당 아이디는 존재하나 패스워드가 다름\n");
			printf("다시 로그인을 하세요\n");
		}
		else
		{
			printf("해당 아이디가 없음\n");
			printf("다시 로그인을 하세요.\n");
		}
	}
	


	do
	{
		printf("1--좌석 확인하기\n");
		printf("2--예약하기\n");
		printf("3--예약 취소하기\n");
		printf("4--다른 사용자로 로그인하기\n");
		printf("5--종료하기\n");
		printf("메뉴를 선택하시오:");
		scanf_s("%d", &select);

		if (select == 1)
		{
			printf("선택된 메뉴 = 좌석 확인하기\n\n");
			print_seats(s);

		}
		else if (select == 2)
		{
			printf("선택된 메뉴 ==예약하기\n\n");
			printf("예약을 원하는 자리는(예- A2)?:");
			while (c = getchar() != '\n' && c != EOF) {};
			scanf("%c%d", &row, &col);
			reserve(s, row-'A', col,log_ID);
		
			print_seats(s);


		}
		else if (select == 3)
		{
			printf("선택된 메뉴 == 예약 취소하기 \n\n");
			printf("예약 취소를 원하는 자리는(예- A2)?: ");
			while (c = getchar() != '\n' && c != EOF) {};
			scanf("%c%d", &row, &col);
			cancel(s, row -'A', col,log_ID);

			print_seats(s);

		}
		else if (select == 4) {
			printf("다른 사용자로 로그인을 하세요\n");
			while (1) {

				printf("id:");
				fflush(stdin);
				scanf("%s", log_ID.id);
				printf("password:");
				scanf("%s", &log_ID.password);
				if ((log_ID.id_num = check_login(user, log_ID, 10)) > 0) {
					printf("%s님 반갑습니다\n", log_ID.id);
					break;
				}
				else if (check_login(user, log_ID, 10) == -2)
				{
					printf("해당 아이디는 존재하나 패스워드가 다름\n");
					printf("다시 로그인을 하세요\n");
				}
				else
				{
					printf("해당 아이디가 없음\n");
					printf("다시 로그인을 하세요.\n");
				}
			}


		}







	} while (select != 5);
	printf("선택된 메뉴 = 종료하기 \n\n");
	printf("이용해 주셔서 감사합니다.\n");
	save_reservation_info(s);

	return 0;
}

int print_seats(int s_array[3][5])
{
	int i, j;
	char alpha = 65;
	printf("   |0  1  2  3  4\n");
	printf("---------------------\n");
	for (i = 0; i < 3; i++)
	{
		printf("%c |", alpha+i);
		for (j = 0; j < 5; j++)
		{
			printf(" %d ", s_array[i][j]);
		}

		printf("\n");
	}
	return 0;
}

int reserve(int s_array[][5], int row, int col,struct user_info ID)
{
	if (!(s_array[row][col] == 0))
	{
		printf("이미 예약된 자리입니다.\n");
		return -1;
	}
	else
	{
		s_array[row][col] = ID.id_num;
		return 1;
	}

}

int cancel(int s_array[][5], int row, int col, struct user_info ID)
{
	if (s_array[row][col] == 0)
	{
		printf("예약되지 않은 자리입니다.\n");
		return -1;
	}
	else
	{
		if (s_array[row][col] == ID.id_num)
			s_array[row][col] = 0;
		else
			printf("예약 당사자가 아닙니다\n");
		return 1;
	}

}
int load_user_info(struct user_info user[],int size) {
	
	int i = 0,j,least;
	FILE *fp;
	char buffer[256];
	struct user_info temp;
	if ((fp = fopen("user_data.txt", "r")) == NULL)
	{
		fprintf(stderr, "파일을 열 수 없습니다.\n");
		return -1;
	}
	
	while (!feof(fp))
	{
		fscanf(fp, "%d %s %s", &user[i].id_num, user[i].id, user[i].password );
		i++;
	}

	fclose(fp);
	
	for (i = 0; i < size; i++) {

		least = i;
		for (j = i + 1; j < size; j++)
			if (user[j].id_num < user[least].id_num)
				least = j;
				
		temp = user[i];
		user[i] = user[least];
		user[least] = temp;


	}

	return size;
}

int check_login(struct user_info user[],struct user_info ID, int size)
{
	int low, high, middle;
	low = 0;
	high = size - 1;
	while (low <= high) {
		middle = (low + high) / 2;
		if ( strcmp(ID.id,user[middle].id)== 0) {
			if (strcmp(ID.password, user[middle].password) == 0)
			{
				
				return user[middle].id_num;
			}
			else
				return -2;
		}
			
		else if (strcmp(ID.id, user[middle].id)>0)
			low = middle + 1;
		else if(strcmp(ID.id, user[middle].id) < 0)
			high = middle - 1;
	
	}

	return -1;

}

int load_reservation_info(int s[][XSIZE])
{
	FILE *fp;
	if ((fp = fopen("reservation_data.txt", "r")) == NULL)
		return -1;
	
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
			fscanf(fp, "%d", &s[i][j]);

	fclose(fp);
	return 0;


}

int save_reservation_info(int s[][XSIZE]) {
	FILE *fp;
	if(((fp = fopen("reservation_data.txt","w"))==NULL))
		return -1;
	
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
			fprintf(fp, "%d ", s[i][j]);

	fclose(fp);
	return 0;

}