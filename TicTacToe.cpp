//Phạm Hoàng Anh Tuấn
//MSSV 1753123

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <cstdlib> //để sử dụng lệnh xóa màn hình console và random
#include <time.h> //dùng để tạo seed random
#define N_ROWS 3
#define N_COLS 3


void print_board(int a[][N_COLS], char Player, char Com);
int check(int a[][N_COLS]);
int check_draw(int a[][N_COLS]);
void player_turn(int a[][N_COLS]);
void AI_turn(int a[][N_COLS]);
int minimax(int a[][N_COLS], int cPlayer);
void play(int a[][N_COLS], char Player, char Com);
void X_or_O(char *Player, char *Com);
int main()
{
	char Player, Com;
	X_or_O(&Player, &Com);
	srand(time(NULL));
	static int a[N_ROWS][N_COLS]; //khởi tạo mảng
	play(a, Player, Com); //hàm mở game
}

void play(int a[][N_COLS], char Player, char Com)
{
	int winner;
	printf("You are [%c] player\n", Player);
	do
	{
		AI_turn(a);
		winner = check(a);
		if (winner != 0)
		{
			system("cls");
			print_board(a, Player, Com);
			if (winner == -2)
			{
				printf("\Draw\n\n0\n");
				return;
			}
			printf("\nAI is the winner\n\n1\n");
			return;
		}
		print_board(a, Player, Com);
		player_turn(a);
		winner = check(a);
		if (winner != 0)
		{
			system("cls");
			print_board(a, Player, Com);
			if (winner == -2)
			{
				printf("\nhoa\n");
				printf("\n0\n");
				return;
			}
			printf("\nHuman is The Winner (you've cheated, right ? admit it =.=)\n\n-1\n");
			return;
		}
		system("cls");
	} 
	while (true);
}
void print_board(int a[][N_COLS], char Player, char Com)
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
			if (a[i][j] > 0)
				printf("| %c ", Com);
			else if (a[i][j] < 0)
				printf("| %c ", Player);
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
	int x, y;
	do
	{
		printf("Player's turn, please enter row value and then, collum value: \n");
		scanf("%i %i", &x, &y);
	} while ((x>2) || (x<0) || (y > 2) || (y < 0) || (a[x][y] != 0)); 
	a[x][y] = -1;
}

//lượt của máy
void AI_turn(int a[][N_COLS])
{
	int moveX, moveY;
	int i, j;
	int score = 0;
	int list_X[30]; //lưu trữ vị trí hàng các nước đi hợp lệ
	int list_Y[30]; //lưu trữ vị trí cột các nước đi hợp lệ
	int counter = 0;
	int flag = 0;
	for (i = 0; i < N_ROWS; i++)
		for (j = 0; j < N_COLS; j++)
		{
			if (a[i][j] == 0) 
			{
				a[i][j] = 1;
				int tScore = -minimax(a, -1);
				a[i][j] = 0;
				if (tScore >= score)
				{
					score = tScore;
					counter++;
					list_X[counter - 1] = i;
					list_Y[counter - 1] = j;
				}
			}
		}
	flag = rand() % counter; //biến chọn random nước đi
	moveX = list_X[flag];
	moveY = list_Y[flag];
	a[moveX][moveY] = 1;
}

//thuật toán minimax
int minimax(int a[][N_COLS], int cPlayer) //cPlayer = current player
{
	int win = check(a); //kiểm tra trạng thái bàn cờ
	if ((win != 0) && (win != -2))
		return win*cPlayer; //nếu đã đạt trạng thái kết thúc thì trả về số điểm của trạng thái
	int possible_win = -1;
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
	if (possible_win == -1) return 0; //không có khả năng thắng với nước đi này
	return score;
}

void X_or_O(char *Player, char *Com)
{
	do
	{
		printf("[x] or [o] ?\n");
		scanf("%c", Player);
	} while (((*Player) != 'x') && ((*Player) != 'o'));
	if ((*Player) == 'x') ((*Com) = 'o');
	else ((*Com) = 'x');
}