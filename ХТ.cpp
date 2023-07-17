
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<tuple>
//Струкутура входных данных
struct fullname
{
	//std::string lastname;
	std::string firstname;
	//std::string secondname;
};
struct tituls 
{
	std::string fitst_title;
	//std::string second_title;
};
struct certificate
{
	int number;
};
struct adress {
	//std::string city;
	std::string build;//street
	//int build;
};
struct list
{
	fullname name;
	tituls title;
	certificate num;
	adress traffic_police;
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
    int FirstHF(int key)
	{
		key = key % size1;
		return key;
	}
	// Вторичная ХФ
	int SecondHF(int key, int step)//попытка ввод к с клавиатур
	{
		key = (key + step) % size1;
		return key;
	}

	void Add_I(list record)
	{

		int key1 = FirstHF(record.num.number);
		int key2;
		record.hash = key1;
		if (status[key1] == 0)
		{
			status[key1] = 1;
			items[key1] = record;
			//count++;
		}
		else
		{
			if ((status[key1] == 2) || ((status[key1] == 1) && (record.num.number != items[key1].num.number)))
			{

				key2 = AddColl(key1, status, record);
				if (key2 != -1)
				{
					status[key2] = 1;
					items[key2] = record;
					//count++;
				}
			}
		}
		//}
		//else std::cout << "Нет места вставки" << std::endl;
	}
	int AddColl(int key, std::vector<int>status, list record)
	{
		bool del = false, same = false;
		int num = 1, st = key,st1= -2;
		int step = 1;
		while ((status[st] != 0) && (num < size1))
		{

			st = SecondHF(key, step);
			if ((status[st] == 1) && (record.num.number == items[st].num.number))
			{
				same = true;
			}
			if ((status[st] == 2) && del ==false)
			{
				st1 = st;
				del = true;
			}
			st = SecondHF(key, step);
			num++;
			step++;
		}

		if (!same)
		{
			if (((status[st] == 0) || (status[st] == 0)) && (del == false))
			{
				key = st;
			}
			else if (((status[st] == 2) && (del == true)) || ((status[st] == 1) && (del == true)) || ((status[st] == 0) && (del == true)))
			{
				key = st1;
			}
			else if ((status[st] == 1) && (del == false))
			{
				std::cout << "Нет места" << std::endl;
				key = -1;
			}
			return	key;
		}
		else return key = -1;	
	}
	int Collision(int key, std::vector<int>status, list record,int& step)
	{
		int num = 1;
		int st = key;
		int _key = key;
		while (num < size1)
		{
			st = SecondHF(_key, step);
			num++;
			step++;
			if ((status[st] == 0) || (status[st] == 2))
			{
				st = -1;
				break;
			}
			else if ((status[st] == 1) && (record.num.number == items[st].num.number))
			{
				break;
			}
		}
		return st;
	}

	void Search_I(list record)
	{
		int search_s;
		 int step = 0;
		int key1 = FirstHF(record.num.number);
			if (status[key1] == 1 && (record.num.number == items[key1].num.number))
			{
				std::cout << "Найден:" << items[key1].hash << " " << items[key1].name.firstname << " " << items[key1].title.fitst_title << " " << items[key1].num.number << " " << items[key1].traffic_police.build<< std::endl;
					search_s = 1;
			}
			else
			{
				int key2 = Collision(key1, status, record,step);
					if ((key2 != -1) && (record.num.number == items[key1].num.number))
					{
						std::cout << "Найден:" << items[key2].hash << " " << items[key2].name.firstname << " " << items[key2].title.fitst_title << " " << items[key2].num.number << " " << items[key2].traffic_police.build << std::endl;
						search_s = 1;
					}
					else
					{
						search_s = 0;
							std::cout << "Не найден" << std::endl;
					}


			}
						//std::cout << "Поиск в nустой таблице" << std::endl;
		//search_s = 0;
	}

	

	bool Delete(list record)
	{

		int num = 1;
		int step = 1;
		int key1 = FirstHF(record.num.number);
		if (status[key1] == 1 && (record.num.number == items[key1].num.number))
		{
			status[key1] = 2;
			return true;
		}
		else
		{
			int key2 = Collision(key1, status, record,step);
			if ((key2 != -1) && (record.num.number == items[key2].num.number))
			{
				status[key2] = 2;
				return true;
			}
			else if (key2 == -1) 
			{
				int key3 = Collision(key1, status, record, step);
				while ((key3 == -1) && (num < size1))
				{
					key3 = Collision(key1, status, record, step);
					num++;
				}
				if (record.num.number == items[key3].num.number) 
				{
					status[key3] = 2;
					return true;
				}
				else return false;

			}
				 else return false;
		}

	}
	
