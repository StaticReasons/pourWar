
//Creater : MysteryLJR

#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <conio.h>
#include <cstring>
#ifndef __ANDROID__
#include "bits/stdc++.h"
#endif
#define RED 0x00e03200		// R:224	G:50	B:0
#define ORANGE 0x00e0c000	// R:224	G:192	B:0
#define YELLOW 0x00f0f000	// R:224	G:224	B:0
#define GREEN 0x0000c000	// R:0		G:192	B:0
#define AQUA 0x0000c0c0		// R:0 		G:192 	B:192
#define BLUE 0x000000c0		// R:0 		G:0 	B:192
#define PURPLE 0x00c000c0	// R:192 	G:0 	B:192

#define MAXN 10000 //for bfs

#ifndef SDL_SRCCOLORKEY
#define SDL_SRCCOLORKEY 1
#endif
 
using namespace std;

int MAXWIDTH=1280;
int MAXHEIGHT=960;
int height,width;
int block=20;
int kb=150;
int mouseon=0;
bool mouseonanybutton=false;
int lr=0;
int leftcolor=5;
int rightcolor=6;
int canchoosecolors[5];
int keyonwhichccc=0;
int step=0;
int mapsize=0;
bool ai=false;
bool startlog=false;
bool cross=false;
bool pouring=false;
#ifdef  __ANDROID__
bool os=true;
#else
bool os=false;//0=���ԣ�1=�ֻ� 
#endif
int COLOR[7]={
	RED,
	ORANGE,
	YELLOW,
	GREEN,
	AQUA,
	BLUE,
	PURPLE
};

//bool end=false;

Uint8 gamemap[MAXN][MAXN];
Uint8 poured[MAXN][MAXN]; 

fstream fout;//("./code/log.txt",ios::out|ios::trunc);
fstream fpout("./code/piclog.txt",ios::out|ios::trunc);

