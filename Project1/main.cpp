#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>

class Student
{
public:
	std::string name;
	int student_id;
	int birth_year;
	std::string department;
	std::string telephone;

	Student(std::string line)
	{
		std::vector<std::string> parse;
		std::istringstream ss(line);
		std::string token;
		while (std::getline(ss, token, ',')) parse.push_back(token);

		name = parse[0];
		student_id = std::stoi(parse[1]);
		birth_year = std::stoi(parse[2]);
		department = parse[3];
		telephone = parse[4];
	}

	std::string GetStudent()
	{
		return name + "," +
			std::to_string(student_id) + "," +
			std::to_string(birth_year) + "," +
			department + "," +
			telephone;
	}
};

std::string file;
std::vector<Student> student_info;

void ReadAll()
{
	std::ifstream fin(file);
	if (!fin.is_open())
	{
		std::cout << "Since the file doesn't exist, it creates a new file.\n";
		std::ofstream make_file(file);
		make_file.close();
		return;
	}

	while (!fin.eof())
	{
		std::string line;
		std::getline(fin, line);
		if (line.empty()) break;
		Student s(line);
		student_info.push_back(s);
	}
	fin.close();
}

void WriteAll()
{
	std::ofstream fout(file);
	for (Student student : student_info) fout << student.GetStudent() << std::endl;
	fout.close();
}

void WriteLine(Student student)
{
	student_info.push_back(student);
	std::ofstream fout(file, std::ios::out | std::ios::app);
	fout << student.GetStudent() << std::endl;
	fout.close();
}

void Insertion()
{
	Student s("Inseo Park,1111111111,1996,Computer Science,01012345678");
	WriteLine(s);
}

void Search()
{
	for (Student student : student_info) std::cout << student.name << std::endl;
}

bool comparename(std::string a, std::string b)
{
	return a < b;
}
bool compareid(int a, int b)
{
	return a < b;
}
bool compareyear(int a, int b)
{
	return a < b;
}
bool comparedepart(std::string a, std::string b)
{
	return a < b;
}

void Sorting()
{
	int sortnum = 0;

	while (sortnum > 4 && sortnum<1)
	{
		std::cout << "- Sorting Option\n1. Sort by Name\n2. Sort by Student ID\n3. Sort by Admission year\n4. Sort by Department namet\n";
		std::cin >> sortnum;
		if (sortnum == 1) std::sort(student_info.begin(), student_info.end(), comparename);
		else if (sortnum == 2) std::sort(student_info.begin(), student_info.end(), compareid);
		else if (sortnum == 3) std::sort(student_info.begin(), student_info.end(), compareyear);
		else if (sortnum == 4) std::sort(student_info.begin(), student_info.end(), comparedepart);
		else
		{
	    std::cout << "invalid order";
		}
	}
	std::cout << "Go back to the main menu, after selecting the sorting option..";
	WriteAll();
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "Please enter a file name.\n";
		return 0;
	}
	file = argv[1];
	ReadAll();

	while (true)
	{
		int num = 0;
		std::cout << "1. Insertion\n2. Search\n3. Sorting Option\n4. Exit\n";
		std::cin >> num;

		if (num == 1) Insertion();
		else if (num == 2) Search();
		else if (num == 3) Sorting();
		else if (num == 4) break;
		else std::cout << "Please enter the correct number.\n";
	}
	std::cout << "Program terminated\n";
	return 0;
}