	void Print()
	{
		for (int i = 0; i < size1; i++)
		{
			std::cout << i << "-" << " ";
			if (status[i] == 1)
				std::cout << items[i].hash << " " << items[i].name.firstname << " " << items[i].title.fitst_title << " " << items[i].num.number << " " << items[i].traffic_police.build<< std::endl;
			else
				std::cout << "-" << std::endl;
		}
		std::cout << '\n';
	}
	/*void GetArray(list*& record, int size1, std::string filename)
	{
		std::ifstream(file);
		file.open(filename);
		std::string line;
		int i = 0;
		while (i != size1)
		{
			getline(file, line, ' ');
			std::string lastname = line;
			getline(file, line, ' ');
			std::string name = line;
			getline(file, line, ' ');
			std::string secondname = line;
			record[i].name.firstname = lastname + " " + name + " " + secondname;


			getline(file, line, ' ');
			std::string title = line;
			getline(file, line, ' ');
			std::string second_title = line;
			record[i].title.fitst_title = title + " " + second_title;
		
			/*getline(file, line, ' ');
			record[i].title.fitst_title = line;
			getline(file, line, ' ');
			record[i].title.second_title = line;
			

			getline(file, line, ' ');
			record[i].num.number = stoi(line);
			getline(file, line, ' ');
			std::string city = line;
			getline(file, line, ' ');
			std::string street = line;
			getline(file, line, ' ');
			std::string build = line;
			record[i].traffic_police.build = city + " " + street + " " + build;


			//record[i].str = i;
			i++;
		}
		file.close();
	}

	~HTable() = default;
	*/
private:
	list* items;
	std::vector<int>status;
	int size1;
	int count = 0;
};

int main()
{
	setlocale(LC_ALL, "Russian");
	int size1;
	std:: cin >> size1;
	HTable Table(size1);

	bool search = 0;
	list record;
	//Table.GetArray(record, size1, "Inspectors.txt");
	/*for (int i = 0; i < size1; i++) {
		std::cout << record[i].name.firstname<<" " << record[i].title.fitst_title
			<< " "<< record[i].num.number << " "<< record[i].traffic_police.city
			<< " "<< record[i].traffic_police.street << " "<< record[i].traffic_police.build
			<< " "<< std::endl;
	}*/
    record.name.firstname = "Федотов Владимир Олегович";
	record.title.fitst_title = "Старший инспектор";
	record.num.number = 123456000;
	record.traffic_police.build = "Москва Семеновская 9";

	Table.Add_I(record);
	Table.Print();

	record.name.firstname = "Нарышкин Святополк Геннадьевич";
	record.title.fitst_title = "Старший инспектор";
	record.num.number = 234567800;
	record.traffic_police.build = "Владивосток Постышева 26";
	Table.Add_I(record);
	Table.Print();

	record.name.firstname = "Суслеганова Ангелина Сергеевна";
	record.title.fitst_title = "Государственный инспектор ";
	record.num.number = 345678900;
	record.traffic_police.build = "Екатеринбург Державина 21";
	Table.Add_I(record);
	Table.Print();

	record.name.firstname = "Суслеганова Ангелина Сергеевна";
	record.title.fitst_title = "Государственный инспектор ";
	record.num.number = 345678900;
	record.traffic_police.build = "Екатеринбург Державина 21";
	Table.Delete(record);
	Table.Print();

	record.name.firstname = "Нарышкин Святополк Геннадьевич";
	record.title.fitst_title = "Старший инспектор";
	record.num.number = 234567800;
	record.traffic_police.build = "Владивосток Постышева 26";
	Table.Delete(record);
	Table.Print();

	record.name.firstname = "Федотов Владимир Олегович";
	record.title.fitst_title = "Старший инспектор";
	record.num.number = 123456000;
	record.traffic_police.build = "Москва Семеновская 9";

	Table.Delete(record);
	Table.Print();

	record.name.firstname = "Федотов Владимир Олегович";
	record.title.fitst_title = "Старший инспектор";
	record.num.number = 123456000;
	record.traffic_police.build = "Москва Семеновская 9";

	Table.Add_I(record);
	Table.Print();

	record.name.firstname = "Нарышкин Святополк Геннадьевич";
	record.title.fitst_title = "Старший инспектор";
	record.num.number = 234567800;
	record.traffic_police.build = "Владивосток Постышева 26";
	Table.Add_I(record);
	Table.Print();

	record.name.firstname = "Суслеганова Ангелина Сергеевна";
	record.title.fitst_title = "Государственный инспектор ";
	record.num.number = 345678900;
	record.traffic_police.build = "Екатеринбург Державина 21";
	Table.Add_I(record);
	Table.Print();

	record.name.firstname = "Нарышкин Святополк Геннадьевич";
	record.title.fitst_title = "Старший инспектор";
	record.num.number = 234567800;
	record.traffic_police.build = "Владивосток Постышева 26";
	Table.Delete(record);
	Table.Print();

	record.name.firstname = "Федотов Владимир Олегович";
	record.title.fitst_title = "Старший инспектор";
	record.num.number = 123456000;
	record.traffic_police.build = "Москва Семеновская 9";

	Table.Delete(record);
	Table.Print();

	record.name.firstname = "Суслеганова Ангелина Сергеевна";
	record.title.fitst_title = "Государственный инспектор ";
	record.num.number = 345678900;
	record.traffic_police.build = "Екатеринбург Державина 21";
	Table.Delete(record);
	Table.Print();
	return 0;

}