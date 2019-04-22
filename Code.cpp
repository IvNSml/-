#include<iostream>
#include <iomanip>
#include<clocale>
#include<windows.h>
#include<fstream>
#include <string>
#define SIZE 30


struct my_time
{
	int hours;
	int minutes;
};
struct train
{
	int number;
	char dest[SIZE];
	my_time* time;
	train* next;
};

using namespace std;
//������� ��� ����������� � ��������
train* create();//������� ������ �����
train* add(train* previous);//������� ������ ������������
train* get_info();//���� � ��������� �������, ��� �������� �������
my_time* time();//���� ������� � ���������
int show(train* root, int number);// ��� ������ ���������� �� ������ ������
int show(train* root, char dest[]);// ��� ������ ���������� �� �������
int show_all(train* root);// ���������� ������ �� ����� ��� ������� ������ ������ ������
int write_file(train* record);

train* get_info()
{
ErrorLabel:
	train* current = new train;
	try {
		cout << "������� ����� ������: ";
		cin >> current->number;
		cin.ignore(1000,'\n');
		cout << "������� ����� ����������: ";
		cin >> current->dest;
		if (!cin || current->dest == '\0')
		{
			throw "������ ���� ������!\n";
		}
		cin.ignore(1000, '\n');
		current->time = time();
	}
	catch(const char* TypeError)
	{
		system("cls");
		cin.clear();
		cin.ignore(1000, '\n');
		cout << TypeError << endl;
		delete current;
		goto ErrorLabel;
	}
	return current;
}
my_time* time() {
	my_time* now = new my_time;
		while (true) {
			cout << "������� �����: ����: ";
			cin >> now->hours;
			if (now->hours >= 24 || now->hours < 0 || now->hours == '\0')
			{
				cout << "������! ������� ������ �����!\n";
				system("pause");
				system("cls");
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}
			cout << "������� �����: ������: ";
			cin >> now->minutes;
			if (now->minutes > 59 || now->minutes < 0 || now->minutes == '\0')
			{
				cout << "������! ������� ������ �����!\n";
				system("pause");
				system("cls");
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}
			break;
		}
		return now;
}
	

train* create()
{
	train* first = new train;
	first = get_info();
	first->next = NULL;
	return first;
}
train* add(train* previous)
{
	train* current = new train;
	current = get_info();
	train* to_next = previous->next;// ��������� ��������� �������
	previous->next = current;//������� (����������->������) �� �������
	current->next = to_next;//������� (�������->������) �� ��������� (����� ����)
	return current;
}

int show(train* root, int number)
{
	train* element = root;
	while (element->number != number)//���� �� ������
	{
		element = element->next;
		if (element==NULL)
		{
			cout << "��� ������ ������!\n" << endl;
			return 0;
		}
	}
	cout << "����� ������: " << element->number << endl;
	cout << "�����������: " << element->dest << endl;
	cout << "����� �����������: " << element->time->hours << ':' << element->time->minutes << endl;
	return 0;
}

int show(train* root, char dest[])
{
	setlocale(LC_ALL, "Russian");
	train* element = root;
	bool free = true;
	while (element)//���� �� NULL
	{
		if (strcmp(dest,element->dest)==0)
		{
			free = false;
			cout << "����� ������: " << element->number << endl;
			cout << "�����������: " << element->dest << endl;
			cout << "����� �����������: " << element->time->hours << ':' << element->time->minutes << endl;
		}
		element = element->next;	
	}	
	if (free)
	{
		cout << "��� ������� �� ������� �����������\n";
	}
	return 0;
}
int show_all(train* root)
{
	train* current = new train;
	ifstream file;
	string buff;
	file.open("file.bin", ios::binary);
	if (!file.is_open())
	{
		cout << "���������� ������� ����!" << endl;
		return -1;
	}
	getline(file, buff);
	while(!file.eof())
	{
		getline(file,buff);
		cout << "����� ������: " << buff << endl;
		getline(file, buff);
		cout << "�����������: " << buff << endl;
		getline(file, buff);
		cout << "����� �����������: " << buff;
		getline(file, buff);
		cout << ':' << buff <<endl;
	}
	file.close();
	return 0;
}

int write_file(train* currrent)
{
	ofstream file;
	file.open("file.bin", ios::binary | ios::app);
	if(!file.is_open())
	{
		cout << "���������� ������� ����!" << endl;
		return -1;
	}
	file << endl;
	file << currrent->number<<endl;
	file << currrent->dest << endl;
	file << currrent->time->hours<<endl;
	file << currrent->time->minutes;
	file.close();
	return 0;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	train* previous = NULL;//��� � add(), ��������� �� ���������� ������� ������
	train* first = NULL;
	train* current = NULL; // ��� � add(),���������� �� ���� �� �������� � switch-case, ������ ��� �����
	bool is_first = true;//�������� �� ������ ���������
label://����� �������� � ����
	cout << "--------------------------------------------------------------------------------" << setw(45);
	cout << "���� ���������" << endl;
	cout << "--------------------------------------------------------------------------------";
	cout << "�������� ������ ��������:" << endl;
	cout << "�������� ����� (a)" << endl << "������� ������ ������� (v)" << endl <<
		"������� ���������� � ������ (i)" << endl << "������� ���������� � ������� �� ������� (s)" << endl << "����� �� ��������� (q)" << endl <<
		"�����: ";
	char command;
	cin >> command;
	cin.ignore(1000, '\n');
	system("cls");
	switch (command)
	{
	case 'a':
		system("cls");
		if (is_first) {
			first = create();
			previous = first;
			is_first = false;
		}
		else
		{
			current = add(previous);
			previous = current;
		}
		write_file(previous);
		system("cls");
		cout<<"����� ������!\n";
		break;
	case 'v':
		if (is_first) {
			cout << "�� ������ ������ �� ���������\n";
			break;
		}
		show_all(first);
		break;

	case 'i':
		if (is_first) {
			cout << "�� ������ ������ �� ���������\n";
			break;
		}
		int number;
		cout << "����� ������: ";
		cin >> number;
		if (cin.fail()) {
			cout << "�������� ��� ������!\n";
			cin.clear();
			cin.ignore(1000, '\n');
			break;
		}
		system("cls");
		show(first, number);
		break;

	case 's':
		if (is_first) {
			cout << "�� ������ ������ �� ���������\n";
			break;
		}
		cout << "�������� �������: ";
		char station[SIZE];
		cin >> station;
		system("cls");
		show(first, station);
		break;
	
	case 'q':
		if (remove("file.bin") != 0)
			std::cout << "������ �������� �����\n";
		return 0;
	
	default:
		cout << "�������� ��������\n";
		break;
	}
	cout << endl;
	system("pause");
	system("cls");
	goto label;
}
