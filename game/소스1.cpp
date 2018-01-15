#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <thread>
using namespace std;
#define COLS 125
#define LOWS 40

#define TM 350 //0.35초
#define ENE 5 //enemy -> Letter


void gotoxy(int x, int y) {
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
} //좌표이동

class User {
	int x, y;
	char ch;
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
	void print_user()
	{
		gotoxy(x, y);
		cout << "&";
	}
};//user class

  //문자 랜덤 생성
  //랜덤으로 방향 정해서
  //ㅇ사방에서 나오기()
  //유저 총 닿으면 죽는다()

class Alpha {
private:
	char lett; //알파벳
	int aX, aY; //좌표값
	int direc;//동서남북 방향 생성 후 어디방향으로 나갈 건지?!
			  //int speed;
public:
	Alpha() {
		//char spaL[] = { '@','#','%','=','+','~' };
		//srand((unsigned int)time(NULL));

		aX = rand() % 125;
		aY = rand() % 40;
		direc = rand() % 4;
		//switch (rand() % 4) {
		//case 0: lett = (char)(rand()) % 10 + 48; break; //0~9까지의 숫자
		//case 1: lett = spaL[(rand()) % 6]; break; //spaL배열안의 문자
		//case 2: lett = (char)(rand()) % 26 + 65; break; //대문자
		//case 3: lett = (char)(rand()) % 26 + 97; break; //소문자
		//}
	}//alpha()
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
	//void print_letter() {
	//	gotoxy(aX, aY);
	//	cout << lett;
	//}
	/*
	void move_letter() {
	switch (direc) {
	case 0:
	//cout << "동쪽";
	gotoxy(aX+1, aY);
	break;
	case 1:
	//cout << "서쪽";
	gotoxy(aX-1, aY);
	break;
	case 2:
	//cout << "남쪽";
	gotoxy(aX, aY+1);
	break;
	case 3:
	//cout << "북쪽";
	gotoxy(aX, aY-1);
	break;
	default:
	cout << "오잉 방향할당이 안되었다니 말이 안돼....일럴쑤 없떠..." << endl;
	break;

	}//switch

	}//move
	*/
};

class realGame {
private:
	Alpha ap[ENE]; //적군 50!
	User u;
public:
	realGame() {
		for (int i = 0; i < ENE; i++) {
			gotoxy(ap[i].get_aX(),ap[i].get_aY());
			cout<<ap[i].get_lett();
		}
	}//생성자
	void gameStart() {
		while (true) {
			for (int i = 0; i < ENE; i++) {
				gotoxy(ap[i].get_aX(), ap[i].get_aY());
				cout <<"@";
				Sleep(TM);
				
				switch (ap[i].get_direc()) {
				case 0: //동
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					cout << " ";
					ap[i].set_aX(ap[i].get_aX() + 1); // ->동쪽으로 좌표이동
					break;
				case 1://서
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					cout << " ";
					ap[i].set_aX(ap[i].get_aX() - 1); // <-서쪽으로 좌표이동
					break;
				case 2://남
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					cout << " ";
					ap[i].set_aY(ap[i].get_aY() + 1); // ↓남쪽으로 좌표이동
					break;
				case 3://북
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					cout << " ";
					ap[i].set_aY(ap[i].get_aY() - 1); // ↑북쪽으로 좌표이동
					break;
				}//switch direc

				switch (ap[i].get_direc()) {
				case 0:if (ap[i].get_aX() >= COLS) break;
				case 1:if (ap[i].get_aX() <= 0) break;
				case 2:if (ap[i].get_aY() >= LOWS) break;
				case 3:if (ap[i].get_aY() <= 0) break;
				default: break;
				}//switch
				 //if문으로 종료처리 하기
			}//for
		}//while
	}//Start
};

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
	//cout << "            ▒              ▒     ▒            ▒     ■▒         ■▒       ■▒   ■■■▒   ■▒       ■▒ " << endl;
	cout << "\n\n" << endl;
}
void Menu() {
	index();
	int menu_choi; //메뉴고르기
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
		realGame rg;
		switch (menu_choi) {
		case 1: {
			cout << "게임시작";
			system("cls");
		}return rg.gameStart();
		case 2: {
			cout << "게임방법";
			system("cls");
		}break;
		case 3: {
			cout << "랭킹보기";
			Sleep(1000);
		}break;
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
	Menu(); //GameStart.cpp
			//레벨O, 


			//스레드 처리 부분 / 움직이면서 총 쏘기
			//움직이면서 총 맞으면 죽기
}