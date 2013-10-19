/*!
@brief CodeIQ 'Longest word chain' ( https://codeiq.jp/ace/stakemura/q408 )
@author Shintaro TAKEMURA (stakemura@gmail.com)

This code is public domain, no warranty expressed or implied,
Functionality is thought to be correct, but it's up to you to make
sure it does what you want.
*/

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using std::vector;
using std::string;
using std::chrono::high_resolution_clock;

// 84 Reserved Words in C++
const vector<string> words = {
	"and",
	"alignof",
	"asm",
	"auto",
	"and_eq",
	"alignas",
	"bitand",
	"break",
	"bool",
	"bitor",
	"case", "continue",
	"catch",
	"compl",
	"char", "constexpr",
	"class",
	"char16_t", "char32_t", "const", "const_cast",
	"decltype", "delete", "double",
	"do",
	"default", "dynamic_cast",
	"else",
	"enum",
	"extern",
	"explicit", "export",
	"friend",
	"false",
	"for",
	"float",
	"goto",
	"inline",
	"if",
	"int",
	"long",
	"mutable",
	"namespace",
	"not_eq",
	"nullptr",
	"noexcept", "not",
	"new",
	"or_eq",
	"operator", "or",
	"public",
	"protected",
	"private",
	"return",
	"register",
	"reinterpret_cast",
	"static",
	"signed",
	"sizeof",
	"switch",
	"short", "static_assert", "static_cast", "struct",
	"typeid",
	"template", "true", "typename",
	"typedef",
	"thread_local",
	"this",
	"throw",
	"try",
	"unsigned",
	"using",
	"union",
	"void",
	"volatile",
	"virtual",
	"while",
	"wchar_t",
	"xor_eq",
	"xor"
};

// index list of previous words
vector<vector<size_t>> word_edges;

auto begin_time = high_resolution_clock::now();

void dfs(vector<size_t> &chain_max, vector<size_t> &chain, vector<int> &visit, size_t cur){
	for (auto &next : word_edges[cur]){
		if (visit[next]>=1) continue;

		chain.push_back(next);
		visit[next] += 1;
		dfs(chain_max, chain, visit, next);
		visit[next] -= 1;
		chain.pop_back();
	}
	if (chain.size() > chain_max.size()){
		auto end_time = high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - begin_time);
		std::cout << "--- " << chain.size() << " words (" << duration.count()/1000000.0 << " sec.) ---" << std::endl;

		chain_max = chain;
		for (auto &ri : chain_max)
			std::cout << words[ri] << std::endl;
	}
	//if (chain_max.size() >= 35) return;
}

int main(int argc, char *argv []){
	word_edges.resize(words.size());
	for (size_t i = 0; i < words.size(); i++){
		for (size_t j = 0; j < words.size(); j++){
			if (i == j) continue;
			if (words[i].front() == words[j].back()){
				word_edges[j].push_back(i);
			}
		}
	}

	// word chain having maximum length
	vector<size_t> chain_max;

	// word chain for buffer
	vector<size_t> chain;
	
	// visited(>0) or unvisited(=0) flag
	vector<int> visit;
	visit.assign(words.size(), 0);

	for (size_t head = 0; head < words.size(); head++){
		chain.push_back(head);
		visit[head] = 1;
		dfs(chain_max, chain, visit, head);
		visit[head] = 0;
		chain.pop_back();
	}
}