SDL_Rect rect;
SDL_Surface* surf;
SDL_Window* wind;
SDL_Surface* pic[2][7]; 
SDL_Surface* ico; 
SDL_Surface* menu[2][3];
SDL_Surface* end0;
SDL_Surface* end1;
SDL_Surface* start;
SDL_Surface* home;
/*
int resizesurface(SDL_Surface* surf,int w,int h){
	SDL_Surface surf1= *surf;
	SDL_FreeSurface(surf);
	
}
*/
int varout(){
	if(startlog){
	fout<<"varout:"<<endl;
	fout<<"height:"<<height<<endl;
	fout<<"width:"<<width<<endl;
	fout<<"block:"<<block<<endl;
	fout<<"kb:"<<kb<<endl;
	fout<<"mouseon:"<<mouseon<<endl;
	fout<<"lr:"<<lr<<endl;
	fout<<"leftcolor:"<<leftcolor<<endl;
	fout<<"rightcolor:"<<rightcolor<<endl;
	fout<<"ai:"<<ai<<endl;
	fout<<"mapsize:"<<mapsize<<endl;
	fout<<"step:"<<step<<endl;
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
}
int flashmap(SDL_Surface* surf,bool turn=false){
	if(startlog)fout<<endl<<"do flashmap:"<<endl;
	varout();
	//SDL_Surface* ntsuf=SDL_CreateRGBSurfaceWithFormat(0,max(surf->w,surf->h),min(surf->w,surf->h),8,surf->format);
	SDL_Rect* rec=new SDL_Rect;
	switch(step){
	case 0:
		SDL_FillRect(surf,NULL,0x00ffffff);
		*rec={MAXWIDTH/2-150,MAXHEIGHT/4-20,300,40};
		SDL_UpperBlit(menu[0][ai?1:0],NULL,surf,rec);
		*rec={MAXWIDTH/2-150,MAXHEIGHT/4*2-20,300,40};
		SDL_UpperBlit(menu[1][mapsize],NULL,surf,rec);
		*rec={MAXWIDTH/2-150,MAXHEIGHT/4*3-50,300,100};
		SDL_UpperBlit(start,NULL,surf,rec);
		break;
	case 1:
		SDL_FillRect(surf,NULL,0x00ffffff);
		rec->w=block;
		rec->h=block;
		for(int yy=0;yy<height;yy++){
			for(int xx=0;xx<width;xx++){
				rec->x=xx*block+(MAXWIDTH-width*block-kb*2)/2+kb;
				rec->y=yy*block+(MAXHEIGHT-50-block*height)/2+50;
				SDL_FillRect(surf,rec,(Uint32)COLOR[gamemap[yy][xx]]);
			}
		}
		rec->w=kb;
		rec->h=kb;
		for(int o=0;o<2;o++){
			if(lr!=o) continue;
			for(int i=0;i<7;i++){
				rec->x=(((MAXWIDTH-width*block)/2-kb)/2<0?0:((MAXWIDTH-width*block)/2-kb)/2)+((o==1)?( (MAXWIDTH-width*block)/2+width*block ):0);
				
				rec->y=((MAXHEIGHT-50)/7-kb)/2+(MAXHEIGHT-50)/7*i+50;
				if(i!=leftcolor&&i!=rightcolor)
				if(SDL_UpperBlit(pic[(mouseon==i&&mouseonanybutton)?1:0][i],NULL,surf,rec)<0) if(startlog)fpout<<"Blit bucket "<<o<<i<<((mouseon==i&&lr==o)?" big":" small")<<" error!"<<endl<<SDL_GetError()<<endl;
			}
		}
		rec->w=50;
		rec->h=50;
		rec->x=MAXWIDTH/2-25;
		rec->y=0;
		if(SDL_UpperBlit(home,NULL,surf,rec)<0) if(startlog)fpout<<"Blit home "<<" error!"<<endl<<SDL_GetError()<<endl;
		break;
	} 
		
	SDL_UpdateWindowSurface(wind);
	varout();
	
	if(startlog)fout<<"end flashmap"<<endl; 
}
int pour(){
	if(startlog)fout<<endl<<"do pour:"<<endl<<endl;
	varout();
	int bfsarray[MAXN][2];
	int l=0,r=0,num=1;
	int fromcolor;
	if(lr==0){
		fromcolor=gamemap[height-1][0];
		leftcolor=mouseon;
		bfsarray[0][0]=0;
		bfsarray[0][1]=height-1;
	}else{
		fromcolor=gamemap[0][width-1];
		rightcolor=mouseon;
		bfsarray[0][0]=width-1;
		bfsarray[0][1]=0;
	}
	int pourcolor=mouseon;
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
			
			if(startlog)fout<<(int)bfsarray[i][0]<<'_'<<(int)bfsarray[i][1]<<endl;
		}

		if(startlog)fout<<endl<<l<<"__"<<r<<"  "<<fromcolor<<endl<<endl;

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
	
	if(startlog)fout<<endl<<"end pour"<<endl<<endl;
}
int aiplay(){
	int pourget[7];
	for(int c=0;c<7;c++){
		if(c==leftcolor||c==rightcolor)continue;
		Uint8 map[height][width];
		for(int i=0;i<height;i++)
			for(int j=0;j<width;j++)
				map[i][j]=gamemap[i][j];
		
		int bfsarray[MAXN][2];
		int l=0,r=0,num=1;
		int fromcolor=map[0][width-1];
		int pourcolor=c;
		bfsarray[0][0]=width-1;
		bfsarray[0][1]=0;
		//cout<<fromcolor<<' '<<pourcolor<<endl;//for test
		//cout<<bfsarray[0][0]<<' '<<bfsarray[0][1]<<endl;//for test
		bool stopbfs=false;
		while(!stopbfs){
			stopbfs=true;
			for(int i=l;i<=r;i++){
				map[bfsarray[i][1]][bfsarray[i][0]]=pourcolor;
				
				if(bfsarray[i][1]<height-1){
					if(map[bfsarray[i][1]+1][bfsarray[i][0]  ]==fromcolor){
						bfsarray[num][0]=bfsarray[i][0];
						bfsarray[num][1]=bfsarray[i][1]+1;
						map[bfsarray[num][1]][bfsarray[num][0]]=pourcolor;
						if((bfsarray[num][0]==1||bfsarray[num][0]==0)&&(bfsarray[num][1]==1||bfsarray[num][1]==0)){
							//cout<<"catch error!!!at:  "<<bfsarray[i][0]<<'_'<<bfsarray[i][1]<<endl;
						}
						num++;
						stopbfs=false;
					}
				}
				if(bfsarray[i][1]>0){
					if(map[bfsarray[i][1]-1][bfsarray[i][0]  ]==fromcolor){
						bfsarray[num][0]=bfsarray[i][0];
						bfsarray[num][1]=bfsarray[i][1]-1;
						map[bfsarray[num][1]][bfsarray[num][0]]=pourcolor;
						if((bfsarray[num][0]==1||bfsarray[num][0]==0)&&(bfsarray[num][1]==1||bfsarray[num][1]==0)){
							//cout<<"catch error!!!at:  "<<bfsarray[i][0]<<'_'<<bfsarray[i][1]<<endl;
						}
						num++;
						stopbfs=false;
					}
				}
				if(bfsarray[i][0]<width-1){
					if(map[bfsarray[i][1]  ][bfsarray[i][0]+1]==fromcolor){
						bfsarray[num][0]=bfsarray[i][0]+1;
						bfsarray[num][1]=bfsarray[i][1];
						map[bfsarray[num][1]][bfsarray[num][0]]=pourcolor;
						if((bfsarray[num][0]==1||bfsarray[num][0]==0)&&(bfsarray[num][1]==1||bfsarray[num][1]==0)){
							//cout<<"catch error!!!at:  "<<bfsarray[i][0]<<'_'<<bfsarray[i][1]<<endl;
						}
						num++;
						stopbfs=false;
					}
				}
				if(bfsarray[i][0]>0){
					if(map[bfsarray[i][1]  ][bfsarray[i][0]-1]==fromcolor){
						bfsarray[num][0]=bfsarray[i][0]-1;
						bfsarray[num][1]=bfsarray[i][1];
							map[bfsarray[num][1]][bfsarray[num][0]]=pourcolor;
						if((bfsarray[num][0]==1||bfsarray[num][0]==0)&&(bfsarray[num][1]==1||bfsarray[num][1]==0)){
							//cout<<"catch error!!!at:  "<<bfsarray[i][0]<<'_'<<bfsarray[i][1]<<endl;
						}
						num++;
						stopbfs=false;
					}
				}
				
				//fout<<(int)bfsarray[i][0]<<'_'<<(int)bfsarray[i][1]<<endl;
			}
	
			//fout<<endl<<l<<"__"<<r<<"  "<<fromcolor<<endl<<endl;
			l=r+1;
			r=num-1;
			/* 
			for(int i=0;i<height;i++){           //for test
				for(int j=0;j<width;j++) 
					cout<<(int)map[i][j];
				cout<<endl;
			}
			*/
		}
		
		l=0,r=0,num=1;
		bfsarray[0][0]=width-1;
		bfsarray[0][1]=0;
		fromcolor=map[0][width-1];
		pourcolor=7;
		//cout<<fromcolor<<' '<<pourcolor<<endl;//for test
		//cout<<bfsarray[0][0]<<' '<<bfsarray[0][1]<<endl;//for test
		stopbfs=false;
		while(!stopbfs){
			stopbfs=true;
			for(int i=l;i<=r;i++){
				map[bfsarray[i][1]][bfsarray[i][0]]=pourcolor;
				
				if(bfsarray[i][1]<height-1){
					if(map[bfsarray[i][1]+1][bfsarray[i][0]  ]==fromcolor){
						bfsarray[num][0]=bfsarray[i][0];
						bfsarray[num][1]=bfsarray[i][1]+1;
						map[bfsarray[num][1]][bfsarray[num][0]]=pourcolor;
						if((bfsarray[num][0]==1||bfsarray[num][0]==0)&&(bfsarray[num][1]==1||bfsarray[num][1]==0)){
							//cout<<"catch error!!!at:  "<<bfsarray[i][0]<<'_'<<bfsarray[i][1]<<endl;
						}
						num++;
						stopbfs=false;
					}
				}
				if(bfsarray[i][1]>0){
					if(map[bfsarray[i][1]-1][bfsarray[i][0]  ]==fromcolor){
						bfsarray[num][0]=bfsarray[i][0];
						bfsarray[num][1]=bfsarray[i][1]-1;
						map[bfsarray[num][1]][bfsarray[num][0]]=pourcolor;
						if((bfsarray[num][0]==1||bfsarray[num][0]==0)&&(bfsarray[num][1]==1||bfsarray[num][1]==0)){
							//cout<<"catch error!!!at:  "<<bfsarray[i][0]<<'_'<<bfsarray[i][1]<<endl;
						}
						num++;
						stopbfs=false;
					}
				}
				if(bfsarray[i][0]<width-1){
					if(map[bfsarray[i][1]  ][bfsarray[i][0]+1]==fromcolor){
						bfsarray[num][0]=bfsarray[i][0]+1;
						bfsarray[num][1]=bfsarray[i][1];
						map[bfsarray[num][1]][bfsarray[num][0]]=pourcolor;
						if((bfsarray[num][0]==1||bfsarray[num][0]==0)&&(bfsarray[num][1]==1||bfsarray[num][1]==0)){
							//cout<<"catch error!!!at:  "<<bfsarray[i][0]<<'_'<<bfsarray[i][1]<<endl;
						}
						num++;
						stopbfs=false;
					}
				}
				if(bfsarray[i][0]>0){
					if(map[bfsarray[i][1]  ][bfsarray[i][0]-1]==fromcolor){
						bfsarray[num][0]=bfsarray[i][0]-1;
						bfsarray[num][1]=bfsarray[i][1];
						map[bfsarray[num][1]][bfsarray[num][0]]=pourcolor;
						if((bfsarray[num][0]==1||bfsarray[num][0]==0)&&(bfsarray[num][1]==1||bfsarray[num][1]==0)){
							//cout<<"catch error!!!at:  "<<bfsarray[i][0]<<'_'<<bfsarray[i][1]<<endl;
						}
						num++;
						stopbfs=false;
					}
				}
				
				//fout<<(int)bfsarray[i][0]<<'_'<<(int)bfsarray[i][1]<<endl;
			}
	
			//fout<<endl<<l<<"__"<<r<<"  "<<fromcolor<<endl<<endl;
			l=r+1;
			r=num-1;
			/* 
			for(int i=0;i<height;i++){           //for test
				for(int j=0;j<width;j++) 
					cout<<(int)map[i][j];
				cout<<endl;
			}
			*/
		}
		pourget[c]=num;
	}
	int res=0;
	while(res==leftcolor||res==rightcolor)res++;
	for(int i=1;i<7;i++){
		if(i==leftcolor||i==rightcolor)continue;
		if(pourget[i]>pourget[res])res=i;
	}/*
	int res1=0;
	while(res1==leftcolor||res1==rightcolor||res1==res)res1++;
	for(int i=0;i<7;i++){
		if(i==leftcolor||i==rightcolor||i==res)continue;
		if(pourget[i]>pourget[res1])res1=i; 
	}*/
	return res;
} 
//bfspoured������Щ�����Ǳ������ҵ�������ģ���Щ�Ǳ��ұߵ�������ģ���Щû�б��������� 
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
long sum(){
	if(startlog)fout<<"do sum:"<<endl;
	varout();
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
	varout();
	if(startlog)fout<<endl<<"result:"<<a<<endl;
	return a;
}
bool decidetoend(){
	if(startlog)fout<<"do decidetoend:"<<endl;
	varout();
	long a,b;
	bool res;
	long area=height*width;
	a=sum();
	b=a%1000;
	a=a/1000;
	res=(a>=area/2||b>=area/2);
	varout();
	if(startlog)fout<<endl<<"result:"<<res<<endl;
	return res;
} 
/*�浵��ʽһ��Ϊ��
	step(��Ϸ�����裩 
	ai(�Ƿ��˻���ս��1��0��  
	height(��ͼ�߶ȣ�
	width����ͼ���ȣ�
	leftcolor��������ɫ��
	rightcolor��������ɫ��
	lr(�ֵ���߻����ұߣ�0��ߣ�1�ұߣ� 
	pouring(�Ƿ����ڵ����ᣬ1��0�� 
*/ 
int save(){
	ofstream s("./code/save.txt",ios::out|ios::trunc);
	s<<step;
	if(step==0)return 0;
	s<<' '<<ai<<' '<<height<<' '<<width<<' '<<leftcolor<<' '<<rightcolor<<' '<<lr<<' '<<pouring<<endl;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			s<<(int)gamemap[i][j]<<' '; 
		}
		s<<endl;
	}
	s.close();
}
int load(){
	fout.open("./code/log.txt",ios::in);
	int a;
	fout>>a;
	startlog=(a==1);
	//cout<<startlog<<' '<<a<<endl;
	fout.close();
	fout.open("./code/log.txt",ios::out|ios::trunc);
	fout<<a<<endl;
	//cout<<startlog<<' '<<a<<endl;
	int b;
	ifstream s("./code/save.txt",ios::in);
	s>>step;
	if(step==0)return 0;
	s>>ai>>height>>width>>leftcolor>>rightcolor>>lr>>pouring;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			s>>b; 
			//cout<<b<<' ';
			gamemap[i][j]=b; 
		}
		//cout<<endl;
	}
	s.close();
	return 1;
}

