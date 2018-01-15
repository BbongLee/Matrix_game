#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <thread>
using namespace std;
#define COLS 125
#define LOWS 40
#define UX 3 //위쪽 윗부분 x좌표
#define UY 1
#define LX 3 //왼쪽 
#define LY 3
#define DX // 아래쪽
#define DY
#define RX //오른쪽
#define RY

#define TM 20 //0.03초
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

class User {
	int x, y;
	char ch;//입력받을
	int time;
	int score;
public:
	User() {
		x = 20;
		y = 30;
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
	//void User::user_print();
};//user class



class Alpha {
private:
	char lett; //알파벳
	int aX, aY; //좌표값
	int direc;//동서남북 방향 생성 후 어디방향으로 나갈 건지?!
			  //int speed;
public:
	Alpha() {
		aX = rand() % 125; //X좌표 초기값
		aY = rand() % 40; //Y좌표 초기값
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

};


class MERGE {
public:
	Alpha ap[ENE]; //적군
	User us;
	char ch;
	void user_move() {
		ch = getch();
		switch (ch)
		{
		case 72: //상
			if (us.get_y() > 0) {
				us.set_y(us.get_y() - 1);
			
			}
				break;
		case 80: //하
			if (us.get_y() < 24) us.set_y(us.get_y() + 1);
			break;
		case 75: //좌
			if (us.get_x() > 0) us.set_x(us.get_x() - 1);
			break;
		case 77: //우
			if (us.get_x() < 79) us.set_x(us.get_x() + 1);
			break;
		}
	}
	void gameStart() {
		while (true) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			for (int i = 0; i < ENE; i++) {
				gotoxy(ap[i].get_aX(), ap[i].get_aY());
				switch (ap[i].get_direc()) {
				case 0: //동
						//cout << "동";
					cout << " ";
					ap[i].set_aX(ap[i].get_aX() - 1);
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					if ((ap[i].get_aX() >= COLS) || (ap[i].get_aX() <= 0) || 
						(ap[i].get_aY() >= LOWS) || (ap[i].get_aY() <= 0)) {
						ap[i].set_aX(rand() % 125); ap[i].set_aY(rand() % 40);
						i--;
					}//reset

					//ap[i].set_aX(ap[i].get_aX() + 2); // ->동쪽으로 좌표이동
					break;
				case 1://서
					   //cout << "서";
					cout << " ";
					ap[i].set_aX(ap[i].get_aX() + 1);
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					cout << " ";
					ap[i].set_aX(ap[i].get_aX() - 2); // <-서쪽
					break;
				case 2://남
					   //cout << "남";
					cout << " ";
					ap[i].set_aY(ap[i].get_aY() - 1);
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					cout << " ";
					ap[i].set_aY(ap[i].get_aY() + 2); // ↓남쪽
					break;
				case 3://북
					   //cout << "북";
					cout << " ";
					ap[i].set_aY(ap[i].get_aY() + 1);
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					cout << " ";
					ap[i].set_aY(ap[i].get_aY() - 2); // ↑북쪽
					break;
				}//switch direc
				Sleep(TM);
				if ((ap[i].get_aX() > COLS) || (ap[i].get_aX()< 0) ||
					(ap[i].get_aY() > LOWS) || (ap[i].get_aY() < 0)) {
					ap[i].set_aX(rand() % 125); ap[i].set_aY(rand() % 40);
					i--;
				}//reset
				cout << (char)ap[i].get_lett(); //뿌리기
			}//for 문자 발생/움직이기
			
			 //user 공간
			if (kbhit())
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				gotoxy(us.get_x(), us.get_y());
				cout << "&";
				user_move();
				gotoxy(us.get_x(), us.get_y());
				cout << " ";  //잔상x
			}
		}//while
	}//gameStart()
};

void howTo() {
	cout << "게임 방법 소개" << endl;
	cout << "점검중입니다♥" << endl << "다음에 또 오세요!!!!" << endl;
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
	MERGE mg;
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