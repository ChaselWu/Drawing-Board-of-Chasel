#include<stdio.h>
#include<stdlib.h>
#include"graphics.h"

int react1, react2;


void mod1() {
	xyprintf(0, 10, "��ӭ������Chasel���壬����ݲ˵�ѡ��������еĲ�����\n1.��ȡ�ļ�\n2.����ȡ�ļ�");
	react1 = getch();

	if (react1 == '1') {
		xyprintf(0, 30, "�Ѷ�ȡ");
	}
	if (react1 == '2') {
		xyprintf(0, 30, "δ��ȡ");
	}
}

void mod2() {
	for (int j = 1; j == 1;) {
		if (react1 == '1') {
			xyprintf(0, 30, "�Ѷ�ȡ");
		}
		if (react1 == '2') {
			xyprintf(0, 30, "δ��ȡ");
		}
		xyprintf(0, 50, "��ӭ������Chasel���壬����ݲ˵�ѡ��������еĲ�����\n1.�����Ļ\n2.����\n3.�˳�");
		react2 = getch();
		switch (react2) {
		case '1':
			cleardevice();
			xyprintf(0, 10, "��ӭ������Chasel���壬����ݲ˵�ѡ��������еĲ�����\n1.��ȡ�ļ�\n2.����ȡ�ļ�");
			break;
		case '2':

			break;
		case '3':
			j = 0;
			break;
		}
	}
}

int main() {
	initgraph(800, 400);
	mod1();
	mod2();
	return 0;
}