int main(int argc,char* args[]){
	int ch;
	SDL_Init(SDL_INIT_EVERYTHING);
	bool end=false;	wind=SDL_CreateWindow("POURWAR",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1000,700,SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE|SDL_WINDOW_MAXIMIZED);
	surf=SDL_GetWindowSurface(wind);
	SDL_FillRect(surf,NULL,0x00ffffff);
	for(int i=0;i<2;i++){
		for(int j=0;j<7;j++){
			string str="./code/buckets/bucket";
			str+=(char)(i+48);
			str+=(char)(j+48);
			str+=".bmp";
			char ch[str.length()+1];
			for(int o=0;o<str.length();o++){
				ch[o]=str[o];
			} 
			ch[str.length()]='\0';
			pic[i][j]=SDL_LoadBMP(ch);
			SDL_SetColorKey(pic[i][j],1,SDL_MapRGB(pic[i][j]->format,0xff,0xff,0xff));
			if(pic[i][j]==NULL) fpout<<"load bucket "<<i<<j<<" error!"<<endl<<SDL_GetError()<<endl; 
		}
	}
	for(int i=0;i<2;i++)
		for(int j=0;j<3;j++){
			string str2="./code/menu/";
			str2+=(char)(i+48);
			str2+=(char)(j+48);
			str2+=".bmp";
			char ch2[50];
			for(int o=0;o<50;o++){
				ch2[o]=' ';
			} 
			//cout<<ch2<<endl;
			for(int o=0;o<str2.length();o++){
				ch2[o]=str2[o];
			} 
			ch2[str2.length()]='\0';
			menu[i][j]=SDL_LoadBMP(ch2);
			//cout<<str<<" "<<ch2<<endl;
			SDL_SetColorKey(menu[i][j],1,SDL_MapRGB(menu[i][j]->format,0xff,0xff,0xff));
			if(menu[i][j]==NULL) fpout<<"load menu "<<i<<j<<" error!"<<endl<<SDL_GetError()<<endl; 
		}
	end0=SDL_LoadBMP("./code/end/0.bmp");
	if(end0==NULL) fpout<<"load end0 error!"<<endl<<SDL_GetError()<<endl;
	SDL_SetColorKey(end0,SDL_SRCCOLORKEY,0x00ffffff);
	
	end1=SDL_LoadBMP("./code/end/1.bmp");
	if(end1==NULL) fpout<<"load end1 error!"<<endl<<SDL_GetError()<<endl;
	SDL_SetColorKey(end1,SDL_SRCCOLORKEY,0x00ffffff);
	
	start=SDL_LoadBMP("./code/start.bmp");
	if(start==NULL) fpout<<"load start error!"<<endl<<SDL_GetError()<<endl;
	SDL_SetColorKey(start,SDL_SRCCOLORKEY,0x00ffffff);
	
	home=SDL_LoadBMP("./code/home.bmp");
	if(home==NULL) fpout<<"load home error!"<<endl<<SDL_GetError()<<endl;
	SDL_SetColorKey(home,SDL_SRCCOLORKEY,0x00ffffff);
	
	ico=SDL_LoadBMP("./code/icon3.bmp");
	if(ico==NULL) fpout<<"load icon error!"<<endl<<SDL_GetError()<<endl;
	
	SDL_SetWindowIcon(wind,ico);
	
	SDL_GetWindowSize(wind,&MAXWIDTH,&MAXHEIGHT);
	
	if(load()) {
		cout<<1;
		goto maingame;
	}
	
	S:
	step=0;
	save();
	end=false;
	while(!end){
		SDL_GetWindowSize(wind,&MAXWIDTH,&MAXHEIGHT);
		SDL_Delay(5);
		SDL_Event menuEvent;
		while(SDL_PollEvent(&menuEvent)!=0){
			surf=SDL_GetWindowSurface(wind);
			SDL_GetWindowSize(wind,&MAXWIDTH,&MAXHEIGHT);
			SDL_FillRect(surf,NULL,0x00ffffff);
			flashmap(surf);
			if(menuEvent.type==SDL_MOUSEBUTTONDOWN){
				if(menuEvent.button.x>(MAXWIDTH-300)/2&&menuEvent.button.x<(MAXWIDTH-300)/2+300){
					if(menuEvent.button.y>MAXHEIGHT/4-20&&menuEvent.button.y<MAXHEIGHT/4+20){
						ai=!ai;
					}
					if(menuEvent.button.y>MAXHEIGHT/4*2-20&&menuEvent.button.y<MAXHEIGHT/4*2+20){
						mapsize=(++mapsize)%3;
					}
					if(menuEvent.button.y>MAXHEIGHT/4*3-50&&menuEvent.button.y<MAXHEIGHT/4*3+50){
						end=true;
					}
				}
			}else if(menuEvent.type==SDL_QUIT){
				end=true;
				cross=true;
				//cout<<"exi";
			}
		}
	}
	if(cross){
		save();
		for(int o=0;o<2;o++){
			for(int i=0;i<7;i++){
				SDL_FreeSurface(pic[o][i]);
			}
		}
		for(int o=0;o<2;o++){
			for(int i=0;i<3;i++){
				SDL_FreeSurface(menu[o][i]);
			}
		}
		SDL_FreeSurface(ico);
		SDL_FreeSurface(surf);
		SDL_DestroyWindow(wind);
		SDL_Quit();
		fout.close();
		fpout.close();
		return 0;
	}
	
	switch(mapsize){
	case 0:
		height=20;
		break;
	case 1:
		height=40;
		break;
	case 2:
		height=70;
		break;
	}
	
	block=(MAXHEIGHT-50)/height;
	width=(MAXWIDTH-(kb*2))/block;
	
	srand((int)time(NULL));
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			gamemap[i][j]=rand()%7;
			poured[i][j]=0;
			//if(i>=height-2&&i<=height-1&&j>=0&&j<=1)gamemap[i][j]=COLOR[2]; 
		}
	}
	maingame:
	step=1;
	gamemap[height-1][0]=leftcolor;
	gamemap[0][width-1]=rightcolor;
	poured[height-1][0]=1;
	poured[0][width-1]=2;
	
	cout<<22<<endl;
	SDL_Rect rec; 
	SDL_FillRect(surf,NULL,0x00ffffff);
	for(int i=0;i<2;i++){
		rec={MAXWIDTH/2-300/2,MAXHEIGHT/3*(i+1)};
	}
	
	save();
	flashmap(surf);
	int mousex,mousey;
	end=false;
	cross=false;
	while(!end){
		//cout<<ch<<endl;
		bool get=false;
    	SDL_Event gameEvent;
		while( SDL_PollEvent(&gameEvent) !=0 ){
			surf=SDL_GetWindowSurface(wind);
			SDL_GetWindowSize(wind,&MAXWIDTH,&MAXHEIGHT);
			block=min((MAXHEIGHT-50)/height,(MAXWIDTH-kb*2)/width);
			switch(gameEvent.type){
			case SDL_QUIT:
				end=true;
				cross=true;
				break;
			case SDL_MOUSEMOTION:
				mousex=gameEvent.motion.x;
				mousey=gameEvent.motion.y;
				if((lr&&mousex>MAXWIDTH-(MAXWIDTH-block*width)/2&&!ai)||(!lr&&mousex<(MAXWIDTH-block*width)/2)){
					mouseon=mousey/(MAXHEIGHT/7);
					mouseonanybutton=true;
				}
				else mouseonanybutton=false; 
				//cout<<"motion:"<<mousex<<" "<<mousey<<" "<<mouseon<<endl;
				flashmap(surf);
				break;
			case SDL_MOUSEBUTTONDOWN:
				mousex=gameEvent.button.x;
				mousey=gameEvent.button.y;
				
				if(mousex>(MAXWIDTH/2)-25&&mousex<(MAXWIDTH/2)+25&&mousey<50){
					end=true;
					break;
				}
				if(ai){
					if(	!lr
						&&mousex<(MAXWIDTH-block*width)/2
						&&mousey/(MAXHEIGHT/7)!=leftcolor
						&&mousey/(MAXHEIGHT/7)!=rightcolor){
						mouseon=mousey/(MAXHEIGHT/7);
						mouseonanybutton=true;
						save();
						pouring=true;
						end=decidetoend();
						if(end) break;
					}
					else mouseonanybutton=false;
				}
				else if((	lr
							&&mousex>MAXWIDTH-(MAXWIDTH-block*width)/2
							&&mousey/(MAXHEIGHT/7)!=rightcolor
							&&mousey/(MAXHEIGHT/7)!=leftcolor)
						||(	!lr
							&&mousex<(MAXWIDTH-block*width)/2
							&&mousey/(MAXHEIGHT/7)!=leftcolor
							&&mousey/(MAXHEIGHT/7)!=rightcolor)){
					mouseon=mousey/(MAXHEIGHT/7);
					mouseonanybutton=true;
					pouring=true;
					save();
					end=decidetoend();
					if(end) break;
				}
				else mouseonanybutton=false; 
				break;
			}
		} 
		if(pouring){
			if(ai){
				if(!lr){
					pour();
					lr=1;
				}else{
					flashmap(surf);
					SDL_Delay(700);
					mouseon=aiplay();
					SDL_Delay(700);
					pour();
					lr=0;
					pouring=false;
				}
			}
			else{
				pour();
				lr=(lr==0)?1:0;
				flashmap(surf);
				pouring=false;
			}
		}
		if(end) break;
		flashmap(surf);
	}
	if(cross) goto destructing;
	long a,b;
	a=sum();
	b=a%1000;
	a=a/1000;
	rect={(MAXWIDTH-300)/2,(MAXHEIGHT-200)/2,300,200};
	if(a>b) SDL_UpperBlit(end0,NULL,surf,&rect);
	else SDL_UpperBlit(end1,NULL,surf,&rect);
	SDL_UpdateWindowSurface(wind);
	end=false;
	cross=false;
	while(!end){
		SDL_Event endEvent;
		while(SDL_PollEvent(&endEvent)!=0){
			if(endEvent.type==SDL_MOUSEBUTTONDOWN){
				end=true;
			}else if(endEvent.type==SDL_QUIT){
				end=true;
				cross=true;
				//cout<<"exi";
			}
		}
	}
	goto S;
	destructing:
	for(int o=0;o<2;o++){
		for(int i=0;i<7;i++){
			SDL_FreeSurface(pic[o][i]);
		}
	}
	for(int o=0;o<2;o++){
		for(int i=0;i<3;i++){
			SDL_FreeSurface(menu[o][i]);
		}
	}
	SDL_FreeSurface(ico);
	SDL_FreeSurface(surf);
	SDL_DestroyWindow(wind);
	SDL_Quit();
	fout.close();
	fpout.close();
	cout<<"��Ϸ������㣺\n���·�������Ͱ������"<<a<<"��������\n���Ϸ�������Ͱ������"<<b<<"��������\n"<<(a>b?"������һ�ʤ��":(a<b?"������һ�ʤ!":"��ϲ���ǣ���ƽ�ˣ��������ж���������������")); 
	char chh;
	cout<<"�����¿ո���Խ�����Ϸ";
	chh=getch();
	while(chh!=' ') {
		chh=getch(); 
		//cout<<chh;
	}
	return 0;
}


