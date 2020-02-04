#include <stdio.h>//�ܼ������ ���̺귯��
#include <string.h>//���ڿ����̺귯��
#include <time.h>//�ð����̺귯��,�����Լ� ���� �ʿ�
#include <stdlib.h>//c��� ǥ�ض��̺귯��,�����Լ�,���ڿ��Լ��� ����
#include <windows.h>//����,�ܼ�â ������
#include <conio.h>//kbhit�� ����°���
#define X_SIZE 15
#define Y_SIZE 15
#define NAME 50

void gotoxy(int x, int y);
void gotoxy2(int x, int y);
int make_board();
int push_keybord(int*x, int*y);
int game_victory(int board[Y_SIZE][X_SIZE], int *x, int *y, int now_turn);


/*�����Լ�*/
int main() {
	/*�ܼ�ũ�� ����.XXXX ����� ����ũ���Է�. ũ��1�� ������ �ϳ��� ���α���. YYYY ����� ����ũ�� �Է�. 1�� �� ���� �ǹ�.*/
	system("mode con: cols=100 lines=35");
	/*Ŀ�����ֱ�.*/
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	int board[Y_SIZE][X_SIZE];
	int x=0, y=0;
	int now_turn = 1;
	
	gotoxy(45, 16);

	Sleep(500);
	printf("�� ");
	Sleep(500);
	printf("�� ");	
	Sleep(500);
	printf("�� ");
	Sleep(500);
	printf("�� \n");

	/*�ƹ�Ű�� ������ �ѱ��.*/
	while (_kbhit()) _getch();
	Sleep(1000);
	gotoxy(37, 20);
	printf("�ƹ� Ű�� ������ �����մϴ�!");
	while (1) {
		if (_kbhit()) {
			_getch();
			break;
		}
	}
	while (1) {
		system("cls");
		int i = 0, j = 0;
		for (i = 0; i < Y_SIZE; i++) {
			for (j = 0; j < X_SIZE; j++) {
				board[i][j] = 0;
			}
		}
		make_board();
		while (1) {
			push_keybord(&x, &y);
			if (now_turn == 1) {
				if (board[y][x] == 0) {
					gotoxy(x * 4, y * 2);
					printf("��");
				}
				board[y][x] = now_turn;
				if (game_victory(board, &x, &y, now_turn)) {
					break;
				}
				now_turn++;
			}
			else {
				if (board[y][x] == 0) {
					gotoxy(x * 4, y * 2);
					printf("��");
				}
				board[y][x] = now_turn;
				if (game_victory(board, &x, &y, now_turn)) {
					break;
				}
				now_turn--;
			}
		
		}

		gotoxy(0, 40);
		if (now_turn == 1) {
			printf("�浹�� �¸��Ͽ����ϴ�.");
		}
		else {
			printf("�鵹�� �¸��Ͽ����ϴ�.");
		}
		Sleep(5000);
		}
	return 0;
}//���� ����


void gotoxy(int x, int y) {
	COORD XY = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
}

