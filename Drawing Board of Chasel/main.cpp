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

//坐标输入
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
			xyprintf(0, y + ylist, "输入格式错误，请重新输入");
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


//生成基本画面
void setbasicboard() {

	//划线
	line(0, ylist, screen_right, ylist);
	line(xinstr, ylist, xinstr, screen_bottom);

	//信息栏
	xyprintf(0, screen_bottom-20, "当前屏幕的像素为：%dx%d",screen_right,screen_bottom);
	xyprintf(0, screen_bottom - 40, "当前绘图区的像素为：%dx%d", screen_right - xinstr, screen_bottom - ylist);
	if (react_fileread == '1') {
		xyprintf(0, screen_bottom - 60, "文件读取情况:%s", "已读取");
	}
	else if (react_fileread == '2') {
		xyprintf(0, screen_bottom - 60, "文件读取情况:%s", "未读取");
	}
	else {
		xyprintf(0, screen_bottom - 60, "文件读取情况:%s", "无指令");
	}

	//菜单栏
	rectangle(0, 0, screen_right / 15, screen_bottom / 30);
	rectangle(2*screen_right / 15, 0, screen_right / 15, screen_bottom / 30);
	rectangle(2 * screen_right / 15, 0, 3*screen_right / 15, screen_bottom / 30);

	




	//指令表框
		//图形选择
	for (int i = 1; i < 5; i++) {
		xyprintf(screen_right / 40  + (i - 1) * xperbutton, (20 + ylist) / 2 - 20, "%d.", i);
		switch (i) {
		case 1:
			line(screen_right / 40 + 10 + (i - 1) * xperbutton,(ylist+60)/4+(ylist-20)/3, screen_right / 20 + 20 + (i - 1) * xperbutton, (ylist + 60) / 4);
			xyprintf(screen_right / 20 + 20 + (i - 1) * xperbutton, (20 + ylist) / 2 - 20, "%s", "直线");
			break;
		case 2:
			xyprintf(screen_right / 20 + 20 + (i - 1) * xperbutton, (20 + ylist) / 2 - 20, "%s", "矩形");
			break;
		case 3:
			xyprintf(screen_right / 20 + 20 + (i - 1) * xperbutton, (20 + ylist) / 2 - 20, "%s", "圆形");
			break;
		case 4:
			xyprintf(screen_right / 20 + 20 + (i - 1) * xperbutton, (20 + ylist) / 2 - 20, "%s", "圆弧");
			break;
		}

	}
		//颜色选择
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 2; j++) {
			rectangle(screen_right * 39 / 40-i*ylist/4, ylist * 3 / 10+j*ylist/4, screen_right * 39 / 40 - (ylist / 4) - i * ylist / 4, ylist * 3 / 10 + ylist / 4 + j * ylist / 4);
		}
	}


}

//在指令框内写入
void write_instr(int y, LPCWSTR s) {
	outtextrect(0, ylist + y, xinstr, screen_bottom-60, s);
	
}

//在指令表框内写入
void write_list(int x, LPCWSTR s) {
	outtextrect(x, 20, x+xperbutton, ylist, s);
}

//清屏并保留画板基本页面
void clear_board() {
	cleardevice();
	setbasicboard();
}

//清除指令框
void clear_instr() {
	write_instr(1, L"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               ");
}

//进入并初始化画板
void init() {


	//展开一个全屏白色画板
	initgraph(-1, -1,0x1);
	setbkcolor(WHITE);
	

	//提示用户切换输入法，防止出错
	for (int j = 1; j == 1;) {
		xyprintf(0, 0, "欢迎您进入Chasel画板,请先确定您的输入法切换为英语模式,然后再按回车进入画板");
		if (getch() == 0x0d) { 
			cleardevice();
			j = 0; 
		}
	}

	//读取该屏幕信息（我的显示器是1280x720个像素点）
	getviewport(&screen_left, &screen_top, &screen_right, &screen_bottom, NULL, NULL);
	ylist = screen_bottom / 6; 
	//xinstr = screen_right * 200 / 1000;
	xinstr = screen_right * 200 / 1000;
	yperbutton = 20; 
	xperbutton = screen_right / 10;


	//创造基本画面
	setbasicboard();
	xyprintf(0, screen_bottom - 60, "文件读取情况:");

}

