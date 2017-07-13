#pragma once
void Setting_Interface() {
	system("cls");
	cout << "1.选择播放模式" << endl;
	cout << "2.切换界面皮肤" << endl;
	cout << "0.返回主菜单" << endl;
}
void Main_Interface() {
	system("cls");
	cout << "\n\t\t1.进入播放界面\n" << endl;
	cout << "\t\t2.选择/查看歌曲播放\n" << endl;
	cout << "\t\t3.扫描歌曲文件\n" << endl;
	cout << "\t\t4.设置\n" << endl;
	cout << "\t\t5.关于/帮助\n" << endl;
	cout << "\t\t0.关机\n";
}
void Play_Hint() {

	cout << "\n\n\tL:上一首 \tN:下一首" << endl << endl;
	cout << "\tP:暂停/继续播放\tS:停止/开始播放\n\n";
	cout << "\t0:关机\t\t1:主菜单\n\n";
}
void SelectPlayMode_Interface() {
	system("cls");
	cout << "1.顺序播放" << endl;
	cout << "2.随机播放" << endl;
	cout << "3.列表循环" << endl;
	cout << "0.返回" << endl;
}
void SetColor__Interface() {
	system("cls");
	cout << "e:" << "淡黄色" << endl;
	cout << "f:" << "亮白色" << endl;
	cout << "b:" << "淡浅绿色" << endl;
	cout << "c:" << "淡红色" << endl;
	cout << "d:" << "淡紫色" << endl;
	cout << "4:" << "红色" << endl;
	cout << "6:" << "暗黄色" << endl;

	cout << "0:" << "保存" << endl;
}
void ExecCmd(const char *s) {
	system(s);
}
void ShowAbout() {
	system("cls");
	cout << "\n\n\t\t关于\n\n";
	cout << "\tVer 1.2\t\t By Vove"<<endl;
	cout << "  \n\n\t基本功能：\n";
	cout << "\t1、实现Mp3基本功能:播放 、选择、 切换歌曲"<<endl;
	cout << "\t2、启动扫描播放列表文件，无 扫描磁盘"<<endl;
	cout << "\t3、设置播放模式，选择外观皮肤"<<endl;
	cout << "\t4、实现配置参数存储";

	cout << "5、播放界面操作：";
	cout << "\n\n\tL:上一首 \tN:下一首" << endl << endl;
	cout << "\tP:暂停播放\tS:/开始停止播放\n\n";
	cout << "\t0:关机\t\t1:主菜单\n\n";
	system("pause");
}