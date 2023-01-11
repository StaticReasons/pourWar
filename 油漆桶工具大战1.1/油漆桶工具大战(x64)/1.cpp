
//Creater : MysteryLJR
//下次上机目标：油漆桶图标 

//17.10.13
//这似乎是一件很容易的工程
 
//17.10.14
//好久没复习bfs了 现在搞起来真他妈难
 
//真佩服自己能写出一个57行的bfs

//zc的好像只有10行 
//我去 

//17.10.15
//都在忙着绘制按键贴图的bmp......

//ps我今晚不再爱你了 

//累趴 

//17.10.21
//首次编译.........cnnnnnnnnnnnmmmmnmnmnmmnmnmnmnmnmnmnmnmnmnmnmnmnmnmnmnmnmnm
//我可能安装了一个假的SDL 神他妈bmp能把绿色读成红色 有毒

//emmmmmm我想应该是photoshop太坑爹了吧跟SDL的bmp格式不一样
//hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh 

//17.10.22
//哇去!!!!!!!!!!!!!!!!!!!!!!!!!!
//我怎么就没有想到可以用光标啊！！！
//这样就不用画出按键说明在游戏里面了，直接在文字窗口里面说按W和S或upkey和downke以移动光标！！！
//真是天生我才（划掉

//光标任务很容易实现的嘛OVO的要死		//cnmd一点都不简单（备注10.28） 
//再把main函数改改就大功告成了！！！ 
 
//17.10.27 
//哇去！！！哪个神经细胞告诉我光标系统简单的？！
//坑爹canchoosecolors算法（自己起的名字）

//。。。。。。。。。其实也还好的了。。。。。。
 
//真佩服自己能写出250多行的代码
//我可能码了个假窗口

//可能占用内存太大了吧...........诶我有了主意！
//把完整的RGB颜色数据用0~6的数字表示，这个游戏本来就只有7个颜色啊！！！ 
//天生（划掉）还是我的智商高
 
//emmmmmmmmmm恶魔密码密密麻麻买买买密密麻麻迷迷茫茫妈妈
//果然是bfs错了
//但是为什么会无缘无故从左下角的地方bfs到左上角啊？？？？
//一脸迷茫

//17.10.28
//emmmmmmmmmmm吃了一顿金拱门之后果然灵感四射 
//新的catch error方法！
//金拱门万岁万岁万岁万万岁亿岁亿岁亿亿岁2^65536岁2^65536岁2^65536 2^65536岁MAXN岁MAXN岁MAXNMAXN岁

//全面去除三元运算符。。。。吧........ 
 
//哇去！！！！r被多加了1！！！！！
//cnmcnmcnmcnmcnmcnmcnmcnmcnmcnm我怎么可以犯这种低级错误
//诶改好之后 一下子就正常了O_OO__OO_______OO-------------------------OO···O 
//这么说的话......岂不是就可以做结算系统了？！
//就快要大功告成了

//随着poured的加入（表示哪些地盘被染过色）............. 
//好吧有一个地方不得不用三元 
 
//哇去这东东有毒！！！！！！
//bfs乱码又来了!!!
//（可能我又要去吃一顿金拱门了（嗯正好现在晚餐时间（滚
//晚天可能要通宵QAQ明天答应要给lmh测试的.......... 
//突然发现我的代码行已经涨到384行了！！！（可没算这些注释和日志）

//所以我又吃了一餐金拱门（笑cry笑cry笑cry笑cry笑cry 

//没办法啦........只能把更改地图的bfs和统计地盘的bfs两者分开了.......无语 
//然后再4次发现自己犯了低级错误 

//哇去！原来乱码的原因不是bfs!!!!是canchoosecolors计算可选颜色时忘了初始化a了!!!!（吓得我赶紧把他改成局部变量 
//终于！！！！！！！没有bug啦！！！！大功告成！！！！！！！！！！！ 
//然而我发现代码变成了昨天的两倍——423行（咸鱼的智商也许就是永远高不了多少吧，哪像猪 
 
