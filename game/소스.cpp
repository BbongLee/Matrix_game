#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <thread>
using namespace std;
#define LET 30
#define TM 350 //0.35초
#define ENE 50

void gotoxy(int x, int y) {
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
} //좌표이동

class User {
	int x, y;
	char ch;
public:
	User() {
		x = 20;
		y = 30;
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
  //
class Alpha {
private:
	char lett; //알파벳
	int aX, aY; //좌표값
	int direc;//동서남북 방향 생성 후 어디방향으로 나갈 건지?!
	//int speed;
	
public:
	Alpha() {
		char spaL[] = { '@','#','%','=','+','~' };
		srand((unsigned int)time(NULL));

		aX = (rand()) % 125;
		aY = (rand()) % 40;
		direc = (rand()) % 4;
		switch ((rand()) % 4) {
		case 0: lett = (rand()) % 10 + 48; break; //0~9까지의 숫자
		case 1: lett = spaL[(rand()) % 6]; break; //spaL배열안의 문자
		case 2: lett = (rand()) % 26 + 65; break; //대문자
		case 3: lett = (rand()) % 26 + 97; break; //소문자
		}
	}
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
	void set_lett(char _lett) {
		lett = _lett;
	}
	void set_direc(int _direc) {
		direc = _direc;
	}
	void print_letter() {
		gotoxy(aX, aY);
		cout << lett;
	}
	void move_letter() {
		switch (direc) {
		case 0:
			//동쪽으로
			cout << "동쪽";
			set_aX(0); //0으로 초기화!
			while (aX <= 125) { //-----> y좌표 그대로, x좌표 움직임
				gotoxy(aX, aY);
				aX++;
			}
			break;
		case 1:
			//서
			cout << "서쪽";
			aX = 125; //125으로 초기화!
			while (aX >= 0) { //-----> y좌표 그대로, x좌표 움직임
				gotoxy(aX, aY);
				cout << lett;
				Sleep(TM);
				gotoxy(aX, aY);
				cout << " ";
				aX--;
			}
			break;
		case 2:
			//남
			cout << "남쪽";
			aY = 0; //위에서아래로 
			while (aY <= 40) { //-----> X좌표 그대로, Y좌표 움직임
				gotoxy(aX, aY);
				cout << lett;
				Sleep(TM);
				gotoxy(aX, aY);
				cout << " ";
				aY++;
			}
			break;
		case 3:
			//북
			cout << "북쪽";
			aY = 40; //아래서 위로 
			while (aY >= 0) { //-----> X좌표 그대로, Y좌표 움직임
				gotoxy(aX, aY);
				cout << lett;
				Sleep(TM);
				gotoxy(aX, aY);
				cout << " ";
				aY--;
			}
			break;
		default:
			cout << "오잉 방향할당이 안되었다니 말이 안돼....일럴쑤 없떠..." << endl;
			break;

		}//switch 

	}//printletter


};

class realGame {
private:
	Alpha ap[ENE]; //적군 50!
	User u;
public:
	realGame() {
		for (int i = 0; i < ENE; i++) {
			ap[i].print_letter();
		}
		u.print_user();
	}

	void gameStart() {
		system("cls");
		while (true) {
			for (int i = 0; i < ENE; i++) {
				ap[i].print_letter();	
			}
			for (int i = 0; i < ENE; i++) {
				ap[i].move_letter();
			}
		}

	}
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
			system("cls");
			rg.gameStart();
		}break;
		case 2: {
			system("cls");
		}break;
		case 3: {
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