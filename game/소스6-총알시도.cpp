#include <iostream>
#include <fstream>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <thread>

using namespace std;
#define COLS 125
#define LOWS 40

#define TM 30 //0.03��
#define ENE 10 //enemy : Letter

//PROTOTYPE
void gotoxy(int x, int y);
//void user_move();
void index();
void gameStart();
void howTo();
void ranking();

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
} //��ǥ�̵�

void SetCursor(bool bVisible)
{
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = bVisible; // true ����, false �Ⱥ���
	ConsoleCursor.dwSize = 1; // Ŀ��������
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor); // ����
}

class User {
	int x, y;
	char ch;//�Է¹���
	int time;
	int score;
	int heart = 5; //����

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
			cout << "��";
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
	char lett; //���ĺ�
	int aX, aY; //��ǥ��
	int direc;//�������� ���� ���� �� ���������� ���� ����?!

public:
	int wait;
	Alpha() {
		aX = rand() % 76 + 4; //X��ǥ �ʱⰪ
		aY = rand() % 32 + 2; //Y��ǥ �ʱⰪ
		direc = rand() % 4;
		char spaL[] = { '@','#','%','=','+','~' };
		switch (rand() % 6) {
		case 0: lett = rand() % 10 + 48; break; //0~9������ ����
		case 1: lett = spaL[rand() % 6]; break; //spaL�迭���� ����
		case 2:case 4: lett = rand() % 26 + 65; break; //�빮��
		case 3:case 5: lett = rand() % 26 + 97; break; //�ҹ���
		}
		wait = rand() % (ENE * 2);
	}//alpha() -> ���ڰ�ü ����!

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
		this->eraser_lett();//�����ִ� ���� �����
		switch (this->get_direc()) {
		case 0: //�� //->
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			//����Ȯ���� ���� �� �߰�! ���۰�?
			this->set_aX(this->get_aX() + 1);
			gotoxy(this->get_aX(), this->get_aY());
			break;
		case 1: //�� <-
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			this->set_aX(this->get_aX() - 1);
			gotoxy(this->get_aX(), this->get_aY());
			break;
		case 2: //�� ��
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
			this->set_aY(this->get_aY() + 1);
			gotoxy(this->get_aX(), this->get_aY());
			break;
		case 3: //�� ��
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			this->set_aY(this->get_aY() - 1);
			gotoxy(this->get_aX(), this->get_aY());
			break;
		}//switch 
		 //���⿡���� ���� �����̱�
		if ((this->get_aX() > 80) || (this->get_aX() < 4) || (this->get_aY() > 36) || (this->get_aY() < 2)) {
			this->set_aX(rand() % 76 + 4); this->set_aY(rand() % 32 + 2);
		}// ���� �Ѿ�� reset
		gotoxy(this->get_aX(), this->get_aY());
		cout << (char)this->get_lett(); //���ĺ� �Ѹ���
	}


};

class Bullet {
	int bx, by; //�Ѿ� 
	
public:
	boolean bok; //�Ѿ� ���Ƽ� ������ �Ǵ�?
	Bullet() {
		bok = true;
	}
	int get_bx()
	{
		return bx;
	}
	int get_by()
	{
		return by;
	}
	void set_bx(int _bx)
	{
		bx = _bx;
	}
	void set_by(int _by)
	{
		by = _by;
	}
	void eraser_bull() {
		gotoxy(bx, bx);
		cout << " ";
	}
	void bullet_move(int key) {
		//user��ǥ ���� �� ���ĺ�ó�� �����̱�
		this->eraser_bull();
		switch (key) {
		case 77: //�� //->
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			this->set_bx(this->get_bx() + 1);
			break;
		case 75: //�� <-
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			this->set_bx(this->get_bx() - 1);
			break;
		case 80: //�� ��
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
			this->set_by(this->get_by() + 1);
			break;
		case 72: //�� ��
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			this->set_by(this->get_by() - 1);
			break;
		}//switch 
		gotoxy(this->get_bx(), this->get_by());//���⿡���� ���� �����̱�
		cout << "*";
	}//bullet_move

};//bullet class

