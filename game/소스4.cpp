#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <thread>
using namespace std;
#define COLS 125
#define LOWS 40

#define TM 10 //0.03초
#define ENE 50 //enemy : Letter

//PROTOTYPE
void gotoxy(int x, int y);
//void user_move();
void index();
void gameStart();
void howTo();
void ranking();

void gotoxy(int x, int y) {
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
} //좌표이동

void SetCursor(bool bVisible)
{
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = bVisible; // true 보임, false 안보임
	ConsoleCursor.dwSize = 1; // 커서사이즈
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor); // 설정
}

class User {
	int x, y;
	char ch;//입력받을
	int time;
	int score;
public:
	User() {
		x = 50;
		y = 25;
	}
	int get_x()
	{
		return x;
	}
	int get_y()
	{
		return y;
	}
	void set_x(int _x)
	{
		x = _x;
	}
	void set_y(int _y)
	{
		y = _y;
	}
};//user class

class Alpha {
private:
	char lett; //알파벳
	int aX, aY; //좌표값
	int direc;//동서남북 방향 생성 후 어디방향으로 나갈 건지?!
			  //int speed;
public:
	Alpha() {
		aX = rand() % 76 + 4; //X좌표 초기값
		aY = rand() % 33 + 2; //Y좌표 초기값
		direc = rand() % 4;
		char spaL[] = { '@','#','%','=','+','~' };
		switch (rand() % 6) {
		case 0: lett = rand() % 10 + 48; break; //0~9까지의 숫자
		case 1: lett = spaL[rand() % 6]; break; //spaL배열안의 문자
		case 2:case 4: lett = rand() % 26 + 65; break; //대문자
		case 3:case 5: lett = rand() % 26 + 97; break; //소문자
		}
	}//alpha() -> 문자객체 생성!

	int get_aX()
	{
		return aX;
	}
	int get_aY()
	{
		return aY;
	}
	int get_lett() {
		return lett;
	}
	int set_lett(char _lett) {
		lett = _lett;
	}
	int get_direc() {
		return direc;
	}
	void set_aX(int _aX)
	{
		aX = _aX;
	}
	void set_aY(int _aY)
	{
		aY = _aY;
	}
	void eraser_lett() {
		gotoxy(aX, aY);
		cout << " ";
	}

};

class Merge {
public:
	Alpha ap[ENE];//적군
	User us;
	char ch;
	void gameStart() {
		//125, 40
		for (int i = 0; i < 40; i++) { //가로(위) 2,2 3,2,4,2 
			gotoxy(2 + 2 * i, 1);
			cout << "▧";
		}
		for (int i = 0; i < 35; i++) { //세로(양옆) 2, 2, 2,3, 2,4,
			gotoxy(2, 2 + i);
			cout << "▧";
			gotoxy(82, 2 + i);
			cout << "▧";
		}
		for (int i = 0; i < 40; i++) { //가로(아래)
			gotoxy(2 + 2 * i, 37);
			cout << "▧";
		}
		//cout << "    ▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧▧" << endl;
		//cout << "    ▧    ▧" << endl;
		//cout << endl;
		clock_t begin, end;
		begin = clock();        // 시간설정

		for (int i = 0; i < ENE; i=i+4) {
			switch (ap[i].get_direc()) {
			case 0: //동
					//방향확인을 위한 색 추가! 예쁜걸?
				ap[i].set_aX(2);
				break;
			case 1: //서
				ap[i].set_aX(82);
				break;
			case 2: //남
				ap[i].set_aY(2);
				break;
			case 3: //북
				ap[i].set_aY(37);
				break;
			}//switch 초기값 구하기
		}//for

		while (true) {
			SetCursor(false);
			
			//user 공간
			if (kbhit())
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				gotoxy(us.get_x(), us.get_y());
				cout << " ";  //잔상x
				switch (getch())
				{
				case 72: //상
					if (us.get_y() <= 0) break;
					else us.set_y(us.get_y() - 1);
					break;
				case 80: //하
					if (us.get_y() >= 40) break;
					else us.set_y(us.get_y() + 1);
					break;
				case 75: //좌
					if (us.get_x() <= 0) break;
					else us.set_x(us.get_x() - 1);
					break;
				case 77: //우
					if (us.get_x() >= 125) break;
					else us.set_x(us.get_x() + 1);
					break;
				}
				gotoxy(us.get_x(), us.get_y());
				cout << "♥";
			}//user move
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			for (int i = 0; i < ENE; i++) {
				ap[i].eraser_lett();//지우기
				switch (ap[i].get_direc()) {
				case 0: //동 //->
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					//방향확인을 위한 색 추가! 예쁜걸?
					ap[i].set_aX(ap[i].get_aX() + 1); 
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					break;
				case 1: //서 <-
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
					ap[i].set_aX(ap[i].get_aX() - 1);
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					break;
				case 2: //남 ↓
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
					ap[i].set_aY(ap[i].get_aY() + 1);
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					break;
				case 3: //북 ↑
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					ap[i].set_aY(ap[i].get_aY() - 1);
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					break;
				}//switch direct
				if ((ap[i].get_aX() > 80) || (ap[i].get_aX() < 4) ||
					(ap[i].get_aY() > 36) || (ap[i].get_aY() < 2)) {
					ap[i].set_aX(rand() % 80); ap[i].set_aY(rand() % 37);
					i--;
				}// 범위 넘어가면 reset
				gotoxy(ap[i].get_aX(), ap[i].get_aY());
				cout << (char)ap[i].get_lett(); //알파벳 뿌리기
				Sleep(TM);
			}//for 문자 이동
			
			
		}//while