//�´��ϻ�Ŀ�꣺����Ͱͼ�� 

//17.10.13
//���ƺ���һ�������׵Ĺ���
 
//17.10.14
//�þ�û��ϰbfs�� ���ڸ������������
 
//������Լ���д��һ��57�е�bfs

//zc�ĺ���ֻ��10�� 
//��ȥ 

//17.10.15
//����æ�Ż��ư�����ͼ��bmp......

//ps�ҽ����ٰ����� 

//��ſ 

//17.10.21
//�״α���.........cnnnnnnnnnnnmmmmnmnmnmmnmnmnmnmnmnmnmnmnmnmnmnmnmnmnmnmnmnm
//�ҿ��ܰ�װ��һ��ٵ�SDL ������bmp�ܰ���ɫ��ɺ�ɫ �ж�

//emmmmmm����Ӧ����photoshop̫�ӵ��˰ɸ�SDL��bmp��ʽ��һ��
//hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh 

//17.10.22
//��ȥ!!!!!!!!!!!!!!!!!!!!!!!!!!
//����ô��û���뵽�����ù�갡������
//����Ͳ��û����˵������Ϸ�����ˣ�ֱ�������ִ�������˵��W��S��upkey��downke���ƶ���꣡����
//���������Ҳţ�����

//������������ʵ�ֵ���OVO��Ҫ��		//cnmdһ�㶼���򵥣���ע10.28�� 
//�ٰ�main����ĸľʹ󹦸���ˣ����� 
 