//17.10.29
//测试响应不大好啊这
//主要的几个问题：
//1.光标移动不了（原因：忘了把keyon赋值成canchoosecolors[keyonwhichccc]）
//2.颜色太接近（目前把天蓝调浅了一些，深蓝调深了一些，黄色调浅了一些
//3.后期卡（原因：目前已不必要catch error，程序输出太多）（目前把输出都转到log.txt（日志）里面来了）
//目前的几个问题已解决，但是bfs时候会偶尔一大片变黑————gamemap里面出现了0~6以外的数字......目前无法解决，因为这只是偶尔的事件==

//17.11.18
//好久没动这个了
//果然.....看一下SDL源码还是有用的，比浏览器好多了 

//17.11.19
//mdzz bmp格式居然只有那么少颜色
//要是有SDL_image.h就好了...... png还可以透明呢........
 
//17.11.24
//终于 把光标和暴力的色板 改成了油漆桶图片换好了.....
//诶不对 我没有把左右分出来啊........妈的智障（划掉）妈是我制胜的魔杖！！！！笑cry笑cry笑cry 
#include <SDL.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <conio.h>
#include <cstring>

#include "bits/stdc++.h"

#define RED 0x00e03200		// R:224	G:50	B:0
#define ORANGE 0x00e0c000	// R:224	G:192	B:0
#define YELLOW 0x00e0e000	// R:224	G:224	B:0
#define GREEN 0x0000c000	// R:0		G:192	B:0
#define AQUA 0x0000c0c0		// R:0 		G:192 	B:192
#define BLUE 0x000000c0		// R:0 		G:0 	B:192
#define PURPLE 0x00c000c0	// R:192 	G:0 	B:192

#define MAXN 10000 //for bfs
 
using namespace std;

int MAXWIDTH=1280;
int MAXHEIGHT=960;
int height,width;
int block=20;
int kb=150;
int keyon=0;
int lr=0;
int leftcolor=5;
int rightcolor=6;
int canchoosecolors[5];
int keyonwhichccc=0;
int COLOR[7]={
	RED,
	ORANGE,
	YELLOW,
	GREEN,
	AQUA,
	BLUE,
	PURPLE
};

bool end=false;

Uint8 gamemap[MAXN][MAXN];
Uint8 poured[MAXN][MAXN]; 

ofstream fout("./code/log.txt");
ofstream fpout("./code/piclog.txt");
ifstream fin("./code/log.txt");
ifstream fpin("./code/piclog.txt");

SDL_Surface* surf;
SDL_Window* wind;
SDL_Surface* pic[2][7]; 
SDL_Surface* ico; 

