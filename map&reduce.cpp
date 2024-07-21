#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>


struct ComparePairs {
	bool operator()(const std::pair<std::vector<char>, int>& a,
		const std::pair<std::vector<char>, int>& b) const {
		
		// 벡터의 내용을 비교
		if (a.second > b.second) {
			return true;
		}
		else if (a.second < b.second) {
			return false;
		}
		// 벡터가 같다면 두 번째 요소(int)를 비교
		return a.first < b.first;
	}
};

class wordcount {
private:
	
	std::vector<std::pair<std::vector<char>, int>> word_count_list;

public:
	void input(const char* input) {
		map(input);
		sort();
		reduce();
		sort();
	}
	void map(const char* input) {		// map 단계
		int word_size = 0;
		std::vector<char> word;
		for (int i = 0; '\0' != input[i]; i += word_size) {
			word_size = 0;
			word = {};
			for (int j = i; ' ' != input[j] && '\0' != input[j]; j++) {
				word_size++;
				word.push_back(input[j]);
			}
			word_count_list.push_back(std::make_pair(word, 1));
			i++;
		}
	}
	void reduce() {
		for (int i = 0; i < word_count_list.size() - 1; i++) {
			if (word_count_list[i].first == word_count_list[i + 1].first) {
				word_count_list[i].second++;
				word_count_list.erase(word_count_list.begin() + i + 1);
				continue;
			}
		}
	}
	void sort() {
		std::sort(word_count_list.begin(), word_count_list.end(), ComparePairs());
	}
	void print() {
		for (auto &i : word_count_list) {
			for (auto j : i.first) {
				std::cout << j;
			}
			std::cout << i.second << std::endl;
		}
	}
	
	
};


int main() {

	const char* input1 = "The quick brown fox jumps over a rabbit\0";
	const char* input2 = "The quick marathon runner won the race\0";
	wordcount in_word;
	in_word.input(input1);
	in_word.input(input2);
	in_word.print();
	

	return 0;
}