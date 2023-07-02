
/*Реализовать на языке C++ класс для работы с хеш - таблицей
(Входные данные : текстовый файл, в первой строке – целое число 
n - количество строк файла(10 ≤ n ≤ 1000000).Каждая из последующих 
строк содержит данные студента, разделенные 1 пробелом.Все данные во'
входном файле корректные(проверять на корректность не нужно);
ключ - составной n, вид хеш - таблицы - статическая(Статус 0 / 1 / 2),
метод разрешения коллизий - открытая адресация(линейный k > 1), 
хеш - функция - модульная
    Методы :
1. Конструктор
2. Первичная хеш - функция
3. Вторичная хеш - функция
4. Добавление
5. Удаление
6. Поиск
7. Печать
8. Деструктор

5. Тесты (добавление: проверка уникальности ключа, добавление при коллизии; поиск: ключ не существует, ключ существует,
поиск при коллизии; удаление: ключ существует, ключ не существует, удаление при коллизии; 
проверка не только ключа, но и значения, ассоциированного
 с ключом)

*/
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<tuple>
//Струкутура входных данных
struct auditorium
{
	char litera;
	int num;
};
struct fullname
{
	std::string lastname;
	std::string firstname;
	std::string secondname;
};
struct times
{
	int hour;
	int minutes;
};
struct object {
	std::string predmet;
};
struct list
{
	auditorium room;
	fullname name;
	times time;
	object subject;
	int hash;
};
 //Хеш - таблица
class HTable
{
public:

	HTable(int size)
	{
		size1 = size;
		items = new list[size];
		status.resize(size);
	};
	// Первая хеш функция
	void FirstHF( int& key)
	{
		key = key % size1;
	}
	// Вторичная ХФ
	void SecondHF(int& key, int num)//попытка ввод к с клавиатуры

	{
		int k = 2;
		key = (key + num* k) % size1;
	}
	void Int_key(list record, unsigned long i_key) {
		std::string str;
		str = record.name.lastname + record.name.firstname + record.name.secondname;
		int size = str.length();
		char chars;
		for (int i = 0; i < size; i++) {
			//chars = str[i];
			i_key += str[i];//str[i]
		}
	}

	void Add(list record)
	{
		if (count < size1)
		{

			int INT_key =0;
			Int_key(record, INT_key);
			INT_key = INT_key + record.time.hour + record.time.minutes;
			int key1 = INT_key, key2 = 0;
			FirstHF(key1);
			record.hash = key1;
			if (status[key1] == 0)
			{
				/*if (std::tie(record.name.lastname, record.name.firstname, record.name.secondname, record.room.litera, record.room.num,
					record.subject.predmet, record.time.hour, record.time.minutes)
					!= std::tie(items[key1].name.lastname, items[key1].name.firstname, items[key1].name.secondname, items[key1].room.litera,
						items[key1].room.num,items[key1].subject.predmet, items[key1].time.hour, items[key1].time.minutes))*/
				//{
				status[key1] = 1;
				items[key1] = record;
				//}
				count++;
			}
			else 
			{
				if ((status[key1] == 2) or ((status[key1] == 1) and std::tie(record.name.lastname, record.name.firstname, record.name.secondname, record.room.litera, record.room.num, record.subject.predmet,
					record.time.hour, record.time.minutes)
					!= std::tie(items[key1].name.lastname, items[key1].name.firstname, items[key1].name.secondname, items[key1].room.litera,
						items[key1].room.num, items[key1].subject.predmet, items[key1].time.hour, items[key1].time.minutes)))
				{
					//key2 = key1
					bool zero = false, same = false;
					int num = 1;
					while ((status[key1] != 0) && (num < size1))
					{
						
						SecondHF(key1,num);
						if ((status[key1] == 1) && std::tie(record.name.lastname, record.name.firstname, record.name.secondname, record.room.litera, record.room.num, record.subject.predmet,
							record.time.hour, record.time.minutes)
							== std::tie(items[key1].name.lastname, items[key1].name.firstname, items[key1].name.secondname, items[key1].room.litera,
								items[key1].room.num, items[key1].subject.predmet, items[key1].time.hour, items[key1].time.minutes))
						{
							same = true;
						}
						num++;
					}
					if (same == false)
					{
						if (status[key1] == 0)
						{
							zero = true;
						}
						if (!zero)
						{
						
							while ((status[key1] != 2) && (num < size1))
							{
								SecondHF(key1,num);
								num++;
							}
						}
						
						key2 = key1;
					}
					else
						 key2 = -1;

					if (key2 != -1)
					{
						status[key2] = 1;
						items[key2] = record;
						count++;//?
					}
				}
			}
		
		}
		else
			std::cout << "Таблица заполнена!\n" << std::endl;
	}