int varout(){
	fout<<"varout:"<<endl;
	fout<<"height:"<<height<<endl;
	fout<<"width:"<<width<<endl;
	fout<<"block:"<<block<<endl;
	fout<<"kb:"<<kb<<endl;
	fout<<"keyon:"<<keyon<<endl;
	fout<<"lr:"<<lr<<endl;
	fout<<"leftcolor:"<<leftcolor<<endl;
	fout<<"rightcolor:"<<rightcolor<<endl;
	
	fout<<"canchoosecolors:";
	for(int i=0;i<5;i++)
	fout<<canchoosecolors[i]<<' ';
	fout<<endl;
	
	fout<<"keyonwhichccc:"<<keyonwhichccc<<endl;
	
	fout<<"gamemap:"<<endl;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++)
			fout<<(int)gamemap[i][j]<<' ';
		fout<<endl;
	}
	fout<<endl;
	
	fout<<"poured:"<<endl;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++)
			fout<<(int)poured[i][j]<<' ';
		fout<<endl;
	}
	fout<<endl;
}
int flashmap(SDL_Surface* surf){
	fout<<endl<<"do flashmap:"<<endl;
	varout();
	SDL_FillRect(surf,NULL,0x00ffffff);
	SDL_Rect* rec=new SDL_Rect;
	rec->w=block;
	rec->h=block;
	for(int yy=0;yy<height;yy++){
		for(int xx=0;xx<width;xx++){
			rec->x=xx*block+(MAXWIDTH-width*block)/2;
			rec->y=yy*block+(MAXHEIGHT-block*height)/2;
			SDL_FillRect(surf,rec,(Uint32)COLOR[gamemap[yy][xx]]);
		}
	}
	rec->w=kb;
	rec->h=kb;
	for(int o=0;o<2;o++){
		for(int i=0;i<5;i++){
			int q=canchoosecolors[i];
			rec->x=((MAXWIDTH-width*block)/2-kb)/2+((o==1)?( (MAXWIDTH-width*block)/2+width*block ):0);
			rec->y=(MAXHEIGHT/7-kb)/2+MAXHEIGHT/7*q;
			if(SDL_UpperBlit(pic[(keyon==q&&lr==o)?1:0][q],NULL,surf,rec)<0) fpout<<"Blit bucket "<<o<<q<<((keyon==q&&lr==o)?" big":" small")<<" error!"<<endl<<SDL_GetError()<<endl;
		}
	} 
		
	SDL_UpdateWindowSurface(wind);
	varout();
	fout<<"end flashmap"<<endl; 
}
int pour(){
	fout<<endl<<"do pour:"<<endl<<endl;
	varout();
	int bfsarray[MAXN][2];
	int l=0,r=0,num=1;
	int fromcolor;
	if(lr==0){
		fromcolor=gamemap[height-1][0];
		leftcolor=keyon;
		bfsarray[0][0]=0;
		bfsarray[0][1]=height-1;
	}else{
		fromcolor=gamemap[0][width-1];
		rightcolor=keyon;
		bfsarray[0][0]=width-1;
		bfsarray[0][1]=0;
	}
	int pourcolor=keyon;
	//cout<<fromcolor<<' '<<pourcolor<<endl;//for test
	//cout<<bfsarray[0][0]<<' '<<bfsarray[0][1]<<endl;//for test
	bool stopbfs=false;
	while(!stopbfs){
		stopbfs=true;
		for(int i=l;i<=r;i++){
			gamemap[bfsarray[i][1]][bfsarray[i][0]]=pourcolor;
			
			if(bfsarray[i][1]<height-1){
				if(gamemap[bfsarray[i][1]+1][bfsarray[i][0]  ]==fromcolor){
					bfsarray[num][0]=bfsarray[i][0];
					bfsarray[num][1]=bfsarray[i][1]+1;
					gamemap[bfsarray[num][1]][bfsarray[num][0]]=pourcolor;
					if((bfsarray[num][0]==1||bfsarray[num][0]==0)&&(bfsarray[num][1]==1||bfsarray[num][1]==0)){
						//cout<<"catch error!!!at:  "<<bfsarray[i][0]<<'_'<<bfsarray[i][1]<<endl;
					}
					num++;
					stopbfs=false;
				}
			}
			if(bfsarray[i][1]>0){
				if(gamemap[bfsarray[i][1]-1][bfsarray[i][0]  ]==fromcolor){
					bfsarray[num][0]=bfsarray[i][0];
					bfsarray[num][1]=bfsarray[i][1]-1;
					gamemap[bfsarray[num][1]][bfsarray[num][0]]=pourcolor;
					if((bfsarray[num][0]==1||bfsarray[num][0]==0)&&(bfsarray[num][1]==1||bfsarray[num][1]==0)){
						//cout<<"catch error!!!at:  "<<bfsarray[i][0]<<'_'<<bfsarray[i][1]<<endl;
					}
					num++;
					stopbfs=false;
				}
			}
			if(bfsarray[i][0]<width-1){
				if(gamemap[bfsarray[i][1]  ][bfsarray[i][0]+1]==fromcolor){
					bfsarray[num][0]=bfsarray[i][0]+1;
					bfsarray[num][1]=bfsarray[i][1];
					gamemap[bfsarray[num][1]][bfsarray[num][0]]=pourcolor;
					if((bfsarray[num][0]==1||bfsarray[num][0]==0)&&(bfsarray[num][1]==1||bfsarray[num][1]==0)){
						//cout<<"catch error!!!at:  "<<bfsarray[i][0]<<'_'<<bfsarray[i][1]<<endl;
					}
					num++;
					stopbfs=false;
				}
			}
			if(bfsarray[i][0]>0){
				if(gamemap[bfsarray[i][1]  ][bfsarray[i][0]-1]==fromcolor){
					bfsarray[num][0]=bfsarray[i][0]-1;
					bfsarray[num][1]=bfsarray[i][1];
					gamemap[bfsarray[num][1]][bfsarray[num][0]]=pourcolor;
					if((bfsarray[num][0]==1||bfsarray[num][0]==0)&&(bfsarray[num][1]==1||bfsarray[num][1]==0)){
						//cout<<"catch error!!!at:  "<<bfsarray[i][0]<<'_'<<bfsarray[i][1]<<endl;
					}
					num++;
					stopbfs=false;
				}
			}
			
			fout<<(int)bfsarray[i][0]<<'_'<<(int)bfsarray[i][1]<<endl;
		}

		fout<<endl<<l<<"__"<<r<<"  "<<fromcolor<<endl<<endl;

		if(!stopbfs){
			flashmap(surf);
			SDL_Delay(0x00000032);
		}
		
		l=r+1;
		r=num-1;
		/* 
		for(int i=0;i<height;i++){           //for test
			for(int j=0;j<width;j++) 
				cout<<(int)gamemap[i][j];
			cout<<endl;
		}
		*/
	}
	
	fout<<endl<<"end pour"<<endl<<endl;
}
//bfspoured计算哪些方块是被左边玩家倒了油漆的，哪些是被右边到过油漆的，哪些没有被到过油漆 
int bfspoured(){
	int fromcolor;
	for(int i=0;i<height;i++){ 
		for(int j=0;j<width;j++) 
			poured[i][j]=0;
	}
	for(int LR=0;LR<=1;LR++){
	int l=0,r=0,num=1;
	int bfsarray[MAXN][2];
	//cout<<LR<<endl;	//for test
	if(LR==0){
		fromcolor=gamemap[height-1][0];
		bfsarray[0][0]=0;
		bfsarray[0][1]=height-1;
	}else{
		fromcolor=gamemap[0][width-1];
		bfsarray[0][0]=width-1;
		bfsarray[0][1]=0;
	}
	//cout<<fromcolor<<' '<<pourcolor<<endl;//for test
	//cout<<bfsarray[0][0]<<' '<<bfsarray[0][1]<<endl;//for test
	bool stopbfs=false;
	while(!stopbfs){
		stopbfs=true;
		for(int i=l;i<=r;i++){
			
			if(LR==0){
				poured[bfsarray[i][1]][bfsarray[i][0]]=1;
			}else{
				poured[bfsarray[i][1]][bfsarray[i][0]]=2;
			}
			
			if(bfsarray[i][1]<height-1){
				if(gamemap[bfsarray[i][1]+1][bfsarray[i][0]  ]==fromcolor && poured[bfsarray[i][1]+1][bfsarray[i][0]  ]==0){
					bfsarray[num][0]=bfsarray[i][0];
					bfsarray[num][1]=bfsarray[i][1]+1;
					if((bfsarray[num][0]==1||bfsarray[num][0]==0)&&(bfsarray[num][1]==1||bfsarray[num][1]==0)){
						//cout<<"catch error!!!at:  "<<bfsarray[i][0]<<'_'<<bfsarray[i][1]<<endl;
					}
					num++;
					stopbfs=false;
				}
			}
			if(bfsarray[i][1]>0){
				if(gamemap[bfsarray[i][1]-1][bfsarray[i][0]  ]==fromcolor&&poured[bfsarray[i][1]-1][bfsarray[i][0]  ]==0){
					bfsarray[num][0]=bfsarray[i][0];
					bfsarray[num][1]=bfsarray[i][1]-1;
					if((bfsarray[num][0]==1||bfsarray[num][0]==0)&&(bfsarray[num][1]==1||bfsarray[num][1]==0)){
						//cout<<"catch error!!!at:  "<<bfsarray[i][0]<<'_'<<bfsarray[i][1]<<endl;
					}
					num++;
					stopbfs=false;
				}
			}
			if(bfsarray[i][0]<width-1){
				if(gamemap[bfsarray[i][1]  ][bfsarray[i][0]+1]==fromcolor&&poured[bfsarray[i][1]][bfsarray[i][0]+1]==0){
					bfsarray[num][0]=bfsarray[i][0]+1;
					bfsarray[num][1]=bfsarray[i][1];
					if((bfsarray[num][0]==1||bfsarray[num][0]==0)&&(bfsarray[num][1]==1||bfsarray[num][1]==0)){
						//cout<<"catch error!!!at:  "<<bfsarray[i][0]<<'_'<<bfsarray[i][1]<<endl;
					}
					num++;
					stopbfs=false;
				}
			}
			if(bfsarray[i][0]>0){
				if(gamemap[bfsarray[i][1]  ][bfsarray[i][0]-1]==fromcolor&&poured[bfsarray[i][1]][bfsarray[i][0]-1]==0){
					bfsarray[num][0]=bfsarray[i][0]-1;
					bfsarray[num][1]=bfsarray[i][1];
					if((bfsarray[num][0]==1||bfsarray[num][0]==0)&&(bfsarray[num][1]==1||bfsarray[num][1]==0)){
						//cout<<"catch error!!!at:  "<<bfsarray[i][0]<<'_'<<bfsarray[i][1]<<endl;
					}
					num++;
					stopbfs=false;
				}
			}
			
			//cout<<(int)bfsarray[i][0]<<'_'<<(int)bfsarray[i][1]<<endl;	//for test
		}

		//cout<<endl<<l<<"__"<<r<<endl<<endl;	//for test
		
		/*
		for(int i=0;i<height;i++){           //for test
			for(int j=0;j<width;j++) 
				cout<<(int)poured[i][j];
			cout<<endl;
		}
		*/
		l=r+1;
		r=num-1;
		
	}
	}
}
bool decidetoend(){
	bfspoured();
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			if(poured[i][j]==0){
				return false;
			}
		}
	}
	return true;
} 
long sum(){
	long a=0,b=0;
	bfspoured();
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			if(poured[i][j]==1){
				a++;
			}else if(poured[i][j]==2){
				b++;
			}
		}
	}
	a=a*1000;
	a+=b;
	return a;
}

