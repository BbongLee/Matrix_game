#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <thread>
using namespace std;
#define COLS 125
#define LOWS 40

#define TM 10 //0.03��
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
	char lett; //���ĺ�
	int aX, aY; //��ǥ��
	int direc;//�������� ���� ���� �� ���������� ���� ����?!
			  //int speed;
public:
	Alpha() {
		aX = rand() % 76 + 4; //X��ǥ �ʱⰪ
		aY = rand() % 33 + 2; //Y��ǥ �ʱⰪ
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
	Alpha ap[ENE];//����
	User us;
	char ch;
	void gameStart() {
		//125, 40
		for (int i = 0; i < 40; i++) { //����(��) 2,2 3,2,4,2 
			gotoxy(2 + 2 * i, 1);
			cout << "��";
		}
		for (int i = 0; i < 35; i++) { //����(�翷) 2, 2, 2,3, 2,4,
			gotoxy(2, 2 + i);
			cout << "��";
			gotoxy(82, 2 + i);
			cout << "��";
		}
		for (int i = 0; i < 40; i++) { //����(�Ʒ�)
			gotoxy(2 + 2 * i, 37);
			cout << "��";
		}
		//cout << "    �ʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢʢ�" << endl;
		//cout << "    ��    ��" << endl;
		//cout << endl;
		clock_t begin, end;
		begin = clock();        // �ð�����

		for (int i = 0; i < ENE; i=i+4) {
			switch (ap[i].get_direc()) {
			case 0: //��
					//����Ȯ���� ���� �� �߰�! ���۰�?
				ap[i].set_aX(2);
				break;
			case 1: //��
				ap[i].set_aX(82);
				break;
			case 2: //��
				ap[i].set_aY(2);
				break;
			case 3: //��
				ap[i].set_aY(37);
				break;
			}//switch �ʱⰪ ���ϱ�
		}//for

		while (true) {
			SetCursor(false);
			
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
					break;
				case 80: //��
					if (us.get_y() >= 40) break;
					else us.set_y(us.get_y() + 1);
					break;
				case 75: //��
					if (us.get_x() <= 0) break;
					else us.set_x(us.get_x() - 1);
					break;
				case 77: //��
					if (us.get_x() >= 125) break;
					else us.set_x(us.get_x() + 1);
					break;
				}
				gotoxy(us.get_x(), us.get_y());
				cout << "��";
			}//user move
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			for (int i = 0; i < ENE; i++) {
				ap[i].eraser_lett();//�����
				switch (ap[i].get_direc()) {
				case 0: //�� //->
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					//����Ȯ���� ���� �� �߰�! ���۰�?
					ap[i].set_aX(ap[i].get_aX() + 1); 
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					break;
				case 1: //�� <-
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
					ap[i].set_aX(ap[i].get_aX() - 1);
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					break;
				case 2: //�� ��
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
					ap[i].set_aY(ap[i].get_aY() + 1);
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					break;
				case 3: //�� ��
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					ap[i].set_aY(ap[i].get_aY() - 1);
					gotoxy(ap[i].get_aX(), ap[i].get_aY());
					break;
				}//switch direct
				if ((ap[i].get_aX() > 80) || (ap[i].get_aX() < 4) ||
					(ap[i].get_aY() > 36) || (ap[i].get_aY() < 2)) {
					ap[i].set_aX(rand() % 80); ap[i].set_aY(rand() % 37);
					i--;
				}// ���� �Ѿ�� reset
				gotoxy(ap[i].get_aX(), ap[i].get_aY());
				cout << (char)ap[i].get_lett(); //���ĺ� �Ѹ���
				Sleep(TM);
			}//for ���� �̵�
			
			
		}//while

		for (int i = 0; i<30; i++)
		{
			if ((us.get_x() == ap[i].get_aX()) && (us.get_y() == ap[i].get_aY()))
			{
				cout << "���� �Ф�" << endl;
				exit(1);
			}
		}//�¾�����?

		end = clock();          // �ð�����
		cout << "����ð� : " << ((end - begin) / CLOCKS_PER_SEC) << endl;
	}//void gamestart();
};

void howTo() {
	//cout << "���� ��� �Ұ�" << endl;
	
	//cout << "�������Դϴ٢�" << endl << "������ �� ������!!!!" << endl;
	
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