		for (int i = 0; i<30; i++)
		{
			if ((us.get_x() == ap[i].get_aX()) && (us.get_y() == ap[i].get_aY()))
			{
				cout << "죽음 ㅠㅠ" << endl;
				exit(1);
			}
		}//맞았을때?

		end = clock();          // 시간설정
		cout << "수행시간 : " << ((end - begin) / CLOCKS_PER_SEC) << endl;
	}//void gamestart();
};

void howTo() {
	//cout << "게임 방법 소개" << endl;
	
	//cout << "점검중입니다♥" << endl << "다음에 또 오세요!!!!" << endl;
	
}//howTo()

void ranking() {
	cout << "당신의 점수는 몇등일까요?" << endl;
	cout << "점검중입니다♥" << endl;
}//ranking()

 //게임메뉴
 //랭킹보기
 // >>화살표 상하 키보드로!

void index() {
	system("cls");
	cout << "\n\n" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "          ■▒            ■▒        ■▒      ■■■■■■■▒   ■■■■■▒      ■■■▒   ■▒      ■▒" << endl;
	cout << "          ■■▒        ■■▒       ■■▒     ▒▒▒■▒▒▒▒   ■▒▒▒▒■▒      ■▒      ■▒    ■▒ " << endl;
	cout << "          ■▒■▒    ■▒■▒      ■▒■▒          ■▒         ■▒      ■▒      ■▒       ■▒ ■▒   " << endl;
	cout << "          ■▒  ■▒■▒  ■▒     ■▒  ■▒         ■▒         ■■■■■▒        ■▒         ■■▒" << endl;
	cout << "          ■▒    ■▒    ■▒    ■■■■■▒        ■▒         ■▒▒▒▒■▒      ■▒        ■▒ ■▒" << endl;
	cout << "          ■▒     ▒     ■▒   ■▒▒▒▒■▒       ■▒         ■▒       ■▒     ■▒      ■▒    ■▒ " << endl;
	cout << "          ■▒            ■▒  ■▒        ■▒      ■▒         ■▒        ■▒  ■■■▒   ■▒      ■▒" << endl;
	cout << "\n\n" << endl;
}
void Menu() {
	index();
	int menu_choi; //메뉴고르기
	Merge mg;
	srand((unsigned int)time(NULL));
	while (true) {
		gotoxy(50, 25);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "1. 게임시작";
		gotoxy(50, 27);
		cout << "2. 게임방법";
		gotoxy(50, 29);
		cout << "3. 랭킹보기";

		gotoxy(50, 30);
		cout << "====================\n\n" << endl;
		gotoxy(50, 31);
		cout << "번호를 입력해 주세요 >>";
		cin >> menu_choi;

		switch (menu_choi) {
		case 1: {
			cout << "게임시작";
			system("cls");
		}return mg.gameStart();
		case 2: {
			cout << "게임방법";
			system("cls");
		}return howTo();
		case 3: {
			cout << "랭킹보기";
			system("cls");
		}return ranking();
		default: {
			cout << "다시 입력해주세요!!" << endl;
			break;
		}
		}//switch

		
	}//while
}


int main() {
	system("mode con cols=125 lines=40"); //cols = 칸/행 (가로)  lines = 줄/열 (세로)
										  //first();
	Menu();


	//스레드 처리 부분 / 움직이면서 총 쏘기
	//움직이면서 총 맞으면 죽기
}