class Merge : public GameObject {
public:
	GameObject *go;
	Alpha ap[ENE];//����
	User us;
	Bullet bl[ENE];
	char ch;
	char myName[20];
	int myScore=0;
	int  myTime;	
	int key;
	ifstream rd_file;
	ofstream wd_file;
	int b = 0;

	void user_move() {
		//user ����
		if (kbhit())
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			gotoxy(us.get_x(), us.get_y());
			cout << " ";  //�ܻ�x
			switch (getch())
			{
			case 72: //��
				if (us.get_y() <= 0) break;
				else us.set_y(us.get_y() - 1);
				key = 72;
				break;
			case 80: //��
				if (us.get_y() >= 40) break;
				else us.set_y(us.get_y() + 1);
				key = 80;
				break;
			case 75: //��
				if (us.get_x() <= 0) break;
				else us.set_x(us.get_x() - 1);
				key = 75;
				break;
			case 77: //��
				if (us.get_x() >= 125) break;
				else us.set_x(us.get_x() + 1);
				key = 77;
				break;

			case 50: //space bar -> �ѽ�� !!!
				//thread�� �̿��� �Ѿ� �����

				while (bl[b].bok==true) {// == bl[b].bok
					bl[b].bullet_move(key);
					if ((bl[b].get_bx() > 80) || (bl[b].get_bx() < 4) || (bl[b].get_by() > 36) || (bl[b].get_by() < 2)) {
						//bl[b]����
						bl[b].bok = false;
					}// ���� �Ѿ�� ���߱�
				}//while
				b++;
				break;
			}//if for user move

			gotoxy(us.get_x(), us.get_y());
			cout << "��";
		}
	}//user.move();

	

	void gameStart() {
		system("cls");
		gotoxy(60, 20);
		cout << "�̸��� �Է��� �ּ���! : ";
		cin >> myName;
		gameMain();
	}

	void gameMain() {
		system("cls");
		//125, 40
		//���� ����ĭ
		for (int i = 0; i <= 40; i++) {
			gotoxy(2 + 2 * i, 1);
			cout << "��";
		}//����(��) 2,2 3,2,4,2 
		for (int i = 0; i < 35; i++) {
			gotoxy(2, 2 + i);
			cout << "��";
			gotoxy(82, 2 + i);
			cout << "��";
		}//����(�翷) 2, 2, 2,3, 2,4,
		for (int i = 0; i <= 40; i++) {
			gotoxy(2 + 2 * i, 37);
			cout << "��";
		}//����(�Ʒ�)
		 //������ ����ĭ
		for (int i = 0; i <= 13; i++) {
			gotoxy(90 + 2 * i, 1);
			cout << "��";
		}//����(��) 2,2 3,2,4,2 
		for (int i = 0; i < 35; i++) {
			gotoxy(90, 2 + i);
			cout << "��";
			gotoxy(116, 2 + i);
			cout << "��";
		}//����(�翷) 2, 2, 2,3, 2,4,
		for (int i = 0; i <= 13; i++) {
			gotoxy(90 + 2 * i, 37);
			cout << "��";
		} //����(�Ʒ�)
		clock_t begin, end;
		begin = clock();  // �ð�����

		for (int i = 0; i < ENE; i++) {
			switch (ap[i].get_direc()) {
			case 0: //��
				ap[i].set_aX(5);
				break;
			case 1: //��
				ap[i].set_aX(81);
				break;
			case 2: //��
				ap[i].set_aY(3);
				break;
			case 3: //��
				ap[i].set_aY(37);
				break;
			}//switch
		}//for �ʱⰪ ���ϱ�

		//todo : �浹ó�� / �ѽ�� ���� ó�ø� / �����ð� ������ ���� ++;
		while (true) {
			for (int i = 0; i < ENE; i++) {
				SetCursor(false);
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
							if (us.get_heart() == 0) {
								end = clock();
								myTime = ((end - begin) / CLOCKS_PER_SEC);
								GameOver(myName, myTime, myScore);
							}
						}//user, enemy �浹ó��
						gotoxy(95, 8);
						us.showHeart(us.get_heart());
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
						gotoxy(95, 15);
						cout << "T I M E : " << endl;
						end = clock(); //��� end�� ���ŵȴ�
						switch (end) {
						
						
						}
						gotoxy(105, 15);
						myTime = ((end - begin) / CLOCKS_PER_SEC);
						cout << myTime << endl; //�ð� ȣ��
						Sleep(TM);
					}//else
				}//for ���� �̵�
			}//for �������� char ������ ����!
		
		}//while

		
	}//void gamestart();
	 //****************************************************�����ؾߵ� �κ�
	void GameOver(char * , int, int) {
		system("cls");
		cout << "�����  ,, ,,  �׾����!" << endl;
		cout << *myName << " " << myScore << " " << myTime << endl;
		//��������
		// ���� �Է� (����)
		/*
		ifstream inFile("score.txt");
		while (!inFile.eof()) {
			cout << *myName << " " << myScore << " " << myTime << endl;
		}
		inFile.close();
		*/
	}

	void showRank() {
		//���� ��� (�б�)
		ofstream wd_file;
		wd_file.open("score.txt", ios::out);
		if (wd_file.fail()) {
			cout << "file�� �������� �ʽ��ϴ�." << endl;
			//�ڷΰ���
		}
		wd_file << *myName << " " << myScore << " " << myTime << endl;
		wd_file.close();

		//�ٽ� �����ϼ���!
	}
};

