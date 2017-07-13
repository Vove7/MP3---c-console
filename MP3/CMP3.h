#pragma once
#include"CPlayList.h"
#include"Interface.h"
#include<mmsystem.h>//声音头文件
#pragma comment (lib,"winmm.lib")//声音链接库
using namespace std;

class MP3 {
private:
	PlayList L;
	int now;//当前歌曲
	int PlayMode;//播放模式 (0、未开始)(1、开始播放) (2、正在播放) (3、播放暂停)
	int status;//播放状态
	int background_playstatus;//背景播放状态
	char color;//皮肤
public:
	MP3() {
		BootAnimation();
	}
	void BootAnimation() {//开机动画
		setlocale(0, "chs");
		cout << "\n\n\t\t开机ing.\n";
		for (int i = 0; i < 50; i++) {
			Sleep(20);
			cout << "-";
		}
		Sleep(100);
		system("cls");
	}
	void Launch() {
		LoadConf();//载入配置文件
		setlocale(0, "chs");
		cout << "\n\t\t载入歌曲列表...\n";
		status = 0;//播放状态 未开始
		background_playstatus = 0;
		L.ScanListFile();
		//进入主菜单
		while (1)
			MainMenu();
	}
	void LoadConf() {
		fstream conf("MP3配置.txt");
		if (!conf) {
			setlocale(0, "chs");
			cout << "\n\t未发现配置文件，使用初始化设置。\n";
			InitConf();//初始化
			return;
		}
		else {//读入
			conf >> now;		//上次播放记录
			conf >> PlayMode;   //读入播放模式
			conf >> color; // 皮肤
			char cmd[8] = "color  ";
			cmd[6] = color;
			ExecCmd(cmd);//换肤
			conf.close();
			setlocale(0, "chs");
			cout << "\t\t配置文件载入成功..\n";
		}
	}

	 void InitConf() { //创建初始配置
		 now = 0;
		 PlayMode = 1;
		 color = '7';
		 SaveConf();//保存默认参数
	}
	void MainMenu() {
		Main_Interface();//主界面
		int n;
	loop:
		cout << "->";
		cin >> n;
		switch (n) {
			case 0:  Shutdown();
			case 1: 
			if(L.Songnum){
				if (!status&&background_playstatus == 0)//进入播放界面若不在后台播放
					status = 1;//切换状态
				background_playstatus = 0;
				Play();//
			}
			else {
				system("cls");
				setlocale(0, "chs");
				cout << "\n\t当前播放列表无歌曲\n\n" << endl;
				system("pause");
			}
			break;
			case 2: 
				if (SelectSong()) {//选择歌曲返回true
					background_playstatus = 0;//进入播放
					status = 1;//开始
					SaveConf();
					Play();
				}
				//else 查看
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
				ShowAbout();//显示
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
				setlocale(0, "chs"); cout << "重新"; goto loop;
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
		cout << "\n\n-------已保存.";
		Sleep(400);
		cout << ".";
		Sleep(400);
		cout << ".";
		Sleep(400);
	}

	void SelectPlayMode() {
		SelectPlayMode_Interface();//界面
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
				setlocale(0, "chs"); cout << "重新"; goto loop;
		}
		SaveConf();
		setlocale(0, "chs");
		cout << "\n\n-------已保存.";
		Sleep(400);
		cout << ".";
		Sleep(400);
		cout << ".";
		Sleep(400);
	}
	void SaveConf() {
		fstream conf;
		conf.open("MP3配置.txt", ios::out);
		conf <<now<<" "<< PlayMode <<" "<< color;
		conf.close();
	}
	bool SelectSong() {
		L.DisplayList();//显示歌曲列表
		cout << "0.返回\n";
	loop:
		setlocale(0, "chs");
		cout << "选择->";
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
			cout << "\n\n\t播放列表为空,即将返回..";
			Sleep(1000);
			return;
		}
			if (status == 1 && !background_playstatus) {
				StartPlay();
			}
			if (now < 0 || now >= L.Songnum) {//意外/序号错误时
				status = 1;
				now = 0;//
				goto start;
			}

			setlocale(0, "chs");
			cout << "歌曲数目：" << L.Songnum;
			cout << "\t播放模式：";
			switch (PlayMode) {
				case 1:cout << "顺序播放"; break;
				case 2:cout << "随机播放"; break;
				case 3:cout << "列表循环"; break;
			}
			cout << endl << endl;

