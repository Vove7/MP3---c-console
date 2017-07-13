#pragma once
#include<fstream>
#include<ctime>
#include<string>
#include<stdlib.h>
#include<Windows.h>
#include"Song.h"
const int N = 200;
using namespace std;
class PlayList {
private:
	Song song[N];
	int Songnum;
public:
	friend class MP3;
	PlayList() {
		Songnum = 0;
	}
	void ScanListFile() {
		//读取列表文件
		fstream mp3file("MP3文件列表.txt");
		if (!mp3file) {//若无文件
			cout << "\n\n\n未发现歌曲列表文件\n\n";
			cout << "是否扫描磁盘?\n\nY/N\n\n->";
			char ch;
		loop:
			cin >> ch;
			switch (ch) {
				case 'y':
				case 'Y': ScanDisk(); 
					break;//
				case 'n':
				case 'N':return;
				default: goto loop;
			}
		}
		else {//发现文件
			string name,path;
			for(Songnum = 0;! mp3file.eof() ; Songnum++){
				getline(mp3file, name,'#');
				song[Songnum].SetSongname(name);
				//mp3file >>"\"">> song[Songnum].Songname>>"\"";
				getline(mp3file, path, '\n');
				song[Songnum].Setpath(path);
				//mp3file >> song[Songnum].path;
			}
			mp3file.close();
			cout << "\n\n\t\t扫描完成.";
			cout << "\n\n\t\t进入主界面."; Sleep(350); cout << ".";
			Sleep(350); cout << "."; Sleep(300); cout << ".";
			Sleep(300); system("cls");
		}
	}

	 void DisplayList() {
		 system("cls");
		 cout << "\t\t歌曲列表\n" << endl<<endl;
		// cout << "曲名\t\t音乐人\t时长" << endl;
		 if (!Songnum) {
			 cout << "\n\n\n\t\t播放列表为空\n\n\n";
			 return;
		 }
		 for (int i = 0; i < Songnum; i++) {
			 cout   << i + 1 << "." << song[i].GetSongname();
			 //cout << "\t" << song[i].GetSingername();
			 cout << endl;
			 //cout << "\t" << song[i].GetTime() << "s" << endl;
		 }
		 cout << endl << endl;
	 }

	 void ScanDisk() {//扫描磁盘
		 system("cls");
		 cout << "输入扫描路径(例：E:\\0MUSIC)      0:返回\n\n->";
		 string scanfpath;
		 cin>> scanfpath;
		 if (scanfpath == "0")
			 return;
		 Songnum = 0;//清零
		 //读入MP3格式
		 cout << "\n正在扫描文件...";
		 WIN32_FIND_DATA songfile;
		 HANDLE first = FindFirstFile(((scanfpath + "\\*.mp3")).c_str(), &songfile);
		 //HANDLE first = FindFirstFile("E:\\0MUSIC\\*.mp3", &songfile);
		 while (FindNextFile(first, &songfile) && Songnum<N) {
			 //判断类型不为文件夹
			 if (!(songfile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				 song[Songnum].SetSongname(songfile.cFileName);
				 song[Songnum].Setpath (scanfpath+"\\");
				// song[Songnum].path = "E:\\0MUSIC\\";
				 Songnum++;
			 }
		 }
		 //读入wav格式
		 first = FindFirstFile((scanfpath + "\\*.wav").c_str(), &songfile);
		 //first = FindFirstFile("E:\\0MUSIC\\*.wav", &songfile);
		 while (FindNextFile(first, &songfile) && Songnum<N) {
			 song[Songnum].SetSongname ( songfile.cFileName);
			 song[Songnum].Setpath ("E:\\0MUSIC\\");
			 Songnum++;
		 }
		 FindClose(first);

		 if (Songnum == 0) {
			 cout << "\n\n\t\t未发现歌曲文件\n\n";
			 system("pause");
			 return;
		 }
		 else {
			 cout << "\n\n\t\t共扫描到" << Songnum << "首歌曲\n\n";
		 }
		 Sleep(800);
		 cout << "\n\n存入列表文件..";
		 ListSaveToFile();//存入
		 Sleep(800);
		 cout << "\n\n\t完成";
		 Sleep(500); cout << ".";
		 Sleep(500);
	 }
	 void ListSaveToFile() {

		 fstream listfile;
		 listfile.open("MP3文件列表.txt", ios::out);
		 for (int i = 0; i < Songnum; i++) {
			 listfile <<song[i].GetSongname() << "#";
			 listfile << song[i].Getpath() ;
			 if (i < Songnum-1)
				 listfile << "\n";
		 }
		 listfile.close();
	 }
};