void howTo() {
	SetCursor(false);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

}//howTo()

void ranking() {
	cout << "����� ������ ����ϱ��?" << endl;
//	cout << "�������Դϴ٢�" << endl;

//	����ó���ؾߵȴ�
}//ranking()

 //���Ӹ޴�
 //��ŷ����
 // >>ȭ��ǥ ���� Ű�����!

void index() {
	system("cls");
	cout << "\n\n" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "      ���            ���        ���      ���������   �������      �����   ���      ���" << endl;
	cout << "      ����        ����       ����     �ƢƢơ�ƢƢƢ�   ��ƢƢƢơ��      ���      ���    ��� " << endl;
	cout << "       ��ơ��    ��ơ��      ��ơ��          ���         ���      ���      ���        ��� ���   " << endl;
	cout << "      ���  ��ơ��  ���     ���  ���         ���         �������        ���         ����" << endl;
	cout << "      ���    ���    ���    �������        ���         ��ƢƢƢơ��      ���        ��� ���" << endl;
	cout << "      ���     ��     ���   ��ƢƢƢơ��       ���         ���       ���     ���      ���    ��� " << endl;
	cout << "      ���            ���  ���        ���      ���         ���        ���  �����   ���      ���" << endl;
	cout << "\n\n" << endl;
}
void Menu() {
	index();
	int menu_choi; //�޴�����
	Merge mg;
	srand((unsigned int)time(NULL));
	while (true) {
		gotoxy(50, 25);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "1. ���ӽ���";
		gotoxy(50, 27);
		cout << "2. ���ӹ��";
		gotoxy(50, 29);
		cout << "3. ��ŷ����";

		gotoxy(50, 30);
		cout << "====================\n\n" << endl;
		gotoxy(50, 31);
		cout << "��ȣ�� �Է��� �ּ��� >>";
		cin >> menu_choi;

		switch (menu_choi) {
		case 1: {
			cout << "���ӽ���";
			system("cls");
		}return mg.gameStart();
		case 2: {
			cout << "���ӹ��";
			system("cls");
		}return howTo();
		case 3: {
			cout << "��ŷ����";
			system("cls");
		}return ranking();
		default: {
			cout << "�ٽ� �Է����ּ���!!" << endl;
			break;
		}
		}//switch


	}//while
}


int main() {
	system("mode con cols=125 lines=40"); //cols = ĭ/�� (����)  lines = ��/�� (����)

	
	//first();
	Menu();


	//������ ó�� �κ� / �����̸鼭 �� ���
	//�����̸鼭 �� ������ �ױ�
}