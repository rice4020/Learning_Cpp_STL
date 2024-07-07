#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <chrono>

class Student {
	std::pair<int, int> name;
	bool vaccinated;
public:
	Student(std::pair<int,int> name, bool whether)
		:name(name), vaccinated(whether) {}
	bool operator<(const Student& other) const {
		if (name.first == other.name.first) { return name.second < other.name.second; }
		return name.first < other.name.first;
	}
	const std::pair<int, int>& return_name() const { return name; }
	const bool& return_vaccinated() const { return vaccinated; }
};

bool need_student_vaccine(std::vector<Student> student_list, int name, int id) {
	std::pair<int, int> target = { name,id };
	auto rule = [](const Student& left, const std::pair<int, int>& right) {
		if (left.return_name().first == right.first) { return left.return_name().second < right.second; }
		return left.return_name().second < right.first;
		};
	auto iterator = std::lower_bound(student_list.begin(), student_list.end(),target,rule);
	if (iterator == student_list.end()) { return true; }
	if (!iterator->return_vaccinated()) { 
		iterator->return_vaccinated() == true;
		return true;
	}
	return false;
}

void student_sort(std::vector<Student>& student_list) {
	std::sort(student_list.begin(), student_list.end());
}

int main() {
	int last_name;	//��
	int name;		//�̸�

	std::vector<Student> student_list = {
        { {1, 3}, true },
        { {2, 2}, false },
        { {2, 3}, true }
    };
	
	student_sort(student_list);
	for (;;) {
		std::cout << "�̸��� ���� �Է��� �ֽʽÿ�.\n(������ ������� -1�� �Է��� �ֽʽÿ�)" << std::endl;
		std::cin >> name;
		if (name == -1) { break; }
		std::cin>>last_name;

		auto begin = std::chrono::steady_clock::now();
		bool vaccine_check = need_student_vaccine(student_list, name, last_name);
		auto end = std::chrono::steady_clock::now();
		auto difference = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

		std::cout << "���� �˻� �ҿ� �ð� : " << difference.count() << "us\n";
		if (vaccine_check) { std::cout << "(" << name << " " << last_name << ") �л��� ���� ������ �ʿ��մϴ�.\n\n"; }
		else{ std::cout << "(" << name << " " << last_name << ") �л��� ���� ������ �ʿ����� �ʽ��ϴ�.\n\n"; }
	}

	std::cout << "\n����Ǿ����ϴ�.\n" << std::endl;
	return 0;
}