int main(int argc,char* args[]){
	int ch;
	SDL_Init(SDL_INIT_EVERYTHING);
	cout<<"pourwar\n油漆桶工具大战"<<endl;
	cout<<"图片的高度有多少个像素："; 
	cin>>height;
	while(height>=240||height<5){
		cout<<"输入数值似乎有点不合理.....为了适配您的显示屏，请将高度设定为5~100的数值"<<endl;
		cout<<"请输入高度：";
		cin>>height; 
	} 
	cout<<endl<<"Tips:左边玩家请使用W键和S键移动光标，右边玩家请使用↑键和↓键移动光标，左右玩家都是用空格键倒油漆\n如果游戏过程中想要退出的话请按esc键"<<endl;
	cout<<endl<<"加载中";
	for(int i=0;i<40;i++){
		cout<<'.';
		SDL_Delay(0x00000064);
	}
	wind=SDL_CreateWindow("POURWAR",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1,1,SDL_WINDOW_MAXIMIZED);
	surf=SDL_GetWindowSurface(wind);
	SDL_FillRect(surf,NULL,0x00ffffff);
	for(int i=0;i<2;i++){
		for(int j=0;j<7;j++){
			string str="./code/buckets/bucket";
			str+=(char)(i+48);
			str+=(char)(j+48);
			str+=".bmp";
			char ch[str.length()];
			for(int o=0;o<str.length();o++){
				ch[o]=str[o];
			} 
			pic[i][j]=SDL_LoadBMP(ch);
			if(pic[i][j]==NULL) fpout<<"load bucket "<<i<<j<<" error!"<<endl<<SDL_GetError()<<endl; 
		}
	}
	ico=SDL_LoadBMP("./code/icon3.bmp");
	if(ico==NULL) fpout<<"load icon error!"<<endl<<SDL_GetError()<<endl;
	SDL_SetWindowIcon(wind,ico);
	
	SDL_GetWindowSize(wind,&MAXWIDTH,&MAXHEIGHT);
	block=MAXHEIGHT/height;
	width=(MAXWIDTH-(kb*2))/block;
	
	srand((int)time(NULL));
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			gamemap[i][j]=rand()%7;
			poured[i][j]=0;
			//if(i>=height-2&&i<=height-1&&j>=0&&j<=1)gamemap[i][j]=COLOR[2]; 
		}
	}
	gamemap[height-1][0]=leftcolor;
	gamemap[0][width-1]=rightcolor;
	poured[height-1][0]=1;
	poured[0][width-1]=2;
	/*for test
	pour();
	flashmap(surf);
	*///for test
	//计算可选的颜色（左右玩家当时油漆桶的颜色都不能选）按从小到大（0~6）的顺序存储在canchoosecolors数组中 
	//keyonwhichccc存储是光标在第几个可选的颜色 
	//这个计算在开头做，也在倒油漆的时候做 
	fout<<"do canchoosecolors:";
	for(int i=0,a=0;i<7;i++){
		if(leftcolor!=i&&rightcolor!=i){
			canchoosecolors[a]=i;
			if(i==keyon){
				keyonwhichccc=a;
				fout<<"keyonwhichccc:"<<keyonwhichccc<<endl;
			}
			a++;
		} 
		for(int i=0;i<5;i++)
		fout<<canchoosecolors[i]<<' ';
		fout<<endl;
	}
	fout<<"end canchoosecolors"<<endl;
	flashmap(surf);
	ch=0;
	while(!end){
		//cout<<ch<<endl;
		bool get=false;
    	SDL_Event gameEvent;
		if( SDL_PollEvent(&gameEvent) !=0 ){
			if(gameEvent.type == SDL_KEYDOWN ){
				//cout<<"Event:keydown"<<endl;
				get=true;
				ch=gameEvent.key.keysym.sym;
			}
		}
		if(get){
			if((ch==SDLK_UP&&lr==1)||(ch==SDLK_w&&lr==0)){
				if(keyonwhichccc>0)
					keyonwhichccc--;
				keyon=canchoosecolors[keyonwhichccc];
				flashmap(surf);
			}
			if((ch==SDLK_DOWN&&lr==1)||(ch==SDLK_s&&lr==0)){
				if(keyonwhichccc<4) 
					keyonwhichccc++;
				keyon=canchoosecolors[keyonwhichccc];
				flashmap(surf);
			}
			
			if(ch==SDLK_SPACE){
				keyon=canchoosecolors[keyonwhichccc];//keyon表示光标在全部颜色中指向第几个，是全局变量，pour函数需要引用到 
				pour();//cout<<"pour!";
				lr=(lr==0)?1:0;//左边玩家pour完了，当然要轮到右边玩家了啊！ 
				fout<<endl<<"do canchoosecolors"<<endl<<endl;
				for(int i=0,a=0;i<7;i++){
					if(leftcolor!=i&&rightcolor!=i){
						canchoosecolors[a]=i;
						a++;
					} 
					
					for(int i=0;i<5;i++)
					fout<<canchoosecolors[i]<<' ';
					fout<<endl;
				}
				fout<<endl<<"end canchoosecolors"<<endl;
				/*
				for(int i=0;i<height;i++){           //for test
					for(int j=0;j<width;j++) 
						cout<<(int)gamemap[i][j];
					cout<<endl;
				}
				*/
				keyonwhichccc=0;
				keyon=canchoosecolors[keyonwhichccc];
				flashmap(surf);
				if(decidetoend()) end=true;
			}
			
			if(ch==SDLK_ESCAPE) end=true;
		}
		flashmap(surf);
		SDL_Event windevent;
		while(SDL_PollEvent(&windevent)!=0){
			if(windevent.type == SDL_WINDOWEVENT){
				if(windevent.window.event == SDL_WINDOWEVENT_CLOSE){
					end=true;
					//cout<<endl<<"get event:close";
				}
			}
		}
		SDL_Delay(0x00000016);
	}
	for(int o=0;o<2;o++){
		for(int i=0;i<7;i++){
			SDL_FreeSurface(pic[o][i]);
		}
	}
	SDL_FreeSurface(surf);
	SDL_DestroyWindow(wind);
	SDL_Quit();
	fout.close();
	fin.close();
	fpout.close();
	fpin.close();
	long a,b;
	a=sum();
	b=a%1000;
	a=a/1000;
	cout<<"游戏结束，结算：\n左下方的油漆桶倒出了"<<a<<"个方格的油漆\n右上方的油漆桶倒出了"<<b<<"个方格的油漆\n"<<(a>b?"左下玩家获胜！":(a<b?"右上玩家获胜!":"恭喜你们，打平了！（你们有毒啊！！！！！）")); 
	char chh;
	cout<<"按几下空格键以结束游戏";
	chh=getch();
	while(chh!=' ') {
		chh=getch(); 
		//cout<<chh;
	}
	return 0;
}
