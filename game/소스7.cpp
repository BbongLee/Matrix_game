#include <iostream>
#include <fstream>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <thread>
#include "string"

using namespace std;
#define COLS 125
#define LOWS 40

#define TM 1 //0.01초
#define ENE 40 //enemy : Letter

static int score = 0;
//PROTOTYPE
void gotoxy(int x, int y);
//void user_move();
void Menu();
void index();
void gameStart();
void howTo();
void ranking();

class GameObject;
class Merge;

class GameObject {
	int level = 0;

public:

	int tm[3] = { 30, 20, 10 };
	int enemy[3] = { 20, 30, 40 };

	int get_level() {
		return level;
	}
	void set_level(int _level) {
		level = _level;
	}
};

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
	int heart = 5; //생명

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
	int get_heart() {
		return heart;
	}
	void set_heart(int _heart) {
		heart = _heart;
	}
	void showHeart(int heart) {
		for (int i = 0; i < heart; i++) {
			cout << "♥";
		}
	}
	int get_score()
	{
		return score;
	}
	void set_score(int _score)
	{
		score = _score;
	}

};//user class

class Alpha {
private:
	char lett; //알파벳
	int aX, aY; //좌표값
	int direc;//동서남북 방향 생성 후 어디방향으로 나갈 건지?!

public:
	int wait;
	
	Alpha() {
		aX = rand() % 76 + 4; //X좌표 초기값
		aY = rand() % 32 + 2; //Y좌표 초기값
		direc = rand() % 4;
		char spaL[] = { '@','#','%','=','+','~' };
		switch (rand() % 6) {
		case 0: lett = rand() % 10 + 48; break; //0~9까지의 숫자
		case 1: lett = spaL[rand() % 6]; break; //spaL배열안의 문자
		case 2:case 4: lett = rand() % 26 + 65; break; //대문자
		case 3:case 5: lett = rand() % 26 + 97; break; //소문자
		}
		wait = rand() % (ENE * 2);
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
	void alp_move() {
		this->eraser_lett();//남아있는 흔적 지우기
		switch (this->get_direc()) {
		case 0: //동 //->
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			//방향확인을 위한 색 추가! 예쁜걸?
			this->set_aX(this->get_aX() + 1);
			gotoxy(this->get_aX(), this->get_aY());
			break;
		case 1: //서 <-
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			this->set_aX(this->get_aX() - 1);
			gotoxy(this->get_aX(), this->get_aY());
			break;
		case 2: //남 ↓
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
			this->set_aY(this->get_aY() + 1);
			gotoxy(this->get_aX(), this->get_aY());
			break;
		case 3: //북 ↑
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			this->set_aY(this->get_aY() - 1);
			gotoxy(this->get_aX(), this->get_aY());
			break;
		}//switch 
		 //방향에따라 문자 움직이기
		if ((this->get_aX() > 80) || (this->get_aX() < 4) || (this->get_aY() > 36) || (this->get_aY() < 2)) {
			this->set_aX(rand() % 76 + 4); this->set_aY(rand() % 32 + 2);
			score++;
		}// 범위 넘어가면 reset
		gotoxy(this->get_aX(), this->get_aY());
		cout << (char)this->get_lett(); //알파벳 뿌리기
	}


};
class Merge : public GameObject {
public:
	GameObject *go;
	Alpha ap[ENE];//적군
	User us;
	//Bullet bl[ENE];
	char ch;
	char myName[20];
	int myScore = 0;
	int  myTime;
	int key;
	ifstream rd_file;
	ofstream wd_file;
	int b = 0;

	void user_move() {
		//user 공간
		if (kbhit())
		{
			if (us.get_x() > 4 && us.get_x() < 80 && us.get_y() < 36 && us.get_y() > 2) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				gotoxy(us.get_x(), us.get_y());
				cout << " ";  //잔상x
				switch (getch())
				{
				case 72: //상
					if (us.get_y() <= 0) break;
					else us.set_y(us.get_y() - 1);
					key = 72;
					break;
				case 80: //하
					if (us.get_y() >= 40) break;
					else us.set_y(us.get_y() + 1);
					key = 80;
					break;
				case 75: //좌
					if (us.get_x() <= 0) break;
					else us.set_x(us.get_x() - 1);
					key = 75;
					break;
				case 77: //우
					if (us.get_x() >= 125) break;
					else us.set_x(us.get_x() + 1);
					key = 77;
					break;
				}//if for user move
			}
			else {
				gotoxy(us.get_x(), us.get_y());
				cout << " ";  //잔상x
				switch (key) {
				case 72: //상
					us.set_y(us.get_y() + 1);
					break;
				case 80: //하
					us.set_y(us.get_y() - 1);
					break;
				case 75: //좌
					us.set_x(us.get_x() + 1);
					break;
				case 77: //우
					us.set_x(us.get_x() - 1);
					break;
				}
			}
			gotoxy(us.get_x(), us.get_y());
			cout << "★";
		}
	}//user.move();


