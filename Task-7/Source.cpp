#include <iostream>
#include <iomanip>
#include<math.h>
#include<ctime>
#include<cstring>
#include<fstream>

using namespace std;

//7.***Описать структуру Man(Фамилия, Имя, Возраст, Дата рождения).Создать массив, предусмотреть:
//1-Вывод информации с сортировкой по фамилии или имени;
//2-Вывод списка именинников месяца с указанием даты рождения.
//3-Изменение размеров массива при добавлении и удалении записей;
//4-Поиск по фамилии и имени;
//5-Редактирование записи.

int current_size = 0;
int buffer_size = 0;

struct Date {
	int day, month, year;
	void print() {
		cout << day << "/" << month << "/" << year << endl;
	}
};
struct Man {
	char name[30];
	char surname[30];
	int age;
	Date date_of_birth;

	void print() {
		cout << name << " " << surname << " " << age << " ";
		date_of_birth.print();
		cout << endl;
	}
};
//1-Вывод информации с сортировкой по фамилии или имени;
void sort(Man*&ms) {
	int choice;
	cout << "Enter 1 to sort by name" << endl;
	cout << "Enter 2 to sort by surname" << endl;
	cin >> choice;
	int k = 0;
	switch (choice)
	{
	case 1:
		for (int i = 0; i < current_size - 1; i++)
		{
			for (int j = 0; j < current_size - 1; j++)
			{
				if (strcmp(ms[j].name, ms[j + 1].name) == 1)
					swap(ms[j], ms[j + 1]);
				else if (strcmp(ms[j].name, ms[j + 1].name) == 0)
					if (strcmp(ms[j].surname, ms[j + 1].surname) == 1)
						swap(ms[j], ms[j + 1]);
			}
		}
		break;
	case 2:
		for (int i = 0; i < current_size - 1; i++)
		{
			for (int j = 0; j < current_size - 1; j++)
			{
				if (strcmp(ms[j].surname, ms[j + 1].surname) == 1)
					swap(ms[j], ms[j + 1]);
				else if (strcmp(ms[j].surname, ms[j + 1].surname) == 0)
					if (strcmp(ms[j].name, ms[j + 1].name) == 1)
						swap(ms[j], ms[j + 1]);
			}
		}
		break;
	}
}
//2-Вывод списка именинников месяца с указанием даты рождения.
void b_day(Man*ms) {
	cout << "Enter a month to check if there are b-day persons" << endl;
	int bm;
	cin >> bm;
	int k = 0;
	for (int i = 0; i < current_size; i++)
	{
		if (bm == ms[i].date_of_birth.month)
		{
			ms[i].print();
			k++;
		}
	}
	if (k == 0) cout << "No b-days this month" << endl;
}
//3-Изменение размеров массива при добавлении и удалении записей;
void add(Man*&ms, Man m) {
	if (buffer_size == 0)
	{
		buffer_size = 4;
		ms = new Man[buffer_size];
	}
	else
	{
		if (current_size == buffer_size)
		{
			buffer_size *= 2;
			Man*tmp = new Man[buffer_size];
			for (int i = 0; i < current_size; i++)
				tmp[i] = ms[i];
			delete[] ms;
			ms = tmp;
		}
	}
	ms[current_size++] = m;
}
void erase_last(Man*&ms) {
	current_size--;
	if (current_size == 0)
		delete[] ms;
}
void erase_by_name(Man*&ms, const char*name) {
	for (int i = 0; i < current_size; i++)
	{
		if (strcmp(ms[i].name, name) == 0)
		{
			for (int j = i; j < current_size; j++)
			{
				ms[j] = ms[j + 1];
				i--;
			}
			current_size--;
		}
	}
}
//4-Поиск по фамилии и имени;
void search(Man*ms) {
	int choice;
	cout << "Enter 1 to search by name" << endl;
	cout << "Enter 2 to search by surname" << endl;
	cout << "Enter 3 to search by full name" << endl;
	cin >> choice;
	int k = 0;
	char name[30];
	char surname[30];
	switch (choice)
	{
	case 1:
		cout << "Enter needed name" << endl;
		cin >> name;
		k = 0;
		for (int i = 0; i < current_size; i++)
		{
			if (strcmp(ms[i].name, name) == 0)
			{
				ms[i].print();
				k++;
			}
		}
		if (k == 0) cout << "No sought-for person in the database" << endl;
		break;
	case 2:
		cout << "Enter needed surname" << endl;
		cin >> surname;
		k = 0;
		for (int i = 0; i < current_size; i++)
		{
			if (strcmp(ms[i].surname, surname) == 0)
			{
				ms[i].print();
				k++;
			}
		}
		if (k == 0) cout << "No sought-for person in the database" << endl;
		break;
	case 3:
		cout << "Enter needed name and surname" << endl;
		cin >> name >> surname;
		k = 0;
		for (int i = 0; i < current_size; i++)
		{
			if (strcmp(ms[i].name, name) == 0 && strcmp(ms[i].surname, surname) == 0)
			{
				ms[i].print();
				k++;
			}
		}
		if (k == 0) cout << "No sought-for person in the database" << endl;
		break;
	}
}
//5-Редактирование записи.
void edit(Man*&ms) {
	for (int i = 0; i < current_size; i++)
	{
		cout << i + 1 << " - ";
		ms[i].print();
	}
	cout << "Enter index of the person to edit" << endl;
	int k;
	cin >> k;
	k = k - 1;

	char new_name[30];
	char new_surname[30];
	int new_age;
	Date new_date_of_birth;

	cout << "Enter new information" << endl;
	cout << "Enter a name: "; cin >> new_name;
	cout << "Enter a surname: "; cin >> new_surname;
	cout << "Enter an age: "; cin >> new_age;
	cout << "Enter date of birth: "; cin >> new_date_of_birth.day >> new_date_of_birth.month >> new_date_of_birth.year;

	strcpy_s(ms[k].name, new_name);
	strcpy_s(ms[k].surname, new_surname);
	ms[k].age = new_age;
	ms[k].date_of_birth.day = new_date_of_birth.day;
	ms[k].date_of_birth.month = new_date_of_birth.month;
	ms[k].date_of_birth.year = new_date_of_birth.year;
}

int main()
{
	srand(time(NULL));

	setlocale(LC_ALL, "Rus");

	//красиво зациклить задания - продолжить, выйти
	/*int cont=1;
	while(cont)
	{
	cout << "Enter 1 to continue" << endl << "Enter any other key to exit" << endl;
	cin >> cont;
	if (cont != 1) break;*/

	Man*ms = 0;
	Man tmp_man;
	char c;
	ifstream in_file("in.txt");
	if (!in_file)
	{
		cerr << "Enter open error" << endl;
	}
	else
	{
		while (!in_file.eof())
		{
			in_file >> tmp_man.name >> tmp_man.surname >> tmp_man.age >>
				tmp_man.date_of_birth.day >> c
				>> tmp_man.date_of_birth.month >> c
				>> tmp_man.date_of_birth.year;

			add(ms, tmp_man); //3
		}
	}

	sort(ms); //1
	for (int i = 0; i < current_size; i++)
		ms[i].print();

	b_day(ms); //2
	search(ms); //4
	edit(ms); //5
	for (int i = 0; i < current_size; i++)
		ms[i].print();


	cout << endl << endl;
	erase_by_name(ms, "Karina"); //3
	erase_by_name(ms, "Liza"); //3
	erase_last(ms); //3
	for (int i = 0; i < current_size; i++)
		ms[i].print();




	/*}*/

	system("pause");
	return 0;
}