//17.10.27 
//��ȥ�������ĸ���ϸ������ҹ��ϵͳ�򵥵ģ���
//�ӵ�canchoosecolors�㷨���Լ�������֣�

//��������������������ʵҲ���õ��ˡ�����������
 
//������Լ���д��250���еĴ���
//�ҿ������˸�ٴ���

//����ռ���ڴ�̫���˰�...........�����������⣡
//�������RGB��ɫ�����0~6�����ֱ�ʾ�������Ϸ�����ֻ��7����ɫ�������� 
//����������ҵ����̸�
 
//emmmmmmmmmm��ħ������������������������������ãã����
//��Ȼ��bfs����
//����Ϊʲô����Ե�޹ʴ����½ǵĵط�bfs�����Ͻǰ���������
//һ���ã

//17.10.28
//emmmmmmmmmmm����һ�ٽ���֮���Ȼ������� 
//�µ�catch error������
//������������������������������������2^65536��2^65536��2^65536 2^65536��MAXN��MAXN��MAXNMAXN��

//ȫ��ȥ����Ԫ�����������........ 
 
//��ȥ��������r�������1����������
//cnmcnmcnmcnmcnmcnmcnmcnmcnmcnm����ô���Է����ֵͼ�����
//��ĺ�֮�� һ���Ӿ�����O_OO__OO_______OO-------------------------OO������O 
//��ô˵�Ļ�......���ǾͿ��������ϵͳ�ˣ���
//�Ϳ�Ҫ�󹦸����

