#include<iostream>
#include <windows.h>
#define SIZE 100
struct stack
{
	char symbol;
	stack* next;
};
void push(stack** top,char symbol, bool* first)// ������� ���������, ����� �������� ��������� 
{
	stack* current = new stack;
	current->symbol = symbol;
	if(*first)
	{
		current->next = NULL;//��� �����
		*top = current;
		*first = false;
	}
	else {
		current->next = *top;
		*top = current;
	}
}
void pop(stack** top)
{
	std::cout << (*top)->symbol;
	*top = (*top)->next;
}
using namespace std;
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool first = true;
	stack* example = NULL;
	stack** top = &example;//������� ������� ��������� �� NULL: ������ ��������� ���
	setlocale(LC_ALL, "Russian");
	char sentance[SIZE];
	cout << "������� �����������: ";
	cin.getline(sentance,SIZE);
	const char* psent = sentance;
	while(*(psent-1))//��-�� ����������, ��������� ����� �� ��������� �� '\0' ��������
	{	
		while (*psent != ' '&&  *psent)
		{
			push(top, *psent, &first);
			psent++;
		}
		while(*top)
		{
			pop(top);
		}
		first = true;
		psent++;//���������, ����� ������� �� ����� ������ ����� ' '
		cout << ' ';
	}
	cout << endl;
	system("pause");
	return 0;	
}