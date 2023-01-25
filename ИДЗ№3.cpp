#include <iostream>
#include <fstream>
#include<string>
#include<tuple>
#include<chrono>


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
struct list
{
	auditorium room;
	fullname name;
	times time;
};

//получение количества строк из файла
void GetSize(int& size, std::string filename)
{
	std::ifstream(file);
	file.open(filename);
	std::string line;
	std::getline(file, line);
	size = std::stoi(line);
	file.close();
}
//считывание массива
void GetArray(list*& record, int size, std::string filename)
{
	std::ifstream(file);
	file.open(filename);
	std::string line;
	getline(file, line);
	int i = 0;
	while (i != size)
	{
		getline(file, line, ' ');
		record[i].room.litera = line[0];
		std::string number = line.erase(0, 1);
		record[i].room.num = stoi(number);
		getline(file, line, ' ');
		record[i].name.lastname = line;
		getline(file, line, ' ');
		record[i].name.firstname = line;
		getline(file, line, ' ');
		record[i].name.secondname = line;
		getline(file, line, ':');
		record[i].time.hour = stoi(line);
		getline(file, line);
		record[i].time.minutes = stoi(line);
		i++;
	}
	file.close();
}
//Запись данных в файл
void PutArray(list*& record, double time, int size, std::string filename, bool flag)
{
	std::ofstream(file);
	file.open(filename);
	file << time << "s\n";
	!flag ? file << "stable\n" : file << "unstable\n";
	for (int i = 0; i < size; i++)
	{
		file << record[i].room.litera << record[i].room.num << " ";
		file << record[i].name.lastname << " " << record[i].name.firstname << " " << record[i].name.secondname << " ";
		file << record[i].time.hour << ":" << record[i].time.minutes << std::endl;
	}
	file.close();
}
//сравнение сортировок
void SortCompare(int flagI, int flagS, double timeI, double timeS, std::string filename)
{
	std::ofstream(file);
	file.open(filename);
	file << "                Insert sort                    Sedgwick sort\n";
	file << "stable:       ";
	flagS == 0 ? file << "stable" : file << "unstable";
	flagI == 0 ? file << "                         stable\n" : file << "                       unstable\n";
	file << "time:        " << timeS << "                            " << timeI << std::endl;
	if (timeS < timeI)
		file << "Shell sort faster than Isertion sort";
	if (timeS > timeI)
		file << "Insertion sort faster than Shell sort";
	if (timeS == timeI)
		file << "Shell sort equal Isertion sort";
	file.close();
}
// Сортировка шелла растояние седжвика
void Sedgwick(list*& record, int size)
{
	int k = size;
	int *steps = new int[size];
	list temp;
	int step;

	int r = size - 1, left = 0;
	int q = 1;
	steps[0] = 1;
	while (steps[q - 1] * 3 < size)
	{
		if (q % 2 == 0)
		steps[q] = 9 * (1 << q) - 9 * (1 << (q / 2)) + 1;// Знак << для степени двойки
		else
		steps[q] = 8 * (1 << q) - 6 * (1 << ((q + 1) / 2)) + 1;
		q++;
	}
	q--;
	for (; q >= 0; q--)
	{
		step = steps[q];
		for (int i = left + step; i <= r; i++)
		{
			int j = i;
			int diff = j - step; 
			while (diff >= left && std::tie(record[diff].room.litera, record[diff].room.num) < std::tie(record[j].room.litera, record[j].room.num))
			{
				//смена
				temp = record[diff];
				record[diff] = record[j];
				record[j] = temp;
				j = diff;
				diff = j - step;
			}
			while (std::tie(record[diff].room.litera, record[diff].room.num) == (std::tie(record[j].room.litera, record[j].room.num))
				&& diff >= left && std::tie(record[diff].name.lastname, record[diff].name.firstname, record[diff].name.secondname) <
				(std::tie(record[j].name.lastname, record[j].name.firstname, record[j].name.secondname)))
			{
				//смена
				temp = record[diff];
				record[diff] = record[j];
				record[j] = temp;
				j = diff;
				diff = j - step;
			}
		}
	}
}
void STimer(double& time, list*& record, int size)
{
	std::chrono::time_point<std::chrono::high_resolution_clock>start, end;
	start = std::chrono::high_resolution_clock::now();
	Sedgwick(record, size);
	end = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> elapsedTime(end - start);
	const double seconds(elapsedTime.count());
	time = seconds;
}
void SedgwiStab(list*& record, int size,int flagS)

