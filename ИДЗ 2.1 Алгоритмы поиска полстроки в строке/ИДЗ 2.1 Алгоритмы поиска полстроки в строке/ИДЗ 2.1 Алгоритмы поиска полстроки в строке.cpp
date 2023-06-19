#include<iostream>
#include<fstream>
#include<string>
#include<chrono>
#include<vector>
# define NO_OF_CHARS 256
#define d 256
struct Auditorium
{
	char litera;
	int num;
};
struct sub
{
	std::string subj;
};
struct Times
{
	int hour;
	int minute;
};
struct list
{
	Auditorium room;
	std::string fullname;
	Times time;
	std::string object;
};

void GetSize(int& size, std::string filename)
{
	std::ifstream(file);
	file.open(filename);
	std::string line;
	std::getline(file, line);
	size = std::stoi(line);
	file.close();
};
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
		std::string name = line;
		getline(file, line, ' ');
		name = name + " " + line;
		getline(file, line, ' ');
		record[i].fullname = name + " " + line;
		getline(file, line, ':');
		record[i].time.hour = stoi(line);
		getline(file, line, ' ');
		record[i].time.minute = stoi(line);
		getline(file, line);
		record[i].object = line;
		i++;
	}
	file.close();
}
void PutArray(list*& record, double time, int size, std::string filename)
{
	std::ofstream(file);
	file.open(filename);
	file << time << "s\n";
	for (int i = 0; i < size; i++)
	{
		file << record[i].room.litera << record[i].room.num << " ";
		file << record[i].fullname << " ";
		file << record[i].time.hour << ":" << record[i].time.minute << std::endl;
		file << record[i].object << " ";
	}
	file.close();
};


void badCharHeuristic(std::string pattern, int size, std::vector<char>& badchar)
{
	int i;

	for (i = 0; i < NO_OF_CHARS; i++)
		badchar[i] = -1;

	for (i = 0; i < size; i++)
		badchar[(int)pattern[i]] = i;
}
void BMH(std::string str, std::string pattern, int& res, int& t, std::vector<char> badchar)
{
	int m = pattern.length();
	int n = str.length();

	res = -1;
	t = 0;

	int s = 0;
	while (s <= (n - m))
	{
		int j = m - 1;
		while (j >= 0 && pattern[j] == str[s + j])
			j--;
		if (j < 0)
		{
			t++;
			res = 1;
			s += (s + m < n) ? m - badchar[str[s + m]] : 1;
		}
		else
			s += std::max(1, j - badchar[str[s + j]]);
	}
}
void BMHTimer(list* record, double& time, std::string pattern, int size, int res1, int res2, int m1, int m2, std::string filename)
{
	std::vector<char> badchar(NO_OF_CHARS);
	int m = pattern.length();
	badCharHeuristic(pattern, m, badchar);
	std::chrono::time_point<std::chrono::high_resolution_clock>start, end;
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < size; i++)
	{
		BMH(record[i].fullname, pattern, res1, m1, badchar);
		BMH(record[i].object, pattern, res2, m2, badchar);
	}
	end = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> elapsedTime(end - start);
	const double seconds(elapsedTime.count());
	time = seconds;
}
void BMH_search(list* record, std::string pattern, int size)
{
	list* listing2 = new list[size];
	double time = 0;
	int res1 = 0, res2 = 0, m1 = 0, m2 = 0, j = 0;
	std::vector<char> badchar(NO_OF_CHARS);
	int m = pattern.length();
	BMHTimer(record, time, pattern, size, res1, res2, m1, m2, "OutputBMH.txt");
	badCharHeuristic(pattern, m, badchar);
	for (int i = 0; i < size; i++)
	{
		BMH(record[i].fullname, pattern, res1, m1, badchar);
		BMH(record[i].object, pattern, res2, m2, badchar);
		if ((res1 != -1 && m1 == 1) && (res2 != -1 && m2 == 1))
		{
			listing2[j] = record[i];
			j++;
		}
	}
	PutArray(listing2, time, j, "Output1.txt");
}


void RBK(std::string str, std::string pattern, int& res, int& mt)
{
	int q = 13;
	int m = pattern.size();
	int n = str.size();
	int i, j;
	int p = 0;//хеш патерна
	int t = 0;//хеш текста
	int h = 1;
	mt = 0;
	for (i = 0; i < m - 1; i++)
		h = (h * d) % q;

	// Calculate hash value for pattern and text
	for (i = 0; i < m; i++) 
	{
		p = (d * p + pattern[i]) % q;
		t = (d * t + str[i]) % q;
	}

	// Find the match
	for (i = 0; i <= n - m; i++) 
	{
		if (p == t) 
		{
			for (j = 0; j < m; j++) 
			{
				if (str[i + j] != pattern[j])
					break;
			}

			if (j == m)
			{
				res = 1;
				mt++;
			}
		}

		if (i < n - m) {
			t = (d * (t - str[i] * h) + str[i + m]) % q;

			if (t < 0)
				t = (t + q);
		}
	}
}
void RBKTimer(list* record, double& time, std::string pattern, int size, int res1, int res2, int m1, int m2, std::string filename)
{
	std::vector<char> badchar(NO_OF_CHARS);
	int m = pattern.length();
	//badCharHeuristic(pattern, m, badchar);
	std::chrono::time_point<std::chrono::high_resolution_clock>start, end;
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < size; i++)
	{
		RBK(record[i].fullname, pattern, res1, m1);
		RBK(record[i].object, pattern, res2, m2);
	}
	end = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> elapsedTime(end - start);
	const double seconds(elapsedTime.count());
	time = seconds;
}
void RBK_search(list* record, std::string pattern, int size)
{
	list* listing2 = new list[size];
	double time = 0;
	int res1 = 0, res2 = 0, m1 = 0, m2 = 0, j = 0;
	//std::vector<char> badchar(NO_OF_CHARS);
	int m = pattern.length();
	RBKTimer(record, time, pattern, size, res1, res2, m1, m2, "OutputRBK.txt");
	//badCharHeuristic(pattern, m, badchar);
	for (int i = 0; i < size; i++)
	{
		RBK(record[i].fullname, pattern, res1, m1);
		RBK(record[i].object, pattern, res2, m2);
		if ((res1 != -1 && m1 == 1) && (res2 != -1 && m2 == 1))
		{
			listing2[j] = record[i];
			j++;
		}
	}
	PutArray(listing2, time, j, "Output2.txt");
}


int main()
{
	int size{};
	double time{};
	int res1 = 0, res2 = 0, m1 = 0, m2 = 0;
	std::ifstream file;
	GetSize(size, "input.txt");
	list* record1 = new list[size];

	GetArray(record1, size, "input.txt");
	file.close();
	std::string pattern = "A";

	BMH_search(record1, pattern, size);
	RBK_search(record1, pattern, size);
}