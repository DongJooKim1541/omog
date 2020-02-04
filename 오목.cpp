#include <stdio.h>//콘솔입출력 라이브러리
#include <string.h>//문자열라이브러리
#include <time.h>//시간라이브러리,랜덤함수 사용시 필요
#include <stdlib.h>//c언어 표준라이브러리,난수함수,문자열함수등 포함
#include <windows.h>//슬립,콘솔창 조절등
#include <conio.h>//kbhit등 입출력관련
#define X_SIZE 15
#define Y_SIZE 15
#define NAME 50

void gotoxy(int x, int y);
void gotoxy2(int x, int y);
int make_board();
int push_keybord(int*x, int*y);
int game_victory(int board[Y_SIZE][X_SIZE], int *x, int *y, int now_turn);


/*메인함수*/
int main() {
	/*콘솔크기 조정.XXXX 지우고 가로크기입력. 크기1은 영문자 하나의 가로길이. YYYY 지우고 세로크기 입력. 1은 한 줄을 의미.*/
	system("mode con: cols=100 lines=35");
	/*커서없애기.*/
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	int board[Y_SIZE][X_SIZE];
	int x=0, y=0;
	int now_turn = 1;
	
	gotoxy(45, 16);

	Sleep(500);
	printf("오 ");
	Sleep(500);
	printf("목 ");	
	Sleep(500);
	printf("게 ");
	Sleep(500);
	printf("임 \n");

	/*아무키나 누르면 넘긴다.*/
	while (_kbhit()) _getch();
	Sleep(1000);
	gotoxy(37, 20);
	printf("아무 키나 누르면 시작합니다!");
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
					printf("○");
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
					printf("●");
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
			printf("흑돌이 승리하였습니다.");
		}
		else {
			printf("백돌이 승리하였습니다.");
		}
		Sleep(5000);
		}
	return 0;
}//메인 끝남


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
		puts("2x2보다 작은 오목판은 그릴 수 없습니다.");
		return 1;
	}


	for (j = 0; j < X_SIZE; j++) {
		if (j == 0) {
			printf_s("┌─");
		}
		else if (j == X_SIZE - 1) {
			printf_s("┐\n");
		}
		else {
			printf_s("┬─");
		}
	}
	for (j = 0; j < X_SIZE; j++) {
		printf_s("│　");
	}
	printf_s("\n");

	for (i = 1; i < Y_SIZE - 1; i++) {
		for (j = 0; j < X_SIZE; j++) {
			if (j == 0) {
				printf_s("├─");
			}
			else if (j == X_SIZE - 1) {
				printf_s("┤\n");
			}
			else {
				printf_s("┼─");
			}
		}
		for (j = 0; j < X_SIZE; j++) {
			printf_s("│　");
		}
		printf_s("\n");
	}
	for (j = 0; j < X_SIZE; j++) {
		if (j == 0) {
			printf_s("└─");
		}
		else if (j == X_SIZE - 1) {
			printf_s("┘\n");
		}
		else {
			printf_s("┴─");
		}
	}

	return 0;
}


int push_keybord(int *x,int *y) {
	while (1) {
		int key;
		key = _getch();
		/*변수값과 일치하는 케이스를 실행. 변수와 맞는 케이스가 없으면default를 실행. 브레이크를 적지않으면 모두 실행한다.*/
		switch (key) {
		case 72://업
			if (*y > 0) {
				gotoxy2((*x), (*y));
				if (*y == Y_SIZE - 1) {
					printf_s("　");
				}
				else {
					printf_s("│");
				}
				(*y)--;
				gotoxy2((*x), (*y));
				printf_s("▲");
			}

			break;
		case 80: //다운
			if (*y < Y_SIZE - 1) {
				gotoxy2((*x), (*y));
				if (*y == Y_SIZE - 1) {
					printf_s("　");
				}
				else {
					printf_s("│");
				}
				(*y)++;
				gotoxy2((*x), (*y));
				printf_s("▲");
			}
			break;

		case 77: //우
			if (*x < X_SIZE - 1) {
				gotoxy2((*x), (*y));
				if (*y == Y_SIZE - 1) {
					printf_s("　");
				}
				else {
					printf_s("│");
				}
				(*x)++;
				gotoxy2((*x), (*y));
				printf_s("▲");
			}
			break;
		case 75: //좌
			if (*x >0) {
				gotoxy2((*x), (*y));
				printf_s("│");
				(*x)--;
				gotoxy2((*x), (*y));
				printf_s("▲");
			}
			break;
		case 13: //엔터
			return 0;
			break;
		}//스위치문종료
	}//와일문종료
}//함수종료

int game_victory(int board[Y_SIZE][X_SIZE], int *x, int *y, int now_turn) {

	int min_x, min_y;
	int max_x, max_y;
	int i, j;
	int count;

	//가로검사
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

	//세로검사
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

	//대각선 주방향 검사
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

	//대각선 역방향 검사
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