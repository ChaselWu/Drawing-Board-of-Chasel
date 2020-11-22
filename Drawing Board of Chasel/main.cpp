#include<stdio.h>
#include<stdlib.h>
#include"graphics.h"
#include<iostream>
using namespace std;
int react_fileread, react_ifdraw, react_draw;
int screen_left, screen_top, screen_right, screen_bottom, ylist, xinstr,xperbutton,yperbutton;
int coord[5] = { 0 };
LOGFONT typeface;
int xline1, xline2, yline1, yline2,xrec1,yrec1,xrec2,yrec2,xcir,ycir,rcir,arcbegin,arcend;

color_t white = EGERGB(255,255,255);

//��������
int coordinate(int y) {
	int coord[5] = { 0 };

	for (int i = 0; i < 5; i++) {
		int c = getch();
		if (c == 0x0d) {
			break;
		}
		else if (47 < c < 57) {
			coord[i] = c;
			xyprintf(8 * i, y + ylist, "%d", c-48);
		}
		else {
			xyprintf(0, y + ylist, "�����ʽ��������������");
			i=0;
			for (int j = 0; j < 5; j++) {
				coord[j] = 0;
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		if (coord[4] == 0) {
			for (int i = 0; i < 4; i++) {
				coord[4 - i] = coord[3 - i];
				coord[3 - i] = '0';
			}
		}
	}
	int ans = (coord[0] - 48) * 10000 + (coord[1] - 48) * 1000 + (coord[2] - 48) * 100 + (coord[3] - 48) * 10 + coord[4] - 48;
	xyprintf(0, y + ylist, "%d",ans);
	return ans;
}


//���ɻ�������
void setbasicboard() {

	//����
	line(0, ylist, screen_right, ylist);
	line(xinstr, ylist, xinstr, screen_bottom);

	//��Ϣ��
	xyprintf(0, screen_bottom-20, "��ǰ��Ļ������Ϊ��%dx%d",screen_right,screen_bottom);
	xyprintf(0, screen_bottom - 40, "��ǰ��ͼ��������Ϊ��%dx%d", screen_right - xinstr, screen_bottom - ylist);
	if (react_fileread == '1') {
		xyprintf(0, screen_bottom - 60, "�ļ���ȡ���:%s", "�Ѷ�ȡ");
	}
	else if (react_fileread == '2') {
		xyprintf(0, screen_bottom - 60, "�ļ���ȡ���:%s", "δ��ȡ");
	}
	else {
		xyprintf(0, screen_bottom - 60, "�ļ���ȡ���:%s", "��ָ��");
	}

	//�˵���
	rectangle(0, 0, screen_right / 15, screen_bottom / 30);
	rectangle(2*screen_right / 15, 0, screen_right / 15, screen_bottom / 30);
	rectangle(2 * screen_right / 15, 0, 3*screen_right / 15, screen_bottom / 30);

	




	//ָ����
		//ͼ��ѡ��
	for (int i = 1; i < 5; i++) {
		xyprintf(screen_right / 40  + (i - 1) * xperbutton, (20 + ylist) / 2 - 20, "%d.", i);
		switch (i) {
		case 1:
			line(screen_right / 40 + 10 + (i - 1) * xperbutton,(ylist+60)/4+(ylist-20)/3, screen_right / 20 + 20 + (i - 1) * xperbutton, (ylist + 60) / 4);
			xyprintf(screen_right / 20 + 20 + (i - 1) * xperbutton, (20 + ylist) / 2 - 20, "%s", "ֱ��");
			break;
		case 2:
			xyprintf(screen_right / 20 + 20 + (i - 1) * xperbutton, (20 + ylist) / 2 - 20, "%s", "����");
			break;
		case 3:
			xyprintf(screen_right / 20 + 20 + (i - 1) * xperbutton, (20 + ylist) / 2 - 20, "%s", "Բ��");
			break;
		case 4:
			xyprintf(screen_right / 20 + 20 + (i - 1) * xperbutton, (20 + ylist) / 2 - 20, "%s", "Բ��");
			break;
		}

	}
		//��ɫѡ��
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 2; j++) {
			rectangle(screen_right * 39 / 40-i*ylist/4, ylist * 3 / 10+j*ylist/4, screen_right * 39 / 40 - (ylist / 4) - i * ylist / 4, ylist * 3 / 10 + ylist / 4 + j * ylist / 4);
		}
	}


}

//��ָ�����д��
void write_instr(int y, LPCWSTR s) {
	outtextrect(0, ylist + y, xinstr, screen_bottom-60, s);
	
}

//��ָ������д��
void write_list(int x, LPCWSTR s) {
	outtextrect(x, 20, x+xperbutton, ylist, s);
}

//�����������������ҳ��
void clear_board() {
	cleardevice();
	setbasicboard();
}

//���ָ���
void clear_instr() {
	write_instr(1, L"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               ");
}

