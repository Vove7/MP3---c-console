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
		//��ȡ�б��ļ�
		fstream mp3file("MP3�ļ��б�.txt");
		if (!mp3file) {//�����ļ�
			cout << "\n\n\nδ���ָ����б��ļ�\n\n";
			cout << "�Ƿ�ɨ�����?\n\nY/N\n\n->";
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
		else {//�����ļ�
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
			cout << "\n\n\t\tɨ�����.";
			cout << "\n\n\t\t����������."; Sleep(350); cout << ".";
			Sleep(350); cout << "."; Sleep(300); cout << ".";
			Sleep(300); system("cls");
		}
	}

	 void DisplayList() {
		 system("cls");
		 cout << "\t\t�����б�\n" << endl<<endl;
		// cout << "����\t\t������\tʱ��" << endl;
		 if (!Songnum) {
			 cout << "\n\n\n\t\t�����б�Ϊ��\n\n\n";
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

	 void ScanDisk() {//ɨ�����
		 system("cls");
		 cout << "����ɨ��·��(����E:\\0MUSIC)      0:����\n\n->";
		 string scanfpath;
		 cin>> scanfpath;
		 if (scanfpath == "0")
			 return;
		 Songnum = 0;//����
		 //����MP3��ʽ
		 cout << "\n����ɨ���ļ�...";
		 WIN32_FIND_DATA songfile;
		 HANDLE first = FindFirstFile(((scanfpath + "\\*.mp3")).c_str(), &songfile);
		 //HANDLE first = FindFirstFile("E:\\0MUSIC\\*.mp3", &songfile);
		 while (FindNextFile(first, &songfile) && Songnum<N) {
			 //�ж����Ͳ�Ϊ�ļ���
			 if (!(songfile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				 song[Songnum].SetSongname(songfile.cFileName);
				 song[Songnum].Setpath (scanfpath+"\\");
				// song[Songnum].path = "E:\\0MUSIC\\";
				 Songnum++;
			 }
		 }
		 //����wav��ʽ
		 first = FindFirstFile((scanfpath + "\\*.wav").c_str(), &songfile);
		 //first = FindFirstFile("E:\\0MUSIC\\*.wav", &songfile);
		 while (FindNextFile(first, &songfile) && Songnum<N) {
			 song[Songnum].SetSongname ( songfile.cFileName);
			 song[Songnum].Setpath ("E:\\0MUSIC\\");
			 Songnum++;
		 }
		 FindClose(first);

		 if (Songnum == 0) {
			 cout << "\n\n\t\tδ���ָ����ļ�\n\n";
			 system("pause");
			 return;
		 }
		 else {
			 cout << "\n\n\t\t��ɨ�赽" << Songnum << "�׸���\n\n";
		 }
		 Sleep(800);
		 cout << "\n\n�����б��ļ�..";
		 ListSaveToFile();//����
		 Sleep(800);
		 cout << "\n\n\t���";
		 Sleep(500); cout << ".";
		 Sleep(500);
	 }
	 void ListSaveToFile() {

		 fstream listfile;
		 listfile.open("MP3�ļ��б�.txt", ios::out);
		 for (int i = 0; i < Songnum; i++) {
			 listfile <<song[i].GetSongname() << "#";
			 listfile << song[i].Getpath() ;
			 if (i < Songnum-1)
				 listfile << "\n";
		 }
		 listfile.close();
	 }
};
