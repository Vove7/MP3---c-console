#pragma once
void Setting_Interface() {
	system("cls");
	cout << "1.ѡ�񲥷�ģʽ" << endl;
	cout << "2.�л�����Ƥ��" << endl;
	cout << "0.�������˵�" << endl;
}
void Main_Interface() {
	system("cls");
	cout << "\n\t\t1.���벥�Ž���\n" << endl;
	cout << "\t\t2.ѡ��/�鿴��������\n" << endl;
	cout << "\t\t3.ɨ������ļ�\n" << endl;
	cout << "\t\t4.����\n" << endl;
	cout << "\t\t5.����/����\n" << endl;
	cout << "\t\t0.�ػ�\n";
}
void Play_Hint() {

	cout << "\n\n\tL:��һ�� \tN:��һ��" << endl << endl;
	cout << "\tP:��ͣ/��������\tS:ֹͣ/��ʼ����\n\n";
	cout << "\t0:�ػ�\t\t1:���˵�\n\n";
}
void SelectPlayMode_Interface() {
	system("cls");
	cout << "1.˳�򲥷�" << endl;
	cout << "2.�������" << endl;
	cout << "3.�б�ѭ��" << endl;
	cout << "0.����" << endl;
}
void SetColor__Interface() {
	system("cls");
	cout << "e:" << "����ɫ" << endl;
	cout << "f:" << "����ɫ" << endl;
	cout << "b:" << "��ǳ��ɫ" << endl;
	cout << "c:" << "����ɫ" << endl;
	cout << "d:" << "����ɫ" << endl;
	cout << "4:" << "��ɫ" << endl;
	cout << "6:" << "����ɫ" << endl;

	cout << "0:" << "����" << endl;
}
void ExecCmd(const char *s) {
	system(s);
}
void ShowAbout() {
	system("cls");
	cout << "\n\n\t\t����\n\n";
	cout << "\tVer 1.2\t\t By Vove"<<endl;
	cout << "  \n\n\t�������ܣ�\n";
	cout << "\t1��ʵ��Mp3��������:���� ��ѡ�� �л�����"<<endl;
	cout << "\t2������ɨ�貥���б��ļ����� ɨ�����"<<endl;
	cout << "\t3�����ò���ģʽ��ѡ�����Ƥ��"<<endl;
	cout << "\t4��ʵ�����ò����洢";

	cout << "5�����Ž��������";
	cout << "\n\n\tL:��һ�� \tN:��һ��" << endl << endl;
	cout << "\tP:��ͣ����\tS:/��ʼֹͣ����\n\n";
	cout << "\t0:�ػ�\t\t1:���˵�\n\n";
	system("pause");
}