//����poured�ļ��루��ʾ��Щ���̱�Ⱦ��ɫ��............. 
//�ð���һ��ط����ò�����Ԫ 
 
//��ȥ�ⶫ���ж�������������
//bfs���������!!!
//����������Ҫȥ��һ�ٽ����ˣ�������������ʱ�䣨��
//�������Ҫͨ��QAQ�����ӦҪ��lmh���Ե�.......... 
//ͻȻ�����ҵĴ������Ѿ��ǵ�384���ˣ���������û����Щע�ͺ���־��

//�������ֳ���һ�ͽ��ţ�ЦcryЦcryЦcryЦcryЦcry 

//û�취�........ֻ�ܰѸ�ĵ�ͼ��bfs��ͳ�Ƶ��̵�bfs��߷ֿ���.......���� 
//Ȼ����4�η����Լ����˵ͼ����� 

//��ȥ��ԭ������ԭ����bfs!!!!��canchoosecolors�����ѡ��ɫʱ���˳�ʼ��a��!!!!���ŵ��ҸϽ����ĳɾֲ���� 
//���ڣ�������������û��bug����������󹦸�ɣ��������������������� 
//Ȼ���ҷ��ִ�������������������423�У����������Ҳ�������Զ�߲��˶��ٰɣ������� 
 