	void gameStart() {
		system("cls");
		gotoxy(60, 20);
		cout << "이름을 입력해 주세요! : ";
		cin >> myName;
		gameMain();
	}

	void gameMain() {
		system("cls");
		int timeee = 0; //스코어 계산 목적
		int sco;
		//125, 40
		//왼쪽 게임칸
		for (int i = 0; i <= 40; i++) {
			gotoxy(2 + 2 * i, 1);
			cout << "▧";
		}//가로(위) 2,2 3,2,4,2 
		for (int i = 0; i < 35; i++) {
			gotoxy(2, 2 + i);
			cout << "▧";
			gotoxy(82, 2 + i);
			cout << "▧";
		}//세로(양옆) 2, 2, 2,3, 2,4,
		for (int i = 0; i <= 40; i++) {
			gotoxy(2 + 2 * i, 37);
			cout << "▧";
		}//가로(아래)
		 //오른쪽 정보칸
		for (int i = 0; i <= 13; i++) {
			gotoxy(90 + 2 * i, 1);
			cout << "▧";
		}//가로(위) 2,2 3,2,4,2 
		for (int i = 0; i < 35; i++) {
			gotoxy(90, 2 + i);
			cout << "▧";
			gotoxy(116, 2 + i);
			cout << "▧";
		}//세로(양옆) 2, 2, 2,3, 2,4,
		for (int i = 0; i <= 13; i++) {
			gotoxy(90 + 2 * i, 37);
			cout << "▧";
		} //가로(아래)
		clock_t begin, end;
		begin = clock();  // 시간설정
		
		for (int i = 0; i < ENE; i++) {
			switch (ap[i].get_direc()) {
			case 0: //동
				ap[i].set_aX(5);
				break;
			case 1: //서
				ap[i].set_aX(81);
				break;
			case 2: //남
				ap[i].set_aY(3);
				break;
			case 3: //북
				ap[i].set_aY(35);
				break;
			}//switch
		}//for 초기값 구하기

		 //todo : 충돌처리
		while (true) {
			for (int i = 0; i < ENE; i++) {
				SetCursor(false);
				/*
				std::bind(&user_move(), this);
				std::thread t1(user_move); 
				t1.join();
				*/
				user_move();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				for (int i = 0; i < ENE; i++) {
					if (ap[i].wait > 0) {
						ap[i].wait--;
					}
					else {
						ap[i].alp_move();
						if ((us.get_x() == ap[i].get_aX()) && (us.get_y() == ap[i].get_aY())) {
							us.set_heart(us.get_heart() - 1);
							myScore - 10;
							if (us.get_heart() == 0 || myScore < 0) {
								end = clock();
								myTime = ((end - begin) / CLOCKS_PER_SEC);
								return GameOver(myName, myTime, myScore);
							}
						}//user, enemy 충돌처리
						gotoxy(95, 8);
						us.showHeart(us.get_heart());
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
						gotoxy(95, 10);
						cout << "T I M E : " << endl;
						
						end = clock(); //계속 end가 갱신된다
						myTime = ((end - begin) / CLOCKS_PER_SEC);
						gotoxy(105, 10);
						cout << myTime << endl; //시간 호출
												//객체가 한번 나왔다 다시 생성될때 점수++
						myScore = score * 10;
						gotoxy(95, 15);
						cout << "S C O R E : " << endl;
						gotoxy(110, 15);
						cout << myScore << endl; //시간 호출
						Sleep(TM);
					}//else
				}//for 문자 이동
			}//for 랜덤으로 char 나오기 위해!
		}//while


	}//void gamemain();


