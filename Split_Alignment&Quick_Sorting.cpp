#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <chrono>

class Student {
	std::pair<int, int> name;
	bool vaccinated;
public:
	Student(std::pair<int, int> name, bool whether)
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
	auto iterator = std::lower_bound(student_list.begin(), student_list.end(), target, rule);
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
	int last_name;	//성
	int name;		//이름

	std::vector<Student> student_list = {
		{ {1, 3}, true },
		{ {2, 2}, false },
		{ {2, 3}, true }
	};

	student_sort(student_list);
	for (;;) {
		std::cout << "이름과 성을 입력해 주십시오.\n(끝내고 싶은경우 -1을 입력해 주십시오)" << std::endl;
		std::cin >> name;
		if (name == -1) { break; }
		std::cin >> last_name;

		auto begin = std::chrono::steady_clock::now();
		bool vaccine_check = need_student_vaccine(student_list, name, last_name);
		auto end = std::chrono::steady_clock::now();
		auto difference = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

		std::cout << "이진 검색 소요 시간 : " << difference.count() << "us\n";
		if (vaccine_check) { std::cout << "(" << name << " " << last_name << ") 학생은 예방 접종이 필요합니다.\n\n"; }
		else { std::cout << "(" << name << " " << last_name << ") 학생은 예방 접종이 필요하지 않습니다.\n\n"; }
	}

	std::cout << "\n종료되었습니다.\n" << std::endl;
	return 0;
}



/*#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

template <typename T>		//분할 연산
auto partition(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end) {
	auto pivot_val = *begin;
	auto left_iter = begin + 1;
	auto right_iter = end;

	while (true) {
		while (*left_iter <= pivot_val && std::distance(left_iter, right_iter) > 0)
			left_iter++;
		while (*right_iter > pivot_val && std::distance(left_iter, right_iter) > 0)
			right_iter--;

		if (left_iter == right_iter) 
			break;
		else
			std::iter_swap(left_iter, right_iter);
	}

	if (pivot_val > *right_iter)
		std::iter_swap(begin, right_iter);
	return right_iter;
}

template <typename T>						//퀵 정렬
void quick_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator last) {
	if (std::distance(begin, last) >= 1) {
		//분할 연산
		auto partition_iter = partition<T>(begin, last);

		quick_sort<T>(begin, partition_iter - 1);
		quick_sort<T>(partition_iter, last);
	}
 }

template <typename T>
void partial_quick_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator last, size_t k) {
	if (std::distance(begin, last) >= 1) {
		//분할 연산
		auto partition_iter = partition<T>(begin, last);

		partial_quick_sort<T>(begin, partition_iter - 1, k);

		if (std::distance(begin, partition_iter) < k)
			partial_quick_sort<T>(partition_iter, last, k);
	}
}

template <typename T>
void print_vector(std::vector<T> arr) {
	for (auto i : arr)
		std::cout << i << " ";

	std::cout << std::endl;
}

template <typename T>
auto generate_random_vector(T size) {
	std::vector<T> V;
	V.reserve(size);

	std::random_device rd;
	std::mt19937 rand(rd());

	std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, size);

	for (T i = 0; i < size; i++)
		V.push_back(uniform_dist(rand));

	return std::move(V);
}

template <typename T>
void test_partial_quicksort(size_t size, size_t k) {
	auto random_vec = generate_random_vector<T>(size);
	auto random_vec_copy(random_vec);

	std::cout << "입력 벡터: " << std::endl;
	print_vector<T>(random_vec);

	auto begin1 = std::chrono::steady_clock::now();
	partial_quick_sort<T>(random_vec.begin(), random_vec.end() - 1, k);
	auto end1 = std::chrono::steady_clock::now();
	auto diff1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1);

	std::cout << std::endl;
	std::cout << "부분 퀵 정렬 수행 시간: " << diff1.count() << "us" << std::endl;
	
	std::cout << "(처음" << k << "개 원소만) 부분 정렬된 벡터:";
	print_vector<T>(random_vec);

	auto begin2 = std::chrono::steady_clock::now();
	quick_sort<T>(random_vec_copy.begin(), random_vec_copy.end() - 1);
	auto end2 = std::chrono::steady_clock::now();
	auto diff2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2);

	std::cout << std::endl;
	std::cout << "전체 퀵 저렬 수행시간: " << diff2.count() << "us" << std::endl;
	
	std::cout << "전체 정렬된 벡터: ";
	print_vector<T>(random_vec_copy);
}

int main() {
	test_partial_quicksort<unsigned>(100, 10);

	return 0;
}*/