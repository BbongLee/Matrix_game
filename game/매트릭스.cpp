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

void user_move() {
	//	setcursortype(NOCURSOR);
	int x = 0, y = 0;
	char ch;
	gotoxy(x, y);
	printf("&");
	while (true)
	{
		ch = getch();
		gotoxy(x, y);
		printf(" ");  //�ܻ�x
		switch (ch)
		{
		case 72: //��
			if (y > 0) y--;
			break;
		case 80: //��
			if (y < 24) y++;
			break;
		case 75: //��
			if (x > 0) x--;
			break;
		case 77: //��
			if (x < 79) x++;
		}
		gotoxy(x, y);
		printf("@");
	}
} //user_move()

  //���� ���� ����
  //�������� ���� ���ؼ�
  //����濡�� ������()
  //���� �� ������ �״´�()
  //
class Alpha {
private:
	char lett; //���ĺ�
	int aX, aY; //��ǥ��
	int direc;//�������� ���� ���� �� ���������� ���� ����?!
	int speed;
public:
	void making_letter() {

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
	}//makingLetter()
	void move_letter() {
		switch (direc) {
		case 0:
			//��������
			cout << "����";
			aX = 0; //0���� �ʱ�ȭ!
			while (aX <= 125) { //-----> y��ǥ �״��, x��ǥ ������
				gotoxy(aX, aY);
				cout << lett;
				Sleep(TM);
				gotoxy(aX, aY);
				cout << " ";
				aX++;
			}
			break;
		case 1:
			//��
			cout << "����";
			aX = 125; //125���� �ʱ�ȭ!
			while (aX >= 0) { //-----> y��ǥ �״��, x��ǥ ������
				gotoxy(aX, aY);
				cout << lett;
				Sleep(TM);
				gotoxy(aX, aY);
				cout << " ";
				aX--;
			}
			break;
		case 2:
			//��
			cout << "����";
			aY = 0; //�������Ʒ��� 
			while (aY <= 40) { //-----> X��ǥ �״��, Y��ǥ ������
				gotoxy(aX, aY);
				cout << lett;
				Sleep(TM);
				gotoxy(aX, aY);
				cout << " ";
				aY++;
			}
			break;
		case 3:
			//��
			cout << "����";
			aY = 40; //�Ʒ��� ���� 
			while (aY >= 0) { //-----> X��ǥ �״��, Y��ǥ ������
				gotoxy(aX, aY);
				cout << lett;
				Sleep(TM);
				gotoxy(aX, aY);
				cout << " ";
				aY--;
			}
			break;
		default:
			cout << "���� �����Ҵ��� �ȵǾ��ٴ� ���� �ȵ�....�Ϸ��� ����..." << endl;
			break;

		}//switch
	}
	void print_letter() {

	}//printletter
};

class realGame {
private:
	Alpha ap[ENE]; //���� 50!
public:
	realGame() {
		system("cls");
		for (int i = 0; i < ENE; i++) {
			ap[i].making_letter();
		}
		for (int i = 0; i < ENE; i++) {
			ap[i].print_letter();
		}
		user_move();
	}

	void gameStart() {


	}
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
	int menu_choi; //�޴�����
	while (true) {
		gotoxy(60, 25);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "1. ���ӽ���";
		gotoxy(60, 27);
		cout << "2. ���ӹ��";
		gotoxy(60, 29);
		cout << "3. ��ŷ����";
		gotoxy(60, 30);
		cout << "====================\n\n" << endl;
		cout << "��ȣ�� �Է��� �ּ��� >>" << endl;
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