	void GameOver(char *, int, int) {
		system("cls");
		gotoxy(50, 15);
		cout << "당신은  ,, ,,  죽었어요!" << endl;
		gotoxy(50, 20);
		cout << "   당신의 점수를 파일에 저장합니다 ! ! !" << endl;
		gotoxy(50, 25);
		cout << *myName << "님의 점수는 " << myScore << ",    걸린 시간은 " << myTime << endl;
		gotoxy(50, 27);
		cout <<" 글자 적들을 피하느라 수고했어요!!" << endl;
		gotoxy(50, 28);
		cout << "  다음엔 공격 버전으로 찾아올게요 :) " << endl;
		//파일저장
		// 파일 입력 (쓰기)
		ofstream writeFile("matrixScore.txt", ios_base::app);
		if (writeFile.is_open()) {
			writeFile << *myName << " \t";
			writeFile << myScore << " \t";
			writeFile << myTime << "\n";
			writeFile.close();
		}
		Menu();
	}

};
void showRank() {
	//파일 출력 (읽기)
	// read File
	ifstream openFile("matrixScore.txt");
	if (openFile.is_open()) {
		string line;
		gotoxy(40, 10);
		cout << "이름\t점수\t실행시간";
		int i = 0;
		while (getline(openFile, line)) {
			gotoxy(40, 12+i*2);
			cout << line << endl;
			i++;
		}
		openFile.close();
	}
	else cout << "파일이 없다!" << endl;
	Menu();
}//showRank

void howTo() {
	gotoxy(55, 3);
	cout << "HOW TO PLAY" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	gotoxy(55, 5);
	cout << "the" << endl;
	gotoxy(55, 6);
	cout << "M A T R I X" << endl;
	gotoxy(55, 7);
	cout << "G A M E" << endl;
	gotoxy(55, 8);
	cout << "사 용 설 명 서" << endl;
	gotoxy(25, 11);
	cout << "1. 문자들이 나타난다 ! " << endl;
	gotoxy(25, 13);
	cout << "2. 키보드 ↑ ↓ ← → 를 이용하여 \"나\"를 움직인다. " << endl;
	gotoxy(25, 15);
	cout << "3. 재주껏 문자들을 피해다닌다. 최대한 오래! " << endl;
	gotoxy(25, 19);
	cout << "오래 살아 남을 수 있다면" << endl;
	gotoxy(25, 21);
	cout << "당신은 이미 THE ONE 입니다! (매트릭스 보신 분은 알겠죵...)" << endl;
	Menu();
}//howTo()

void index() {
	system("cls");
	cout << "\n\n\n\n\n\n" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "          ■▒        2   ■▒        ■▒      ■■■■■■■▒   ■■■■■▒      ■■■▒   ■▒      ■▒   " << endl;
	cout << "          ■■▒        ■■▒   5   ■■▒     ▒▒▒■▒▒▒▒   ■▒▒▒▒■▒      ■▒      ■▒    ■▒   " << endl;
	cout << "         ■▒■▒    ■▒■▒      ■▒■▒          ■▒         ■▒      ■▒      ■▒        ■▒ ■▒     " << endl;
	cout << "          ■▒  ■▒■▒  ■▒     ■▒  ■▒   1     ■▒    7    ■■■■■▒        ■▒         ■■▒   " << endl;
	cout << "          ■▒    ■▒    ■▒  e ■■■■■▒        ■▒         ■▒▒▒▒■▒  l   ■▒   e    ■▒ ■▒      " << endl;
	cout << "          ■▒   y ▒     ■▒   ■▒▒▒▒■▒       ■▒  o      ■▒       ■▒     ■▒      ■▒    ■▒  " << endl;
	cout << "          ■▒            ■▒  ■▒        ■▒  b   ■▒         ■▒  n     ■▒  ■■■▒   ■▒  e   ■▒   " << endl;
	cout << "\n\n" << endl;
}
void Menu() {
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
		gotoxy(50, 31);
		cout << "4. 종료";
		gotoxy(50, 33);
		cout << "====================\n\n" << endl;
		gotoxy(50, 35);
		cout << "번호를 입력해 주세요 >>";
		cin >> menu_choi;

		switch (menu_choi) {
		case 1: {
			system("cls");
		}return mg.gameStart();
		case 2: {
			system("cls");
		}return howTo();
		case 3: {
			system("cls");
		}return showRank();
		case 4: 
			exit(0);
		default: {
			cout << "다시 입력해주세요!!" << endl;
			break;
		}
		}//switch
	}//while
}


int main() {
	system("mode con cols=125 lines=40"); //cols = 칸/행 (가로)  lines = 줄/열 (세로)
	srand((unsigned int)time(NULL));
	index();								  //first();
	Menu();

}
