//Phạm Hoàng Anh Tuấn
//MSSV 1753123

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <cstdlib> //để sử dụng lệnh xóa màn hình console
#define N_ROWS 3
#define N_COLS 3

void print_board(int a[][N_COLS]);
int check(int a[][N_COLS]);
int check_draw(int a[][N_COLS]);
void player_turn(int a[][N_COLS]);
void AI_turn(int a[][N_COLS]);
int minimax(int a[][N_COLS], int cPlayer);
void play(int a[][N_COLS]);
int main()
{
	static int a[N_ROWS][N_COLS]; //khởi tạo mảng
	play(a); //hàm mở game
}

void play(int a[][N_COLS])
{
	int winner;
	do
	{
		//dự định dùng cho PvP, không có tác dụng hiện tại
		/*do
		{
		printf("X turn, please enter row value and then collum value: \n");
		scanf("%i %i", &x, &y);
		} while ((x > 2) || (x < 0) || (y > 2) || (y < 0) || (a[x][y] != 0));
		a[x][y] = 1;*/
		AI_turn(a);
		winner = check(a);
		if (winner != 0)
		{
			system("cls");
			print_board(a);
			if (winner == -2)
			{
				printf("\nhoa\n");
				printf("\n0\n");
				return;
			}
			printf("\nMay thang\n");
			printf("\n1\n");
			return;
		}

		player_turn(a);
		winner = check(a);
		if (winner != 0)
		{
			system("cls");
			print_board(a);
			if (winner == -2)
			{
				printf("\nhoa\n");
				printf("\n0\n");
				return;
			}
			printf("\nNguoi thang (did you cheat ? =.=)\n");
			printf("\n-1\n");
			return;
		}
		system("cls");
	} 
	while (true);
}
void print_board(int a[][N_COLS])
{
	// In chỉ số cột của bàn cờ
	printf("\n   ");
	for (int j = 0; j < N_COLS; j++)
		printf("  %i ", j);
	printf("\n");

	// In đường kẻ ngang của bàn cờ
	printf("   ");
	for (int k = 0; k < N_COLS; k++)
		printf("+---");
	printf("+\n");

	for (int i = 0; i < N_ROWS; i++) // Duyệt dòng
	{
		printf(" %i ", i); // In chỉ số dòng của bàn cờ
		for (int j = 0; j < N_COLS; j++) // Duyệt cột
		{
			if (a[i][j] < 0)
				printf("| x ");
			else if (a[i][j] > 0)
				printf("| o ");
			else
				printf("|   ");
		}
		printf("|\n");

		// In đường kẻ ngang của bàn cờ
		printf("   ");
		for (int k = 0; k < N_COLS; k++)
			printf("+---");
		printf("+\n");
	}
	printf("\n");
}

//kiểm tra xem đã có ai thắng hay chưa
//sẽ cải tiến để có thể mở rộng lên sau
int check(int  a[][N_COLS])
{
	if (a[0][0] == a[0][1] && a[0][1] == a[0][2] && (a[0][0] != 0))
		return a[0][0];

	else if (a[1][0] == a[1][1] && a[1][1] == a[1][2] && (a[1][0] != 0))
		return a[1][0];

	else if (a[2][0] == a[2][1] && a[2][1] == a[2][2] && (a[2][0] != 0))
		return a[2][0];

	else if (a[0][0] == a[1][1] && a[1][1] == a[2][2] && (a[0][0] != 0))
		return a[0][0];

	else if (a[2][0] == a[1][1] && a[1][1] == a[0][2] && (a[2][0] != 0))
		return a[2][0];

	else if (a[0][0] == a[1][0] && a[1][0] == a[2][0] && (a[0][0] != 0))
		return a[0][0];

	else if (a[0][1] == a[1][1] && a[1][1] == a[2][1] && (a[0][1] != 0))
		return a[0][1];

	else if (a[0][2] == a[1][2] && a[1][2] == a[2][2] && (a[0][2] != 0))
		return a[0][2];

	else if (check_draw(a) == 1)
		return -2;
	else
		return  0;

}

//kiểm tra hòa
int check_draw(int a[][N_COLS])
{
	int i, j, sum = 0;
	for (i = 0; i < N_COLS; i++)
		for (j = 0; j < N_ROWS; j++)
		{
			if (a[i][j] == 0) return 0;
		}
	return 1;
}

//lượt của người chơi
void player_turn(int a[][N_COLS])
{
	print_board(a);
	int x, y;
	do
	{
		printf("X turn, please enter row value and then, collum value: \n");
		scanf("%i %i", &x, &y);
	} while ((x>2) || (x<0) || (y > 2) || (y < 0) || (a[x][y] != 0)); 
	a[x][y] = -1;
}

//lượt của máy
void AI_turn(int a[][N_COLS])
{
	int moveX = -1,	moveY = -1;
	int score = -2;
	int i, j;

	for (i = 0; i < N_ROWS; i++)
		for (j = 0; j < N_COLS; j++)
		{
			if (a[i][j] == 0) 
			{
				a[i][j] = 1;
				int tScore = -minimax(a, -1);
				a[i][j] = 0;
				if (tScore > score) 
				{
					score = tScore;
					moveX = i;
					moveY = j;
				}
			}
		}
	a[moveX][moveY] = 1;
}

//thuật toán minimax
int minimax(int a[][N_COLS], int cPlayer)
{
	int win = check(a); //kiểm tra trạng thái bàn cờ
	if ((win != 0) && (win != -2))
		return win*cPlayer; //nếu đã đạt trạng thái kết thúc thì trả về số điểm của trạng thái
	int possible_win = -1;;
	int score = -2;
	int i, j;
	for (i = 0; i < N_ROWS; i++)
		for (j = 0; j < N_COLS; j++)
		{
			if (a[i][j] == 0)
			{
				a[i][j] = cPlayer; //đi thử
				int bestScore = -minimax(a, cPlayer*-1); //giả định lượt đi của người chơi còn lại, coi như nước đi của họ là tối ưu trong trạng thái bàn cờ được đưa vào
				if (bestScore > score)
				{
					score = bestScore; //điểm của người chơi khi đi nước này
					possible_win = 1; //có khả năng thắng hoặc hòa
				}
				a[i][j] = 0; //trả lại trạng thái như lúc đầu
			}
		}
	if (possible_win == -1) return 0; //nước đi tồi => trả về 0 điểm
	return score;
}
