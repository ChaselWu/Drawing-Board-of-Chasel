#include<stdio.h>
#include<stdlib.h>
#include"graphics.h"

int react1, react2;


void mod1() {
	xyprintf(0, 10, "欢迎您进入Chasel画板，请根据菜单选择您想进行的操作：\n1.读取文件\n2.不读取文件");
	react1 = getch();

	if (react1 == '1') {
		xyprintf(0, 30, "已读取");
	}
	if (react1 == '2') {
		xyprintf(0, 30, "未读取");
	}
}

void mod2() {
	for (int j = 1; j == 1;) {
		if (react1 == '1') {
			xyprintf(0, 30, "已读取");
		}
		if (react1 == '2') {
			xyprintf(0, 30, "未读取");
		}
		xyprintf(0, 50, "欢迎您进入Chasel画板，请根据菜单选择您想进行的操作：\n1.清除屏幕\n2.作画\n3.退出");
		react2 = getch();
		switch (react2) {
		case '1':
			cleardevice();
			xyprintf(0, 10, "欢迎您进入Chasel画板，请根据菜单选择您想进行的操作：\n1.读取文件\n2.不读取文件");
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
