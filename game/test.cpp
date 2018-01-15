#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <thread>
using namespace std;
#define LET 30
#define TM 350 //0.35��
#define ENE 50

void gotoxy(int x, int y) {
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
} //��ǥ�̵�

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
	void print_user()
	{
		gotoxy(x, y);
		cout << "&";
	}
};//user class

  //���� ���� ����
  //�������� ���� ���ؼ�
  //����濡�� ������()
  //���� �� ������ �״´�()

class Alpha {
private:
	char lett; //���ĺ�
	int aX, aY; //��ǥ��
	int direc;//�������� ���� ���� �� ���������� ���� ����?!
			  //int speed;
public:
	Alpha() {
		char spaL[] = { '@','#','%','=','+','~' };
		srand((unsigned int)time(NULL));

		aX = (rand()) % 125;
		aY = (rand()) % 40;
		direc = (rand()) % 4;
		switch ((rand()) % 4) {
		case 0: lett = (rand()) % 10 + 48; break; //0~9������ ����
		case 1: lett = spaL[(rand()) % 6]; break; //spaL�迭���� ����
		case 2: lett = (rand()) % 26 + 65; break; //�빮��
		case 3: lett = (rand()) % 26 + 97; break; //�ҹ���
		}
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
//	void print_letter() {
//		gotoxy(aX, aY);
//		cout << lett;
//	}
	void erase_letter() {
		gotoxy(aX, aY);
		cout << " ";
	}
	/*
	void move_letter() {
		switch (direc) {
		case 0:
			//cout << "����";
			gotoxy(aX+1, aY);
			break;
		case 1:
			//cout << "����";
			gotoxy(aX-1, aY);
			break;
		case 2:
			//cout << "����";
			gotoxy(aX, aY+1);
			break;
		case 3:
			//cout << "����";
			gotoxy(aX, aY-1);
			break;
		default:
			cout << "���� �����Ҵ��� �ȵǾ��ٴ� ���� �ȵ�....�Ϸ��� ����..." << endl;
			break;

		}//switch 

	}//move
	*/
};

class realGame {
private:
	Alpha ap[ENE]; //���� 50!
	User u;
public:
	realGame() {
		for (int i = 0; i < ENE; i++) {
		//	ap[i].print_letter();
			gotoxy(ap[i].get_aX(), ap[i].get_aY());
			cout << ap[i].get_lett();
		}
		u.print_user();
	}

	void gameStart() {
		system("cls");
		int i = 0;
		while (true) {
			for (int i = 0; i < ENE; i++) {
				gotoxy(ap[i].get_aX(), ap[i].get_aY());
				cout << ap[i].get_lett();
				switch (ap[i].get_direc()) {
				case 0:
					//cout << "����";
					gotoxy(ap[i].get_aX() + 1, ap[i].get_aY());
					cout << ap[i].get_lett();
					break;
				case 1:
					//cout << "����";
					gotoxy(ap[i].get_aX() - 1, ap[i].get_aY());
					cout << ap[i].get_lett();
					break;
				case 2:
					//cout << "����";
					gotoxy(ap[i].get_aX(), ap[i].get_aY() + 1); 
					cout << ap[i].get_lett();
					break;
				case 3:
					//cout << "����";
					gotoxy(ap[i].get_aX(), ap[i].get_aY() - 1);
					cout << ap[i].get_lett();
					break;

				}//switch direc
			}//for
			//if������ ����ó�� �ϱ�
		}//while

	}//Start
};

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
	//cout << "            ��              ��     ��            ��     ���         ���       ���   �����   ���       ��� " << endl;
	cout << "\n\n" << endl;
}
void Menu() {
	index();
	int menu_choi; //�޴�������
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
		realGame rg;
		switch (menu_choi) {
		case 1: {
			cout << "���ӽ���";
			system("cls");
		}return rg.gameStart();
		case 2: {
			cout << "���ӹ��";
			system("cls");
		}break;
		case 3: {
			cout << "��ŷ����";
			Sleep(1000);
		}break;
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
	Menu(); //GameStart.cpp
			//����O, 



			//������ ó�� �κ� / �����̸鼭 �� ���
			//�����̸鼭 �� ������ �ױ�
}