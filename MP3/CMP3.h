#pragma once
#include"CPlayList.h"
#include"Interface.h"
#include<mmsystem.h>//����ͷ�ļ�
#pragma comment (lib,"winmm.lib")//�������ӿ�
using namespace std;

class MP3 {
private:
	PlayList L;
	int now;//��ǰ����
	int PlayMode;//����ģʽ (0��δ��ʼ)(1����ʼ����) (2�����ڲ���) (3��������ͣ)
	int status;//����״̬
	int background_playstatus;//��������״̬
	char color;//Ƥ��
public:
	MP3() {
		BootAnimation();
	}
	void BootAnimation() {//��������
		setlocale(0, "chs");
		cout << "\n\n\t\t����ing.\n";
		for (int i = 0; i < 50; i++) {
			Sleep(20);
			cout << "-";
		}
		Sleep(100);
		system("cls");
	}
	void Launch() {
		LoadConf();//���������ļ�
		setlocale(0, "chs");
		cout << "\n\t\t��������б�...\n";
		status = 0;//����״̬ δ��ʼ
		background_playstatus = 0;
		L.ScanListFile();
		//�������˵�
		while (1)
			MainMenu();
	}
	void LoadConf() {
		fstream conf("MP3����.txt");
		if (!conf) {
			setlocale(0, "chs");
			cout << "\n\tδ���������ļ���ʹ�ó�ʼ�����á�\n";
			InitConf();//��ʼ��
			return;
		}
		else {//����
			conf >> now;		//�ϴβ��ż�¼
			conf >> PlayMode;   //���벥��ģʽ
			conf >> color; // Ƥ��
			char cmd[8] = "color  ";
			cmd[6] = color;
			ExecCmd(cmd);//����
			conf.close();
			setlocale(0, "chs");
			cout << "\t\t�����ļ�����ɹ�..\n";
		}
	}

	 void InitConf() { //������ʼ����
		 now = 0;
		 PlayMode = 1;
		 color = '7';
		 SaveConf();//����Ĭ�ϲ���
	}
	void MainMenu() {
		Main_Interface();//������
		int n;
	loop:
		cout << "->";
		cin >> n;
		switch (n) {
			case 0:  Shutdown();
			case 1: 
			if(L.Songnum){
				if (!status&&background_playstatus == 0)//���벥�Ž��������ں�̨����
					status = 1;//�л�״̬
				background_playstatus = 0;
				Play();//
			}
			else {
				system("cls");
				setlocale(0, "chs");
				cout << "\n\t��ǰ�����б��޸���\n\n" << endl;
				system("pause");
			}
			break;
			case 2: 
				if (SelectSong()) {//ѡ���������true
					background_playstatus = 0;//���벥��
					status = 1;//��ʼ
					SaveConf();
					Play();
				}
				//else �鿴
				break;
			case 3:
				StopPlay();
				now = 0;
				status = 0;
				background_playstatus = 0;
				L.ScanDisk();
				break;
			case 4:
				Setting();
				break;
			case 5:
				ShowAbout();//��ʾ
				break;
			default:
				goto loop;
		}
	}
	void Setting() {
		Setting_Interface();
		int n;
		loop:
		cout << "\n\n->";
		cin >> n;
		switch(n) {
			case 1: 
				SelectPlayMode();
				break;
			case 2:
				SetColor();
				break;
			case 0:
				break;
			default:
				setlocale(0, "chs"); cout << "����"; goto loop;
		}
	}
	void SetColor() {
		SetColor__Interface();
		char in=color;
		char cmd[8] = "color  ";

		do {
			color = in;
			cout << "->";
			cin >> in;
			cmd[6] = in;
			ExecCmd(cmd);
		} while (in != '0');

		SaveConf();
		setlocale(0, "chs");
		cout << "\n\n-------�ѱ���.";
		Sleep(400);
		cout << ".";
		Sleep(400);
		cout << ".";
		Sleep(400);
	}