	void Collision(int& key, std::vector<int>status,list record)
	{
		int num = 1;

		while (num < size1)
		{
			SecondHF(key, num);
			num++;
			if ((status[key] == 0) || (status[key] == 2))
			{
				key = -1;
				break;
			}
			else if ((status[key] == 1) && std::tie(record.name.lastname, record.name.firstname, record.name.secondname, record.room.litera, record.room.num, record.subject.predmet,
				record.time.hour, record.time.minutes)
				== std::tie(items[key].name.lastname, items[key].name.firstname, items[key].name.secondname, items[key].room.litera,
					items[key].room.num, items[key].subject.predmet, items[key].time.hour, items[key].time.minutes))
				break;
			}
		}
	
	void Search(list record)
	{

		int INT_key = 0;
		Int_key(record, INT_key);
		INT_key = INT_key + record.time.hour + record.time.minutes;
		int key1 = INT_key, key2 = 0;
		//FirstHF(key1);
		//bool empt = true;
		int search_s = 1;
		if (count != 0)
		{
			FirstHF(key1);

			if (status[key1] == 1 && (std::tie(record.name.lastname, record.name.firstname, record.name.secondname, record.room.litera, record.room.num, record.subject.predmet,
				record.time.hour, record.time.minutes)
				== std::tie(items[key1].name.lastname, items[key1].name.firstname, items[key1].name.secondname, items[key1].room.litera,
					items[key1].room.num, items[key1].subject.predmet, items[key1].time.hour, items[key1].time.minutes)))
			{
				std::cout<< "Найден:" << items[key1].hash << " " << items[key1].name.lastname << items[key1].name.firstname << items[key1].name.secondname << " " << items[key1].time.hour << ":" << items[key1].time.minutes << std::endl << std::endl; //найдена
				search_s = 1;
			}
			else
			{
				Collision(key1, status, record);
				key2 = key1;
				if ((key2 != -1) && (std::tie(record.name.lastname, record.name.firstname, record.name.secondname, record.room.litera, record.room.num, record.subject.predmet,
					record.time.hour, record.time.minutes)
					== std::tie(items[key1].name.lastname, items[key1].name.firstname, items[key1].name.secondname, items[key1].room.litera,
						items[key1].room.num, items[key1].subject.predmet, items[key1].time.hour, items[key1].time.minutes)))
				{
					std::cout<< "Найден:" << items[key1].hash << " " << items[key1].name.lastname << items[key1].name.firstname << items[key1].name.secondname << " " << items[key1].time.hour << " : " << items[key1].time.minutes << std::endl << std::endl; //найдена
					search_s = 1;
				}
				else
				{
					search_s = 0;
					std::cout << "Не найден" << std::endl;
				}
			}

		}
		else
		{
			std::cout << "Поиск в nустой таблице" << std::endl;
			search_s = 0;
		}

	}
	//дописать
	/*void Delete(list record)
	{
		int del =1;
		for (int i : status) {
			if (i == 1) {
				del = 1;
			}
		}
		if (del == 0)
		{
			int INT_key = 0;
			Int_key(record, INT_key);
			INT_key = INT_key + record.time.hour + record.time.minutes;
			int key1 = INT_key, key2 = 0;
			FirstHF(key1);
			if (status[key1] == 0 || (std::tie(record.name.lastname, record.name.firstname, record.name.secondname, record.room.litera, record.room.num, record.subject.predmet, record.time.hour, record.time.minutes)!=
				std::tie(items[key1].name.lastname, items[key1].name.firstname, items[key1].name.secondname, items[key1].room.litera, items[key1].room.num, items[key1].subject.predmet, items[key1].time.hour, items[key1].time.minutes))){
				 del = 0;
			}
			else if (status[key1] == 1 && (std::tie(record.name.lastname, record.name.firstname, record.name.secondname, record.room.litera, record.room.num, record.subject.predmet, record.time.hour, record.time.minutes) ==
				std::tie(items[key1].name.lastname, items[key1].name.firstname, items[key1].name.secondname, items[key1].room.litera, items[key1].room.num, items[key1].subject.predmet, items[key1].time.hour, items[key1].time.minutes)))
			{
				status[key1] = 2;
				del = 1;
			}
			else
			{
				while (del == 1)
				{
					key2 = key1;
					Collision(key2, status,record);
					key1 = key2;
					if (status[key1] == 0)
						  del = 0;
					else if (status[key1] == 1 && (std::tie(record.name.firstname, record.room.litera, record.room.num, record.subject.predmet, record.time.hour, record.time.minutes)
						== std::tie(items[key1].name.firstname, items[key1].room.litera, items[key1].room.num, items[key1].subject.predmet, items[key1].time.hour, items[key1].time.minutes)))
					{
						status[key1] = 2;
						del = 1;
					}
				}
			}
		}
		else
		{
		
			del = 0;
		}
	}*/
	bool Delete(list record)
	{
		int del = 1;
		if (count != 0)
		{
			int INT_key = 0;
			Int_key(record, INT_key);
			INT_key = INT_key + record.time.hour + record.time.minutes;
			int key1 = INT_key, key2 = 0;
			FirstHF(key1);
			if (status[key1] == 1 && (std::tie(record.name.lastname, record.name.firstname, record.name.secondname, record.room.litera, record.room.num, record.subject.predmet, record.time.hour, record.time.minutes)
				==
				std::tie(items[key1].name.lastname, items[key1].name.firstname, items[key1].name.secondname, items[key1].room.litera, items[key1].room.num, items[key1].subject.predmet, items[key1].time.hour, items[key1].time.minutes)))
			{
				status[key1] = 2;
				count--;
				int del = 1;
				return true;
			}
			else
			{
				Collision(key1, status, record);
				key2 = key1;
				if ((key2 != -1) && (std::tie(record.name.lastname, record.name.firstname, record.name.secondname, record.room.litera, record.room.num, record.subject.predmet, record.time.hour, record.time.minutes)
					==
					std::tie(items[key1].name.lastname, items[key1].name.firstname, items[key1].name.secondname, items[key1].room.litera, items[key1].room.num, items[key1].subject.predmet, items[key1].time.hour, items[key1].time.minutes)))
				{
					status[key2] = 2;
					count--;
					return true;
				}
				else {
					int del = 0;
					return false;
				}
			}
		}
		else
		{
			std::cout << "Таблица пуста!\n" << std::endl;//можно уьрать 
			int del = 0;
			return false;
		}
	}
	void Print()
	{
		for (int i = 0; i < size1; i++)
		{
			std::cout  << i << "-" << " ";
			if (status[i] == 1)
				std::cout << items[i].hash << " " << items[i].name.lastname << " " << items[i].name.firstname << " " << items[i].name.secondname << " " << items[i].time.hour << ":" << items[i].time.minutes << std::endl;
			else
				std::cout << "-" << std::endl;
		}
		std::cout << '\n';
	}
	
