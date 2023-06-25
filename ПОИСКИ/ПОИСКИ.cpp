/**Входные данные :
1) ключ поиска;
2) текстовый файл, каждая из строк которого содержит данные задания 2.1
(адаптировать входные данные для поиска по цифровому полю
(например, номер рейса / номер аудитории / номер группы / госномер - сделать одним цифровым полем без букв)).
Выходные данные :
1) номер строки входного файла, содержащей заданный ключ поиска;
2) количество шагов поиска каждым из алгоритмов(см.свой вариант задания)
(без учета сортировки любым алгоритмом задания 1.3).*/
//Колпакова Александра - алгоритмы: линейный, интерполяционный; первое найденное вхождение
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
struct auditorium
{
	int num;
};
struct fullname
{
	std::string names;
};
struct sub
{
	std::string subj;
};
struct times
{
	int hour;
	int mint;
};
struct list
{
	auditorium room;
	fullname name;
	sub subject;
	times time;
	int str;
};

void GetSize(int& size, std::string filename)
{
	std::ifstream(file);
	file.open(filename);
	std::string line;
	std::getline(file, line);
	size = std::stoi(line);
	file.close();
}
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
		record[i].room.num = stoi(line);
		getline(file, line, ' ');
		std::string lastname = line;
		getline(file, line, ' ');
		std::string name = line;
		getline(file, line, ' ');
		std::string midlename = line;
		record[i].name.names = lastname + " " + name + " " + midlename;
		getline(file, line, ':');
		record[i].time.hour = stoi(line);
		getline(file, line, ' ');
		record[i].time.mint = stoi(line);
		getline(file, line);
		record[i].subject.subj = line;
		record[i].str = i;
		i++;
	}
	file.close();
}
void PutArray(int step, int pos, std::string filename)
{
	std::ofstream(file);
	file.open(filename);
	file << "Номер строки: " << pos << std::endl << "Количество шагов: " << step << std::endl;
	file.close();
}

void Lenear_Search(std::vector<int>& array, int size, int& step, int& pos, int pattern)
{
	pos = 2;
	step = 1;
	for (int i = 1; i < size; i++)
	{
		if (array[i] == pattern)
		{
			step++;
			pos = i;
		}
	}
}
void Linear(list* record, int size, int pattern)
{
	int step, pos;
	std::vector <int> array(size);
	for (int i = 1; i < size; i++)
	{
		array[i] = record[i].room.num;
	}
	Lenear_Search(array, size, step, pos, pattern);
	PutArray(step, pos, "LinearOutput.txt");
}

void InsertSort(list*& record, int size)
{
	list tmp;
	for (int i = 1; i < size; i++)
	{
		for (int j = i; j > 0 && record[j - 1].room.num > record[j].room.num; j--)
		{
			tmp = record[j];
			record[j] = record[j - 1];
			record[j - 1] = tmp;
		}
	}
}
void InterpolSearch(int* array, int size, int& step, int& pos, int pattern)
{

	int mid=0;
	int left = 1;
	int right = size - 1;
	 pos = 0;
	 step =0;
	while ( /*left <= right &&*/ array[left] <= pattern && array[right] >= pattern)
	{
		mid = left + ((pattern - array[left]) * (right - left)) / (array[right] - array[left]);
		if (array[mid] < pattern) {
			left = mid + 1;
			step++;
		}
		if (array[mid] > pattern) {
			right = mid - 1;
			step++;
		}
		if (array[mid] == pattern) {
			pos = mid+1;
			step++;
			break;
		}

	}

	if (array[left] == pattern) {
		pos = left;
		step ++;
	}
	

	
}
void Interpo(list* record, int size, int pattern)
{

	int step, pos;
	InsertSort(record, size);
	int *array1 = new int[size];
	for (int i = 1; i < size; i++)
	{
		array1[i] = record[i].room.num;
	}
	InterpolSearch(array1, size, step, pos, pattern);
	PutArray(step, pos, "InterpoOutput.txt");
}




int main()
{
	setlocale(LC_ALL, "rus");
	int size;
	int pattern = 112;
	std::ifstream file;
	file.open("input.txt");
	GetSize(size, "input.txt");
	list* record = new list[size];
	GetArray(record, size, "input.txt");


	Linear(record, size, pattern);
	//InsertSort(record, size);
	Interpo(record, size, pattern);
	file.close();
	return 0;
}

