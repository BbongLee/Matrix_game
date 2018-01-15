#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <thread>
using namespace std;
#define COLS 125
#define LOWS 40
#define UX 3 //���� ���κ� x��ǥ
#define UY 1
#define LX 3 //���� 
#define LY 3
#define DX // �Ʒ���
#define DY
#define RX //������
#define RY

#define TM 20 //0.03��
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
} //��ǥ�̵�

class User {
	int x, y;
	char ch;//�Է¹���
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
	char lett; //���ĺ�
	int aX, aY; //��ǥ��
	int direc;//�������� ���� ���� �� ���������� ���� ����?!
			  //int speed;
public:
	Alpha() {
		aX = rand() % 125; //X��ǥ �ʱⰪ
		aY = rand() % 40; //Y��ǥ �ʱⰪ
		direc = rand() % 4;
		char spaL[] = { '@','#','%','=','+','~' };
		switch (rand() % 6) {
		case 0: lett = rand() % 10 + 48; break; //0~9������ ����
		case 1: lett = spaL[rand() % 6]; break; //spaL�迭���� ����
		case 2:case 4: lett = rand() % 26 + 65; break; //�빮��
		case 3:case 5: lett = rand() % 26 + 97; break; //�ҹ���
		}
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
	Alpha ap[ENE]; //����
	User us;
	char ch;
	void user_move() {
		ch = getch();
		switch (ch)
		{
		case 72: //��
			if (us.get_y() > 0) {
				us.set_y(us.get_y() - 1);
			
			}
				break;
		case 80: //��
			if (us.get_y() < 24) us.set_y(us.get_y() + 1);
			break;
		case 75: //��
			if (us.get_x() > 0) us.set_x(us.get_x() - 1);
			break;
		case 77: //��
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
				case 0: //��
						//cout << "��";
					cout << " ";
					ap[i].set_aX(ap[i].get_aX() - 1);
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					if ((ap[i].get_aX() >= COLS) || (ap[i].get_aX() <= 0) || 
						(ap[i].get_aY() >= LOWS) || (ap[i].get_aY() <= 0)) {
						ap[i].set_aX(rand() % 125); ap[i].set_aY(rand() % 40);
						i--;
					}//reset

					//ap[i].set_aX(ap[i].get_aX() + 2); // ->�������� ��ǥ�̵�
					break;
				case 1://��
					   //cout << "��";
					cout << " ";
					ap[i].set_aX(ap[i].get_aX() + 1);
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					cout << " ";
					ap[i].set_aX(ap[i].get_aX() - 2); // <-����
					break;
				case 2://��
					   //cout << "��";
					cout << " ";
					ap[i].set_aY(ap[i].get_aY() - 1);
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					cout << " ";
					ap[i].set_aY(ap[i].get_aY() + 2); // �鳲��
					break;
				case 3://��
					   //cout << "��";
					cout << " ";
					ap[i].set_aY(ap[i].get_aY() + 1);
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					cout << " ";
					ap[i].set_aY(ap[i].get_aY() - 2); // �����
					break;
				}//switch direc
				Sleep(TM);
				if ((ap[i].get_aX() > COLS) || (ap[i].get_aX()< 0) ||
					(ap[i].get_aY() > LOWS) || (ap[i].get_aY() < 0)) {
					ap[i].set_aX(rand() % 125); ap[i].set_aY(rand() % 40);
					i--;
				}//reset
				cout << (char)ap[i].get_lett(); //�Ѹ���
			}//for ���� �߻�/�����̱�
			
			 //user ����
			if (kbhit())
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				gotoxy(us.get_x(), us.get_y());
				cout << "&";
				user_move();
				gotoxy(us.get_x(), us.get_y());
				cout << " ";  //�ܻ�x
			}
		}//while
	}//gameStart()
};

void howTo() {
	cout << "���� ��� �Ұ�" << endl;
	cout << "�������Դϴ٢�" << endl << "������ �� ������!!!!" << endl;
}//howTo()

void ranking() {
	cout << "����� ������ ����ϱ��?" << endl;
	cout << "�������Դϴ٢�" << endl;
}//ranking()

 //���Ӹ޴�
 //��ŷ����
 // >>ȭ��ǥ ���� Ű�����!

void index() {
	system("cls");
	cout << "\n\n" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "          ���            ���        ���      ���������   �������      �����   ���      ���" << endl;
	cout << "          ����        ����       ����     �ƢƢơ�ƢƢƢ�   ��ƢƢƢơ��      ���      ���    ��� " << endl;
	cout << "          ��ơ��    ��ơ��      ��ơ��          ���         ���      ���      ���       ��� ���   " << endl;
	cout << "          ���  ��ơ��  ���     ���  ���         ���         �������        ���         ����" << endl;
	cout << "          ���    ���    ���    �������        ���         ��ƢƢƢơ��      ���        ��� ���" << endl;
	cout << "          ���     ��     ���   ��ƢƢƢơ��       ���         ���       ���     ���      ���    ��� " << endl;
	cout << "          ���            ���  ���        ���      ���         ���        ���  �����   ���      ���" << endl;
	cout << "\n\n" << endl;
}
void Menu() {
	index();
	int menu_choi; //�޴�����
	MERGE mg;
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