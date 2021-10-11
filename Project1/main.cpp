#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctype.h>

class Student
{
public:
	std::string name;
	long long student_id;
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
		student_id = std::stoll(parse[1]);
		birth_year = std::stoi(parse[2]);
		department = parse[3];
		telephone = parse[4];
	}

	Student(std::string nm, long long stdid, int birth, std::string depart, std::string tel)
	{
		name = nm;
		student_id = stdid;
		birth_year = birth;
		department = depart;
		telephone = tel;

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

bool isDigitOnly(std::string str)
{
	for(char ch : str)
	{
		if (!isdigit(ch)) return false;
	}
	return true;

}

bool isCharOnly(std::string str)
{
	for (char ch : str)
	{
		if (isdigit(ch)) return false;
	}
	return true;

}

// trim from left 
inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
	s.erase(0, s.find_first_not_of(t));
	return s;
}

// trim from right 
inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
{
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

// trim from left & right 
inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
{
	return ltrim(rtrim(s, t), t);
}

std::string Input()
{
	std::string input_string;
	std::cin.clear();
	std::getline(std::cin, input_string);
	trim(input_string);
	return input_string;
}

std::string InputName()
{
	std::string name;
	for (;;)
	{
		std::cout << "\nEnter student's name\n";
		name = Input();

		if (name.empty()) std::cout << "\nPlease enter the name.\n";
		else if (name.length() > 15) std::cout << "\nPlease enter shorter name. you can enter up to 15 digits.\n";
		else if (!isCharOnly(name)) std::cout << "\nPlease enter correct name.(charactor only)\nyou should enter charactor.\n";
		else break;
	}
	return name;
}

long long InputStudentId(bool check = false)
{
	std::string string_id;
	long long student_id;
	for (;;)
	{
		std::cout << "\nEnter student id\n";
		string_id = Input();

		if (!isDigitOnly(string_id))
		{
			std::cout << "\nPlease input correct ID.\nYou should enter number.\n";
			continue;
		}

		student_id = std::stoll(string_id);
		if (string_id.length() != 10) std::cout << "\nPlease enter correct student ID(range). you should enter 10 digits.\n";
		else if (student_id < 1918000000 || student_id > 2077999999) std::cout << "\nPlease enter correct student ID.\nStudent IDs can only be entered from 1918 to 2077.\n";
		else if (check)
		{
			bool exist = false;
			for (Student student : student_info)
			{
				if (student.student_id == student_id)
				{
					std::cout << "\nError : Already inserted\n";
					exist = true;
					break;
				}
			}
			if (!exist) break;
		}
		else break;
	}
	return student_id;
}

int InputBirthYear()
{
	std::string string_year;
	int birth_year;
	for (;;)
	{
		std::cout << "\nEnter birth year\n";
		string_year = Input();

		if (!isDigitOnly(string_year))
		{
			std::cout << "\nPlease input correct year.\nYou should enter number.\n";
			continue;
		}

		birth_year = std::stoi(string_year);
		if (birth_year < 1000 || birth_year > 9999) std::cout << "\nPlease enter correct birth year.\nyou should enter 4 digits.\n";
		else break;
	}
	return birth_year;
}

int InputAdmissionYear()
{
	std::string string_year;
	int admission_year;
	for (;;)
	{
		std::cout << "\nEnter admission year\n";
		string_year = Input();

		if (!isDigitOnly(string_year))
		{
			std::cout << "\nPlease input correct year.\nYou should enter number.\n";
			continue;
		}

		admission_year = std::stoi(string_year);
		if (admission_year < 1000 || admission_year > 9999) std::cout << "\nPlease enter correct admission year.\nyou should enter 4 digits.\n";
		else break;
	}
	return admission_year;
}

std::string InputDepartment()
{
	std::cout << "\nEnter student's department\n";
	return Input();
}

std::string InputTelephone()
{
	std::string telephone;
	for (;;)
	{
		std::cout << "\nEnter student's Tel number\n";
		telephone = Input();

		if (telephone.length() > 12 || telephone.length() < 10) std::cout << "\nPlease enter correct TEL.(length)\nyou should enter 11 to 12 digits.\n";
		else if (!isDigitOnly(telephone)) std::cout << "\nPlease enter correct TEL.(number only)\nyou should enter number.\n";
		else break;
	}
	return telephone;
}

void Insertion()
{
	std::cout << "\n- Insertion -\n";
	std::cin.ignore();
	std::string name = InputName();
	long long student_id = InputStudentId(true);
	int birth_year = InputBirthYear();
	std::string department = InputDepartment();
	std::string telephone = InputTelephone();
	

	// 저장
	Student s(name, student_id, birth_year, department, telephone);
	WriteLine(s);
	std::cout << "\nSaved successfully!\n\n";
}

void PrintSerachFirst()
{
	std::ostringstream ss;
	ss << std::left << std::setw(16) << "Name" << std::setw(16) << "Student ID" << std::setw(24) << "Dept" << std::setw(16) << "Birth Year" << std::setw(16) << "Tel";
	
	std::string ps = ss.str();
	std::cout << "\n" << ps << "\n";
}

void PrintSearchStudent(Student student)
{
	std::ostringstream ss;
	ss << std::left << std::setw(16) << student.name
		<< std::setw(16) << student.student_id
		<< std::setw(24) << student.department
		<< std::setw(16) << student.birth_year
		<< std::setw(16) << student.telephone;

	std::string ps = ss.str();
	std::cout << ps << "\n";
}

void PrintSearchLast(int num)
{
	std::cout << "\nTotal " << num << " student was found.\n\n";
}

void SearchName()
{
	int num = 0;
	std::cin.ignore();
	std::string name = InputName();

	PrintSerachFirst();
	for (Student student : student_info) 
	{
		if (student.name == name) PrintSearchStudent(student), num++;
	}
	PrintSearchLast(num);
}

void SearchId() 
{
	int num = 0;
	std::cin.ignore();
	long long student_id = InputStudentId(false);

	PrintSerachFirst();
	for (Student student : student_info)
	{
		if (student.student_id == student_id) PrintSearchStudent(student), num++;
	}
	PrintSearchLast(num);
}

void SearchYear() 
{
	int num = 0;
	std::cin.ignore();
	int year = InputAdmissionYear();

	PrintSerachFirst();
	for (Student student : student_info)
	{
		if (student.student_id / 1000000 == year) PrintSearchStudent(student), num++;
	}
	PrintSearchLast(num);
}

void SearchDepartment()
{
	int num = 0;
	std::cin.ignore();
	std::string department = InputDepartment();

	PrintSerachFirst();
	for (Student student : student_info)
	{
		if (student.department == department) PrintSearchStudent(student), num++;
	}
	PrintSearchLast(num);

}

void SearchAll() 
{
	int num = 0;

	PrintSerachFirst();
	for (Student student : student_info) PrintSearchStudent(student), num++;
	PrintSearchLast(num);
}

void Search()
{
	while (true)
	{
		int num = 0;
		std::cout << "\n- Search -\n1. Search by name\n2. Search by student ID\n3. Search by admission year\n4. Search by department name\n5. List All\n6. Exit\n";
		std::cin >> num;

		if (num == 1) SearchName();
		else if (num == 2) SearchId();
		else if (num == 3) SearchYear();
		else if (num == 4) SearchDepartment();
		else if (num == 5) SearchAll();
		else if (num != 6) std::cout << "Please enter the correct number.\n";

		if (num >= 1 && num <= 6) break;
	}
}

bool CompareName(Student a, Student b)
{
	return a.name < b.name;
}
bool CompareId(Student a, Student b)
{
	return a.student_id < b.student_id;
}
bool CompareYear(Student a, Student b)
{
	return a.student_id / 1000000 < b.student_id / 1000000;
}
bool CompareDepart(Student a, Student b)
{
	return a.department < b.department;
}

void Sorting()
{
	int sortnum = 0;

	while (sortnum > 4 || sortnum < 1)
	{
		std::cout << "\n- Sorting Option -\n1. Sort by Name\n2. Sort by Student ID\n3. Sort by Admission year\n4. Sort by Department name\n";
		std::cin >> sortnum;

		if (sortnum == 1) std::sort(student_info.begin(), student_info.end(), CompareName);
		else if (sortnum == 2) std::sort(student_info.begin(), student_info.end(), CompareId);
		else if (sortnum == 3) std::sort(student_info.begin(), student_info.end(), CompareYear);
		else if (sortnum == 4) std::sort(student_info.begin(), student_info.end(), CompareDepart);
		else std::cout << "invalid order";
	}

	WriteAll();
	std::cout << "\nGo back to the main menu, after selecting the sorting option..\n\n";
}

int main(int argc, char** argv)
{
	if (argc < 2) file = "file1.txt";
	else file = argv[1];

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