//���벢��ʼ������
void init() {


	//չ��һ��ȫ����ɫ����
	initgraph(-1, -1,0x1);
	setbkcolor(WHITE);
	

	//��ʾ�û��л����뷨����ֹ����
	for (int j = 1; j == 1;) {
		xyprintf(0, 0, "��ӭ������Chasel����,����ȷ���������뷨�л�ΪӢ��ģʽ,Ȼ���ٰ��س����뻭��");
		if (getch() == 0x0d) { 
			cleardevice();
			j = 0; 
		}
	}

	//��ȡ����Ļ��Ϣ���ҵ���ʾ����1280x720�����ص㣩
	getviewport(&screen_left, &screen_top, &screen_right, &screen_bottom, NULL, NULL);
	ylist = screen_bottom / 6; 
	//xinstr = screen_right * 200 / 1000;
	xinstr = screen_right * 200 / 1000;
	yperbutton = 20; 
	xperbutton = screen_right / 10;


	//�����������
	setbasicboard();
	xyprintf(0, screen_bottom - 60, "�ļ���ȡ���:");

}

//ѯ���Ƿ��ȡ�ļ�
void mod1() {

	write_instr(1,L"��ӭ������Chasel���壬����ݲ˵�ѡ��������еĲ�����\n1.��ȡ�ļ�\n2.����ȡ�ļ�");
	react_fileread = getch();
	clear_instr();

	xyprintf(0, screen_bottom - 20, "��ǰ��Ļ������Ϊ��%dx%d", screen_right, screen_bottom);
	xyprintf(0, screen_bottom - 40, "��ǰ��ͼ��������Ϊ��%dx%d", screen_right-xinstr, screen_bottom-ylist);
	if (react_fileread == '1') {
		xyprintf(0, screen_bottom - 60, "�ļ���ȡ���:%s", "�Ѷ�ȡ");
	}
	if (react_fileread == '2') {
		xyprintf(0, screen_bottom - 60, "�ļ���ȡ���:%s", "δ��ȡ");
	}
}

//����ȡ�ļ�����ѡ������/����/�˳�
void mod2() {
	for (int j = 1; j == 1;) {//j!=1ʱ�˳�
		write_instr(20, L"��ӭ������Chasel���壬����ݲ˵�ѡ��������еĲ�����\n1.�����Ļ\n2.����\n3.�˳�");
		
		react_ifdraw = getch();
		switch (react_ifdraw) {

		case '1':
			clear_board();
			write_instr(1, L"������");
			write_instr(20, L"��ӭ������Chasel���壬����ݲ˵�ѡ��������еĲ�����\n1.�����Ļ\n2.����\n3.�˳�");
			break;
		
		case '2':
			clear_instr();
			write_instr(1, L"������Ϸ���ָ���ѡ����Ҫ����ͼ��");
			react_draw = getch();
			clear_instr();
			switch (react_draw) {

			case '1':
				write_instr(1, L"��ֱ��");
				write_instr(20, L"�������һ���������:(��enter����)");
				xline1 = coordinate(60);
				write_instr(80, L"�������һ���������꣺");
				yline1 = coordinate(100);
				write_instr(120, L"������ڶ���������꣺");
				xline2 = coordinate(140);
				write_instr(160, L"������ڶ����������꣺");
				yline2 = coordinate(180);
				line(xline1+xinstr, yline1+ylist, xline2+xinstr, yline2+ylist);
				clear_instr();
				write_instr(1, L"����ͼ");
				break;

			case '2':
				write_instr(1, L"������");
				write_instr(20, L"�������һ���������:(��enter����)");
				xline1 = coordinate(60);
				write_instr(80, L"�������һ���������꣺");
				yline1 = coordinate(100);
				write_instr(120, L"������ڶ���������꣺");
				xline2 = coordinate(140);
				write_instr(160, L"������ڶ����������꣺");
				yline2 = coordinate(180);
				rectangle(xline1 + xinstr, yline1 + ylist, xline2 + xinstr, yline2 + ylist);
				clear_instr();
				write_instr(1, L"����ͼ");
				break;


			case '3':
				write_instr(1, L"��Բ��");
				write_instr(20, L"������Բ�������:(��enter����)");
				xcir = coordinate(60);
				write_instr(80, L"������Բ�������꣺");
				ycir = coordinate(100);
				write_instr(120, L"������뾶��");
				rcir= coordinate(140);
				circle(xcir+xinstr, ycir+ylist, rcir);
				clear_instr();
				write_instr(1, L"����ͼ");
				break;

			case '4':
				write_instr(1, L"��Բ��");
				write_instr(20, L"������Բ�������:(��enter����)");
				xcir = coordinate(60);
				write_instr(80, L"������Բ�������꣺");
				ycir = coordinate(100);
				write_instr(120, L"������뾶��");
				rcir = coordinate(140);
				write_instr(160, L"������Բ����ʼ�ǣ�");
				arcbegin= coordinate(180);
				write_instr(200, L"������Բ����ֹ�ǣ�");
				arcend = coordinate(220);
				arc(xcir+xinstr,ycir+ylist,arcbegin,arcend,rcir);
				clear_instr();
				write_instr(1, L"����ͼ");
				break;

			case '5':
				
				break;
			}






		


			break;
		
		case '3':
			j = 0;
			break;
		}
	}
}

int main() {

	init();

	mod1();

	mod2();

	closegraph();
	return 0;
}