	void SelectPlayMode() {
		SelectPlayMode_Interface();//����
		int n;
	loop:
		cout << "->";
		cin >> n;
		switch (n) {
			case 1: PlayMode = 1;
				break; 
			case 2: PlayMode = 2;
				break;
			case 3: PlayMode =3;
				break;
			case 0:	return;
			default:
				setlocale(0, "chs"); cout << "����"; goto loop;
		}
		SaveConf();
		setlocale(0, "chs");
		cout << "\n\n-------�ѱ���.";
		Sleep(400);
		cout << ".";
		Sleep(400);
		cout << ".";
		Sleep(400);
	}
	void SaveConf() {
		fstream conf;
		conf.open("MP3����.txt", ios::out);
		conf <<now<<" "<< PlayMode <<" "<< color;
		conf.close();
	}
	bool SelectSong() {
		L.DisplayList();//��ʾ�����б�
		cout << "0.����\n";
	loop:
		setlocale(0, "chs");
		cout << "ѡ��->";
		int n;
		cin >> n;
		if (n >L.Songnum||n<0) {
			goto loop;
		} 
		if (n) {
			now = n - 1;
			return true;
		}
		else return false;
	}
	void Play() {
	start:
		system("cls");
		if (!L.Songnum) {
			setlocale(0, "chs");
			cout << "\n\n\t�����б�Ϊ��,��������..";
			Sleep(1000);
			return;
		}
			if (status == 1 && !background_playstatus) {
				StartPlay();
			}
			if (now < 0 || now >= L.Songnum) {//����/��Ŵ���ʱ
				status = 1;
				now = 0;//
				goto start;
			}

			setlocale(0, "chs");
			cout << "������Ŀ��" << L.Songnum;
			cout << "\t����ģʽ��";
			switch (PlayMode) {
				case 1:cout << "˳�򲥷�"; break;
				case 2:cout << "�������"; break;
				case 3:cout << "�б�ѭ��"; break;
			}
			cout << endl << endl;

			if (!status) {//ststus=0
				cout << "\n\n\t��ǰ�޸�������";
			}
			else {
				switch (status) {
				case 0:
					cout << "ֹͣ";
					break;
				case 2:
					cout << "����";
					break;
				case 3:
					cout << "��ͣ";
				}
				cout << "���ţ�" << now + 1 << ". \"" << L.song[now].GetSongname() << "\"";
			//cout << "\tʱ����" << L.song[now].GetTime()<<endl<<endl;
			}

			Play_Hint();//�����ʾ
			char t;
		loop:
			cout << "->";
			cin >> t;
			switch (t) {
				case 'L'://��һ��
				case 'l':
					PlayLast();
					goto start;

				case 'N'://��һ��
				case 'n':
					PlayNext();
					goto start;

				case 'P'://��ͣ
				case	'p':
					Pause();
					goto start; 

				case 'S'://��ʼ/ֹͣ����
				case	's':
					if (status)//�ڲ���
						StopPlay();
					else
						StartPlay();
						goto start;

				case '1':
					if(status)//�ڲ���״̬
						background_playstatus = 1; //��������״̬��
					break;//����Mainmenu
				case '0':
					Sleep(500);
					Shutdown();
				default:
					goto loop;
			}
	}
	void StartPlay() {
		Play_file();	//(����)��ʼ����
		status = 2;			//�л�״̬��2 
	}
	void StopPlay() {
		if (status) //���ڲ���ʱ
			mciSendString("close MyPlayer", NULL, 0, 0);
		status = 0;
	}
	void Play_file() {
	loop:
		mciSendString("close MyPlayer", NULL, 0, 0);//�ر�ԭ����
		//��ȷ����ʱ����0����
		if (mciSendString(("open \"" + L.song[now].Getpath() +L.song[now].GetSongname()+"\"" + 
			" alias MyPlayer").c_str(), NULL, 0, 0)) {//�����ļ�

			cerr << L.song[now].GetSongname()<< "\n�򿪴���,����������һ��.";
			Sleep(1000);
			system("cls");
			PlayNext();
			goto loop;
		}
		mciSendString("play MyPlayer", NULL, 0, 0);//��ʼ����
	}
	void Pause() {
		switch (status) {
		case 2://����δ��ͣ
			mciSendString("pause MyPlayer", NULL, 0, 0);
			break;
		case 3://��������ͣ
			mciSendString("resume MyPlayer", NULL, 0, 0);
			break;
		}
		if(status)//���ڲ���״̬
			status = (status == 2 ? 3 : 2);
	}

	void PlayLast() {
		int his_n = now;//��¼��ǰ
		now =SelectLast();
		if (now != his_n)//˳�򲥷��ҵ�һ��
			status = 1;
		SaveConf();
	}
	void PlayNext() {
		//cout << "������һ��..." << endl;
		int his_n = now;//��¼��ǰ
		now = SelectNext();
		if(now!=his_n)//˳�򲥷������һ��
			status = 1;
		SaveConf();
	}
	int SelectLast() {
		switch (PlayMode) {
		case 1: return OrderByList(now, 'L');//˳�򲥷�
		case 2: return RandomMode(now);//�������
		case 3: return AllLoop(now, 'L');//�б�ѭ��
		}
		return 0;
	}
	int  SelectNext() {
		switch (PlayMode) {
		case 1: return OrderByList(now, 'N');//˳�򲥷�ģʽ
		case 2: return RandomMode(now);//�������ģʽ
		case 3: return AllLoop(now, 'N');//�б�ѭ��ģʽ
		}
		return 0;
	}

	int RandomMode(int now) {//�������
		srand(time(0));
		int n = (int)(rand() % L.Songnum);	//ȡ�����
		n = (rand() % L.Songnum);
		while (n == now)		//��ǰһ�������ͬ,����
			n = (rand() % L.Songnum);
		return n;

	}
	int AllLoop(int now, char mode) {//�б�ѭ��
		if (mode == 'N') {//��һ��
			if (now == L.Songnum - 1) return 0;//���һ��
			else return ++now;
		}
		else {//��һ��
			if (now == 0) return L.Songnum - 1;
			else return --now;
		}
	}
	int OrderByList(int now, char mode) {//˳�򲥷�
		if (mode == 'N') {
			if (now != L.Songnum - 1)//���һ��
				return ++now;
			else {
				cout << "---->�������һ��";
				Sleep(800);
				return L.Songnum - 1;
			}
		}
		else {
			if (now == 0) {
				cout << "---->���ǵ�һ��" << endl;
				Sleep(800);
				return 0;
			}
			else return --now;
		}
	}

	void Shutdown() {
		StopPlay();
		ExecCmd("cls");
		cout << "\n\n\n\n\t\t���ڹػ�.";
		Sleep(500); cout << ".";
		Sleep(500); cout << ".";
		Sleep(500); cout << ".";
		Sleep(500); 
		exit(0);
	}
};