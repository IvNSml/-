#include<iostream>
#include <iomanip>
#include<clocale>
#include<windows.h>
#define SIZE 10

struct my_time
{
	int hours;
	int minutes;
};
struct train
{
	int number;
	char dest[SIZE];
	my_time time;
	train* next;
	train* prev;
};

using namespace std;
//������� ��� ����������� � ��������
train* create();//������� ������ �����
train* add(train* previous);//������� ������ ������������
train* get_info();//���� � ��������� �������, ��� �������� �������
int show(train* root, int number);// ��� ������ ���������� �� ������ ������
int show(train* root, char dest[]);// ��� ������ ���������� �� �������
int show_all(train* root);

train* get_info()
{
	train* current = new train;
	cout << "������� ����� ������: ";
	cin >> current->number;
	cout << "������� ����� ����������: ";
	cin >> current->dest;
	cout << "������� �����; ����: ";
	cin >> current->time.hours;
	cout << "������� �����; ������: ";
	cin >> current->time.minutes;
	return current;
}

train* create()
{
	train* first = new train;
	first = get_info();
	first->prev = NULL;
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
	current->prev = previous;//������� (�������->�����) �� ����������
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
	cout << "����� �����������: " << element->time.hours << ':' << element->time.minutes << endl;
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
			cout << "����� �����������: " << element->time.hours << ':' << element->time.minutes << endl;
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
	train* current = root;
	while(current)
	{
		cout << "����� ������: " << current->number << endl;
		cout << "�����������: " << current->dest << endl;
		cout << "����� �����������: " << current->time.hours << ':' << current->time.minutes << endl;
		current = current->next;
	}
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
	switch (command)
	{
	case 'a':
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
		if (!current ||!previous)
		{
			goto label;
		}
		break;
	case 'v':
		if (is_first) {
			cout << "�� ������ ������ �� ���������\n";
			break;
		}
		show_all(first);
		break;

	case 'i':
		cout << "����� ������: ";
		int number;
		cin >> number;
		show(first, number);
		break;

	case 's':
		cout << "�������� �������: ";
		char station[SIZE];
		cin >> station;
		show(first, station);
		break;
	
	case 'q':
	return 0;
	
	default:
		cout << "�������� ��������\n";
		break;
	}
	goto label;
}