{
	int k = size;
	int* steps = new int[size];
	list temp;
	int step;

	int r = size - 1, left = 0;
	int q = 1;
	steps[0] = 1;
	while (steps[q - 1] * 3 < size)
	{
		if (q % 2 == 0)
			steps[q] = 9 * (1 << q) - 9 * (1 << (q / 2)) + 1;// Знак << для степени двойки
		else
			steps[q] = 8 * (1 << q) - 6 * (1 << ((q + 1) / 2)) + 1;
		q++;
	}
	q--;
	for (; q >= 0; q--)
	{
		step = steps[q];
		for (int i = left + step; i <= r; i++)
		{
			int j = i;
			int diff = j - step;
			if ((std::tie(record[diff].room.litera, record[diff].room.num) == std::tie(record[j].room.litera, record[j].room.num)) &&
				(std::tie(record[diff].name.lastname, record[diff].name.firstname, record[diff].name.secondname) == (std::tie(record[j].name.lastname, record[j].name.firstname, record[j].name.secondname))) &&
					(std::tie(record[diff].time.hour, record[diff].time.minutes) == std::tie(record[diff].time.hour, record[diff].time.minutes)))
			{

				while (diff <= left && std::tie(record[diff].room.litera, record[diff].room.num) < std::tie(record[j].room.litera, record[j].room.num))
				{
					//смена
					temp = record[diff];
					record[diff] = record[j];
					record[j] = temp;
					j = diff;
					diff = j - step;
				}
				while (std::tie(record[diff].room.litera, record[diff].room.num) == (std::tie(record[j].room.litera, record[j].room.num))
					&& diff <= left && std::tie(record[diff].name.lastname, record[diff].name.firstname, record[diff].name.secondname) <
					(std::tie(record[j].name.lastname, record[j].name.firstname, record[j].name.secondname)))
				{
					//смена
					temp = record[diff];
					record[diff] = record[j];
					record[j] = temp;
					j = diff;
					diff = j - step;
				}
				flagS = 1;
			}
		}
	}
}
//Сортировка вставки
void InsertSort(list*& record, int size)
{
	list temp;
	for (int i = 0; i < size; i++)
	{
		for (int j = i; j > 0 && std::tie(record[j - 1].room.litera, record[j - 1].room.num) < std::tie(record[j].room.litera, record[j].room.num); j--)
		{
			temp = record[j - 1];
			record[j - 1] = record[j];
			record[j] = temp;
		}
	}
	for (int i = 0; i < size; i++)
	{
		if (std::tie(record[i].room.litera, record[i].room.num) == std::tie(record[i - 1].room.litera, record[i - 1].room.num))
		{
			for (int j = i; j > 0 && std::tie(record[j - 1].name.lastname, record[j - 1].name.firstname, record[j - 1].name.secondname) < std::tie(record[j].name.lastname, record[j].name.firstname, record[j].name.secondname); j--)
			{
				temp = record[j - 1];
				record[j - 1] = record[j];
				record[j] = temp;
			}
		}
		else if (std::tie(record[i].room.litera, record[i].room.num) == std::tie(record[i + 1].room.litera, record[i + 1].room.num))
		{
			for (int j = i; j < size && std::tie(record[j + 1].name.lastname, record[j + 1].name.firstname, record[j + 1].name.secondname) > std::tie(record[j].name.lastname, record[j].name.firstname, record[j].name.secondname); j++)
			{
				temp = record[j + 1];
				record[j + 1] = record[j];
				record[j] = temp;
			}
		}
	}
}
void InsertStab(list* record, int size, int flagI)
{
	list temp;
	flagI = 0;
	for (int i = 0; i < size; i++)
	{
		if (std::tie(record[i].room.litera, record[i].room.num, record[i].name.lastname, record[i].name.firstname, record[i].name.secondname,
			record[i].time.hour, record[i].time.minutes) == std::tie(record[i - 1].room.litera, record[i - 1].room.num, record[i - 1].name.lastname,
				record[i - 1].name.firstname, record[i - 1].name.secondname, record[i - 1].time.hour, record[i - 1].time.minutes))
		{
			for (int j = i; j > 0 && std::tie(record[j - 1].room.litera, record[j - 1].room.num, record[j - 1].name.lastname,
				record[j - 1].name.firstname, record[j - 1].name.secondname, record[j - 1].time.hour, record[j - 1].time.minutes) < std::tie(record[j].room.litera, record[j].room.num,
					record[j].name.lastname, record[j].name.firstname, record[j].name.secondname, record[j].time.hour, record[j].time.minutes); j--)
			{
				temp = record[j - 1];
				record[j - 1] = record[j];
				record[j] = temp;
				flagI = 1;
			}
		}
	}
}
void ITimer(double& time, list*& record, int size)
{
	std::chrono::time_point<std::chrono::high_resolution_clock>start, end;
	start = std::chrono::high_resolution_clock::now();
	InsertSort(record, size);
	end = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> elapsedTime(end - start);
	const double seconds(elapsedTime.count());
	time = seconds;
}

int main()
{
	setlocale(LC_ALL, "rus");
	int size;
	int flagI = 0, flagS = 0;
	double timeS, timeI, time;
	std::ifstream file;
	GetSize(size, "input.txt");
	list*  record1 = new list[size]; 
	list* record2 = new list[size];



	GetArray(record1, size, "input.txt");

	InsertStab(record1, size,flagI);
	ITimer(timeI, record1, size);
	PutArray(record1, timeI, size, "InsertOut.txt", flagI);


	GetArray(record2, size, "input.txt");
    SedgwiStab(record2, size,flagS);
	STimer(timeS, record2, size);
	PutArray(record2, timeS, size, "SedgwOut.txt", flagS);


	SortCompare(flagI, flagS, timeI, timeS, "Srav.txt");
	return 0;
}