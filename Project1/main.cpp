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

	Student(std::string line) // "이요한[15],학번[10],1997[4],학과,01012345678"
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
	Student(std::string nm, int stdid, int birth, std::string depart, std::string tel)
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

void Insertion() // 요한
{
	// 이름 입력
	std::cout << "\nEnter student's name : ";
	std::string name;

	//std::cin >> name;
	std::cin.ignore(); // cin의 whitespace를 무시? 하고 getline으로 값 받기
	std::getline(std::cin, name);

	if (name.empty())
	{
		// 에러
		std::cout << "\nPlease enter the name.\n\n";
		return;
	}

	if (name.length() > 15)
	{
		// 에러
		std::cout << "\nPlease enter the name.\n\n";
		return;
	}

	// 학번
	int stdid;

	std::cout << "Enter student id:";
	std::cin >> stdid;

	if (stdid < 1000000000 || stdid > 9999999999) // 10자리 확인
	{
		// 자리수 에러
		std::cout << "Please enter correct student ID. you should enter 10 digits.\n" << std::endl;
		return;
	}

	if (stdid < 1900000000 || stdid > 2077000000) // 연도 확인.. 임의로 1900~2077로 설정
	{
		// 학번 에러
		std::cout << "Please enter correct student ID.\n Student IDs can only be entered from 1900 to 2077\n" << std::endl;

		return;
	}

	// 중복체크
	for (Student student : student_info)
	{
		if (student.student_id == stdid)
		{
			// 에러
			std::cout << "\nError : Already inserted\n";

			return;
		}
	}


	// 생년
	int birth;
	std::cout << "Enter student's birth year :";
	if (!(std::cin >> birth))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}


	/*
		if (cin >> taxableIncome) {
		break;
	} else {
		cout << "Please enter a valid integer" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	*/

	/**
	if (birth.length() < 4) {
		// 에러
		return;
	}
	birth = birth.substr(0, 4); // 앞의 4자리?
	**/

	if (birth < 1000 || birth > 9999)
	{
		// 에러
		std::cout << "\nPlease enter correct birth year.\nyou should enter 4 digits.\n" << std::endl;

		return;
	}

	// 학과
	std::string depart;
	std::cout << "Enter student's department :";
	// std::cin >> depart;
	std::cin.ignore();
	std::getline(std::cin, depart); // 공백도 받게


	// 전화번호
	std::string tel;
	std::cout << "Enter student's TEL number :";
	std::cin >> tel;

	// 12자리 체크
	if (tel.length() > 12) //최대 12자리
	{
		// 에러
		std::cout << "\nPlease enter correct TEL number.\nTEL number has up to 12 digits.\n\n";

		return;
	}

	// 저장
	Student s(name, stdid, birth, depart, tel);
	WriteLine(s);
	std::cout << "\nsaved successfully!\n\n";

}

void Search()
{
	for (Student student : student_info) std::cout << student.name << std::endl;
}


bool Comparename(Student a, Student b)
{
	return a.name < b.name;
}
bool Compareid(Student a, Student b)
{
	return a.student_id < b.student_id;
}
bool Compareyear(Student a, Student b)
{
	return a.birth_year < b.birth_year;
}
bool Comparedepart(Student a, Student b)
{
	return a.department < b.department;
}

void Sorting()
{
	int sortnum = 0;

	while (sortnum > 4 || sortnum < 1)
	{
		std::cout << "- Sorting Option\n1. Sort by Name\n2. Sort by Student ID\n3. Sort by Admission year\n4. Sort by Department namet\n";
		std::cin >> sortnum;
		if (sortnum == 1) std::sort(student_info.begin(), student_info.end(), Comparename);
		else if (sortnum == 2) std::sort(student_info.begin(), student_info.end(), Compareid);
		else if (sortnum == 3) std::sort(student_info.begin(), student_info.end(), Compareyear);
		else if (sortnum == 4) std::sort(student_info.begin(), student_info.end(), Comparedepart);
		else std::cout << "invalid order";
	}
	std::cout << "Go back to the main menu, after selecting the sorting option..\n";
	WriteAll();
}

int main(int argc, char** argv) // run.exe stu.txt jjhg ==> argc=3,  run.exe => argc=1
{
	if (argc < 2)
	{
		//	std::cout << "Please enter a file name.\n";
		//	return 0;
		file = "file1.txt";
	}
	else
	{
		file = argv[1];
	}


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
		else std::cout << num << " Please enter the correct number.\n";

	}
	std::cout << "Program terminated\n";
	return 0;
}