//17.10.29
//������Ӧ����ð���
//��Ҫ�ļ������⣺
//1.����ƶ����ˣ�ԭ�����˰�keyon��ֵ��canchoosecolors[keyonwhichccc]��
//2.��ɫ̫�ӽ�Ŀǰ�������ǳ��һЩ�����������һЩ����ɫ��ǳ��һЩ
//3.���ڿ���ԭ��Ŀǰ�Ѳ���Ҫcatch error���������̫�ࣩ��Ŀǰ�����ת��log.txt����־��������ˣ�
//Ŀǰ�ļ��������ѽ�����bfsʱ���ż��һ��Ƭ��ڡ�������gamemap���������0~6���������......Ŀǰ�޷������Ϊ��ֻ��ż����¼�==

//17.11.18
//�þ�û�������
//��Ȼ.....��һ��SDLԴ�뻹�����õģ��������ö��� 

//17.11.19
//mdzz bmp��ʽ��Ȼֻ����ô����ɫ
//Ҫ����SDL_image.h�ͺ���...... png������͸����........
 
//17.11.24
//���� �ѹ��ͱ����ɫ�� �ĳ�������ͰͼƬ������.....
//����� ��û�а����ҷֳ����........������ϣ�������������ʤ��ħ�ȣ�������ЦcryЦcryЦcry 

//18.8.20
//����tmd�һ���U��
//��ҪŪ��꣡�������� 

//18.8.22
//AS EASY AS ABC
//̫���˰�ι,����Ҫ����һ�°�����Ͱ��С
//��������Ӧ��  

//18.8.25
//�ȱ��ʲô����Ӧ�ˣ��Ͻ��AI�Ͳ˵��� 