			if (!status) {//ststus=0
				cout << "\n\n\t当前无歌曲播放";
			}
			else {
				switch (status) {
				case 0:
					cout << "停止";
					break;
				case 2:
					cout << "正在";
					break;
				case 3:
					cout << "暂停";
				}
				cout << "播放：" << now + 1 << ". \"" << L.song[now].GetSongname() << "\"";
			//cout << "\t时长：" << L.song[now].GetTime()<<endl<<endl;
			}

			Play_Hint();//输出提示
			char t;
		loop:
			cout << "->";
			cin >> t;
			switch (t) {
				case 'L'://上一首
				case 'l':
					PlayLast();
					goto start;

				case 'N'://下一首
				case 'n':
					PlayNext();
					goto start;

				case 'P'://暂停
				case	'p':
					Pause();
					goto start; 

				case 'S'://开始/停止播放
				case	's':
					if (status)//在播放
						StopPlay();
					else
						StartPlay();
						goto start;

				case '1':
					if(status)//在播放状态
						background_playstatus = 1; //背景播放状态打开
					break;//返回Mainmenu
				case '0':
					Sleep(500);
					Shutdown();
				default:
					goto loop;
			}
	}
	void StartPlay() {
		Play_file();	//(重新)开始播放
		status = 2;			//切换状态到2 
	}
	void StopPlay() {
		if (status) //正在播放时
			mciSendString("close MyPlayer", NULL, 0, 0);
		status = 0;
	}
	void Play_file() {
	loop:
		mciSendString("close MyPlayer", NULL, 0, 0);//关闭原播放
		//正确播放时返回0↓↓
		if (mciSendString(("open \"" + L.song[now].Getpath() +L.song[now].GetSongname()+"\"" + 
			" alias MyPlayer").c_str(), NULL, 0, 0)) {//打开新文件

			cerr << L.song[now].GetSongname()<< "\n打开错误,即将播放下一首.";
			Sleep(1000);
			system("cls");
			PlayNext();
			goto loop;
		}
		mciSendString("play MyPlayer", NULL, 0, 0);//开始播放
	}
	void Pause() {
		switch (status) {
		case 2://播放未暂停
			mciSendString("pause MyPlayer", NULL, 0, 0);
			break;
		case 3://播放已暂停
			mciSendString("resume MyPlayer", NULL, 0, 0);
			break;
		}
		if(status)//处于播放状态
			status = (status == 2 ? 3 : 2);
	}

	void PlayLast() {
		int his_n = now;//记录当前
		now =SelectLast();
		if (now != his_n)//顺序播放且第一首
			status = 1;
		SaveConf();
	}
	void PlayNext() {
		//cout << "播放下一首..." << endl;
		int his_n = now;//记录当前
		now = SelectNext();
		if(now!=his_n)//顺序播放且最后一首
			status = 1;
		SaveConf();
	}
	int SelectLast() {
		switch (PlayMode) {
		case 1: return OrderByList(now, 'L');//顺序播放
		case 2: return RandomMode(now);//随机播放
		case 3: return AllLoop(now, 'L');//列表循环
		}
		return 0;
	}
	int  SelectNext() {
		switch (PlayMode) {
		case 1: return OrderByList(now, 'N');//顺序播放模式
		case 2: return RandomMode(now);//随机播放模式
		case 3: return AllLoop(now, 'N');//列表循环模式
		}
		return 0;
	}

	int RandomMode(int now) {//随机播放
		srand(time(0));
		int n = (int)(rand() % L.Songnum);	//取随机数
		n = (rand() % L.Songnum);
		while (n == now)		//与前一首序号相同,继续
			n = (rand() % L.Songnum);
		return n;

	}
	int AllLoop(int now, char mode) {//列表循环
		if (mode == 'N') {//下一曲
			if (now == L.Songnum - 1) return 0;//最后一曲
			else return ++now;
		}
		else {//上一曲
			if (now == 0) return L.Songnum - 1;
			else return --now;
		}
	}
	int OrderByList(int now, char mode) {//顺序播放
		if (mode == 'N') {
			if (now != L.Songnum - 1)//最后一曲
				return ++now;
			else {
				cout << "---->这是最后一首";
				Sleep(800);
				return L.Songnum - 1;
			}
		}
		else {
			if (now == 0) {
				cout << "---->这是第一首" << endl;
				Sleep(800);
				return 0;
			}
			else return --now;
		}
	}

	void Shutdown() {
		StopPlay();
		ExecCmd("cls");
		cout << "\n\n\n\n\t\t正在关机.";
		Sleep(500); cout << ".";
		Sleep(500); cout << ".";
		Sleep(500); cout << ".";
		Sleep(500); 
		exit(0);
	}
};