	~HTable() = default;

private:
	list* items;
	std::vector<int>status;
	int size1;
	int count = 0;
};

int main()
{
	setlocale(LC_ALL, "rus");
	HTable Table(5);
	list record;
	int search;
	search = 0;
//	Table.Search(record);
	//Table.Delete(record);
	//Table.Print();
	record.name.lastname = "Ва";
	record.name.firstname = "Миил";
	record.name.secondname = "Сервич";
	record.time.hour = 8;
	record.time.minutes = 30;
	Table.Add(record); 
	Table.Print();

	record.name.lastname = "Ва";
	record.name.firstname = "Миил";
	record.name.secondname = "Сервич";
	record.time.hour = 8;
	record.time.minutes = 30;
	Table.Add(record);
	Table.Print();

	record.name.lastname = "Ваяй";
	record.name.firstname = "Михаил";
	record.name.secondname = "Сергеевич";
	record.time.hour = 5;
	record.time.minutes = 30;
	Table.Add(record);	
	Table.Print();

	record.name.lastname = "Иванов";
	record.name.firstname = "Иван";
	record.name.secondname = "Иванович";
	record.time.hour = 6;
	record.time.minutes = 30;
	Table.Add(record);	
	Table.Print();

	record.name.lastname = "Петров";
	record.name.firstname = "Петр";
	record.name.secondname = "Петрович";
	record.time.hour = 18;
	record.time.minutes = 20;
	Table.Add(record);
	Table.Print();

	record.name.lastname = "Петька";
	record.name.firstname = "Петр";
	record.name.secondname = "Петрович";
	record.time.hour = 10;
	record.time.minutes = 30;
	Table.Add(record);
	Table.Print();
	//____________________________

	record.name.lastname = "Петька";
	record.name.firstname = "Петр";
	record.name.secondname = "Пет";
	record.time.hour = 10;
	record.time.minutes = 30;
	Table.Search(record);
	Table.Print();

	record.name.lastname = "Иванов";
	record.name.firstname = "Иван";
	record.name.secondname = "Иванович";
	record.time.hour = 6;
	record.time.minutes = 30;
	Table.Search(record);
	Table.Print();

	record.name.lastname = "Ва";
	record.name.firstname = "Миил";
	record.name.secondname = "Сервич";
	record.time.hour = 8;
	record.time.minutes = 30;
	Table.Delete(record);
	Table.Print();

	record.name.lastname = "Ллаала";
	record.name.firstname = "лалалалала";
	record.name.secondname = "адададада";
	record.time.hour = 18;
	record.time.minutes = 20;
	Table.Search(record);
	Table.Delete(record);

	record.name.lastname = "Ваяй";
	record.name.firstname = "Михаил";
	record.name.secondname = "Сергеевич";
	record.time.hour = 5;
	record.time.minutes = 30;
	Table.Delete(record);
	Table.Print();

	return 0;
}