//询问是否读取文件
void mod1() {

	write_instr(1,L"欢迎您进入Chasel画板，请根据菜单选择您想进行的操作：\n1.读取文件\n2.不读取文件");
	react_fileread = getch();
	clear_instr();

	xyprintf(0, screen_bottom - 20, "当前屏幕的像素为：%dx%d", screen_right, screen_bottom);
	xyprintf(0, screen_bottom - 40, "当前绘图区的像素为：%dx%d", screen_right-xinstr, screen_bottom-ylist);
	if (react_fileread == '1') {
		xyprintf(0, screen_bottom - 60, "文件读取情况:%s", "已读取");
	}
	if (react_fileread == '2') {
		xyprintf(0, screen_bottom - 60, "文件读取情况:%s", "未读取");
	}
}

//（读取文件并）选择清屏/作画/退出
void mod2() {
	for (int j = 1; j == 1;) {//j!=1时退出
		write_instr(20, L"欢迎您进入Chasel画板，请根据菜单选择您想进行的操作：\n1.清除屏幕\n2.作画\n3.退出");
		
		react_ifdraw = getch();
		switch (react_ifdraw) {

		case '1':
			clear_board();
			write_instr(1, L"已清屏");
			write_instr(20, L"欢迎您进入Chasel画板，请根据菜单选择您想进行的操作：\n1.清除屏幕\n2.作画\n3.退出");
			break;
		
		case '2':
			clear_instr();
			write_instr(1, L"请根据上方的指令表选择您要画的图形");
			react_draw = getch();
			clear_instr();
			switch (react_draw) {

			case '1':
				write_instr(1, L"画直线");
				write_instr(20, L"请输入第一个点横坐标:(按enter结束)");
				xline1 = coordinate(60);
				write_instr(80, L"请输入第一个点纵坐标：");
				yline1 = coordinate(100);
				write_instr(120, L"请输入第二个点横坐标：");
				xline2 = coordinate(140);
				write_instr(160, L"请输入第二个点纵坐标：");
				yline2 = coordinate(180);
				line(xline1+xinstr, yline1+ylist, xline2+xinstr, yline2+ylist);
				clear_instr();
				write_instr(1, L"已作图");
				break;

			case '2':
				write_instr(1, L"画矩形");
				write_instr(20, L"请输入第一个点横坐标:(按enter结束)");
				xline1 = coordinate(60);
				write_instr(80, L"请输入第一个点纵坐标：");
				yline1 = coordinate(100);
				write_instr(120, L"请输入第二个点横坐标：");
				xline2 = coordinate(140);
				write_instr(160, L"请输入第二个点纵坐标：");
				yline2 = coordinate(180);
				rectangle(xline1 + xinstr, yline1 + ylist, xline2 + xinstr, yline2 + ylist);
				clear_instr();
				write_instr(1, L"已作图");
				break;


			case '3':
				write_instr(1, L"画圆形");
				write_instr(20, L"请输入圆点横坐标:(按enter结束)");
				xcir = coordinate(60);
				write_instr(80, L"请输入圆点纵坐标：");
				ycir = coordinate(100);
				write_instr(120, L"请输入半径：");
				rcir= coordinate(140);
				circle(xcir+xinstr, ycir+ylist, rcir);
				clear_instr();
				write_instr(1, L"已作图");
				break;

			case '4':
				write_instr(1, L"画圆弧");
				write_instr(20, L"请输入圆点横坐标:(按enter结束)");
				xcir = coordinate(60);
				write_instr(80, L"请输入圆点纵坐标：");
				ycir = coordinate(100);
				write_instr(120, L"请输入半径：");
				rcir = coordinate(140);
				write_instr(160, L"请输入圆弧起始角：");
				arcbegin= coordinate(180);
				write_instr(200, L"请输入圆弧终止角：");
				arcend = coordinate(220);
				arc(xcir+xinstr,ycir+ylist,arcbegin,arcend,rcir);
				clear_instr();
				write_instr(1, L"已作图");
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