void gotoxy2(int x, int y) {
	COORD XY = { x * 4, y * 2 + 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
}

int make_board() {

	int i = 0;
	int j = 0;
	if (Y_SIZE < 2 || X_SIZE < 2) {
		puts("2x2���� ���� �������� �׸� �� �����ϴ�.");
		return 1;
	}


	for (j = 0; j < X_SIZE; j++) {
		if (j == 0) {
			printf_s("����");
		}
		else if (j == X_SIZE - 1) {
			printf_s("��\n");
		}
		else {
			printf_s("����");
		}
	}
	for (j = 0; j < X_SIZE; j++) {
		printf_s("����");
	}
	printf_s("\n");

	for (i = 1; i < Y_SIZE - 1; i++) {
		for (j = 0; j < X_SIZE; j++) {
			if (j == 0) {
				printf_s("����");
			}
			else if (j == X_SIZE - 1) {
				printf_s("��\n");
			}
			else {
				printf_s("����");
			}
		}
		for (j = 0; j < X_SIZE; j++) {
			printf_s("����");
		}
		printf_s("\n");
	}
	for (j = 0; j < X_SIZE; j++) {
		if (j == 0) {
			printf_s("����");
		}
		else if (j == X_SIZE - 1) {
			printf_s("��\n");
		}
		else {
			printf_s("����");
		}
	}

	return 0;
}


int push_keybord(int *x,int *y) {
	while (1) {
		int key;
		key = _getch();
		/*�������� ��ġ�ϴ� ���̽��� ����. ������ �´� ���̽��� ������default�� ����. �극��ũ�� ���������� ��� �����Ѵ�.*/
		switch (key) {
		case 72://��
			if (*y > 0) {
				gotoxy2((*x), (*y));
				if (*y == Y_SIZE - 1) {
					printf_s("��");
				}
				else {
					printf_s("��");
				}
				(*y)--;
				gotoxy2((*x), (*y));
				printf_s("��");
			}

			break;
		case 80: //�ٿ�
			if (*y < Y_SIZE - 1) {
				gotoxy2((*x), (*y));
				if (*y == Y_SIZE - 1) {
					printf_s("��");
				}
				else {
					printf_s("��");
				}
				(*y)++;
				gotoxy2((*x), (*y));
				printf_s("��");
			}
			break;

		case 77: //��
			if (*x < X_SIZE - 1) {
				gotoxy2((*x), (*y));
				if (*y == Y_SIZE - 1) {
					printf_s("��");
				}
				else {
					printf_s("��");
				}
				(*x)++;
				gotoxy2((*x), (*y));
				printf_s("��");
			}
			break;
		case 75: //��
			if (*x >0) {
				gotoxy2((*x), (*y));
				printf_s("��");
				(*x)--;
				gotoxy2((*x), (*y));
				printf_s("��");
			}
			break;
		case 13: //����
			return 0;
			break;
		}//����ġ������
	}//���Ϲ�����
}//�Լ�����

int game_victory(int board[Y_SIZE][X_SIZE], int *x, int *y, int now_turn) {

	int min_x, min_y;
	int max_x, max_y;
	int i, j;
	int count;

	//���ΰ˻�
	min_x = (*x) - 4;
	if (min_x < 0) {
		min_x = 0;
	}
	max_x = (*x) + 4;
	if (max_x >= X_SIZE) {
		max_x = X_SIZE - 1;
	}

	count = 0;
	for (i = min_x; i <= max_x; i++) {
		if (board[*y][i] == now_turn) {
			count++;
		}
		else {
			count = 0;
		}
		if (count == 5) {
			return 1;
		}
	}

	//���ΰ˻�
	min_y = (*y) - 4;
	if (min_y < 0) {
		min_y = 0;
	}
	max_y = (*y) + 4;
	if (max_y >= Y_SIZE) {
		max_y = Y_SIZE - 1;
	}
	count = 0;
	for (i = min_y; i <= max_y; i++) {
		if (board[i][*x] == now_turn) {
			count++;
		}
		else {
			count = 0;
		}
		if (count == 5) {
			return 1;
		}
	}

	//�밢�� �ֹ��� �˻�
	min_x = (*x) - 4;
	min_y = (*y) - 4;
	while (min_x < 0 || min_y<0) {
		min_x++;
		min_y++;
	}

	max_x = (*x) + 4;
	max_y = (*y) + 4;
	while (max_x >= X_SIZE || max_y >= Y_SIZE) {
		max_x--;
		max_y--;
	}

	for (i = min_y, j = min_x; i <= max_y, j <= max_x; i++, j++) {
		if (board[i][j] == now_turn) {
			count++;
		}
		else {
			count = 0;
		}
		if (count == 5) {
			return 1;
		}
	}

	//�밢�� ������ �˻�
	min_x = (*x) + 4;
	min_y = (*y) - 4;
	while (min_x >= X_SIZE || min_y<0) {
		min_x--;
		min_y++;
	}
	max_x = (*x) - 4;
	max_y = (*y) + 4;
	while (max_x <0 || max_y >= Y_SIZE) {
		max_x++;
		max_y--;
	}
	for (i = min_y, j = min_x; i <= max_y, j >= max_x; i++, j--) {
		if (board[i][j] == now_turn) {
			count++;
		}
		else {
			count = 0;
		}
		if (count == 5) {
			return 1;
		}
	}
	return 0;

}