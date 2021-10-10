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

bool isDigitOnly(std::string in)
{
	for (int i = 0; i < in.length(); i++)
	{
		if (!isdigit(in[i])) {
			return false;
		}

	}
	return true;

}

bool isCharOnly(std::string in)
{
	for (int i = 0; i < in.length(); i++) // for (초기값; 반복조건 ; 증감연산자 ) 
	{
		if (isdigit(in[i])) 
		{
			return false;
		}

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


void Insertion() // 요한

{
	// 이름 입력

	std::string name;
	

	for (;;)
	{
		std::cout << "\nEnter student's name : ";
		std::cin.ignore(); // cin의 whitespace를 무시? 하고 getline으로 값 받기
		std::getline(std::cin, name);
		trim(name);
		std::cout << name << "\n";


		if (name.empty())
		{

			// 에러
			std::cout << "Please enter the name.\n";
			//std::cin.ignore(); // 엔터도 공백으로 인식하기 위해서 ignore 쓰지 않음.
			continue;
		}


		if (name.length() > 15)
		{
			// 에러
			std::cout << "Please enter shorter name. you can enter up to 15 digits.\n";
			continue;
		}
		
		if (!isCharOnly(name))
		{
			// 에러
			std::cout << "\nPlease enter correct name.(charactor only)\nyou should enter charactor. your input=" << name << "\n";
			continue;
		}

			break;
		
	}

	// 학번
	int stdid;

	
	//std::cin.ignore();
	
	for (;;)
	{
		std::cout << "Enter student id: ";
		//std::cin.ignore();

		if (!(std::cin >> stdid)) { //0
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "\nPlease enter correct student id(digit).\nyou should enter 10 digits. your input="<<stdid<<"\n";
			// std::cin.ignore();

			continue;
		}

		if (stdid < 1000000000 || stdid > 9999999999) // 10자리 확인
		{
			// 자리수 에러
			std::cout << "Please enter correct student ID(range). you should enter 10 digits. your input=" << stdid << "\n";
			//std::cin.ignore();
			continue;
		}

		if (stdid < 1918000000 || stdid > 2077000000) // 연도 확인.. 임의로 1918~2077로 설정
		{
			// 학번 에러
			std::cout << "Please enter correct student ID.\n Student IDs can only be entered from 1900 to 2077. your input=" << stdid << "\n";
			//std::cin.ignore();
			continue;
		}

		// 중복체크
		bool exist = false;

		for (Student student : student_info)
		{
			if (student.student_id == stdid)
			{
				// 에러
				std::cout << "\nError : Already inserted\n";
				exist = true;
				break;
			}
		}

		if (exist) continue;
		else break;

	}


	// 생년
	int birth;

	/*
	if (!(std::cin >> birth))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	*/

	for (;;)
	{
		std::cout << "Enter student's birth year : ";
		//std::cin.ignore();

		if (!(std::cin >> birth))  // 숫자가 아니면 0 이 반환, 숫자면 true
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "\nPlease enter correct birth year.\nyou should enter 4 digits. your input=" << birth << "\n";
			// std::cin.ignore();
			continue;
		}
		

		if (birth < 1000 || birth > 9999)
		{
			// 에러
			std::cout << "\nPlease enter correct birth year.\nyou should enter 4 digits. your input=" << birth << "\n";
			std::cin.ignore();
			continue;
		}
		//std::cout << "your input=" << birth << "\n";
		break;

	}


	/**
	if (birth.length() < 4) {
		// 에러
		return;
	}
	birth = birth.substr(0, 4); // 앞의 4자리?
	**/

	// 학과
	std::string depart;
	std::cout << "Enter student's department :";
	// std::cin >> depart;
	std::cin.ignore();
	std::getline(std::cin, depart); // 공백도 받게


	// 전화번호
	std::string tel;


	// 12자리 체크

	for (;;)
	{
		std::cout << "Enter student's TEL number : ";

		std::cin >> tel;
		trim(tel);

		if (tel.length() > 12 || tel.length() < 10) //최대 12자리
		{
			// 에러
			std::cout << "\nPlease enter correct TEL.(length)\nyou should enter 11 to 12 digits. your input=" << tel << "\n";
			//std::cin.ignore();
			continue;
		}

		if (!isDigitOnly(tel)) 
		{
			// 에러
			std::cout << "\nPlease enter correct TEL.(number only)\nyou should enter number. your input=" << tel << "\n";

			continue;
		}

		break;
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

void Sorting()
{
	std::sort(student_info.begin(), student_info.end(), [](Student a, Student b) { return a.name < b.name; });
	WriteAll();
}

int main(int argc, char** argv) // run.exe stu.txt jjhg ==> argc=3,  run.exe => argc=1
{
	if (argc < 2)
	{
	//	std::cout << "Please enter a file name.\n";
	//	return 0;
		file = "file1.txt";
	} else
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
