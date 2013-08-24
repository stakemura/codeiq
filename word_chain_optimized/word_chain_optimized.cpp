/*!
@brief CodeIQ 'Word chain' problem ( https://codeiq.jp/ace/stakemura/q408 )
@author Shintaro TAKEMURA (stakemura@gmail.com)

This code is public domain, no warranty expressed or implied,
Functionality is thought to be correct, but it's up to you to make
sure it does what you want.
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <chrono>

using std::vector;
using std::unordered_set;
using std::unordered_map;
using std::string;
using std::chrono::high_resolution_clock;

//typedef string HeadTail;
typedef unsigned int HeadTail;

HeadTail get_headtail(const string &s){
	return (s.front() << 16) + s.back();
}

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

// word index list
unordered_map < HeadTail, vector<size_t>> headtails;

// index list of previous words
unordered_map < HeadTail, unordered_set<HeadTail>> headtail_edges;

auto begin_time = high_resolution_clock::now();

size_t max_length = 0;

vector<HeadTail> dfs(vector<HeadTail> &chain, unordered_map<HeadTail, size_t> &visit){
	// word chain having maximum length
	vector<HeadTail> chain_max;

	unordered_set<HeadTail> can_skip_headtails;

	bool  found_any = false;

	for (auto &next : headtail_edges[chain.back()]){
		if (visit[next] >= headtails[next].size()) continue;

		if (can_skip_headtails.count(next) > 0) continue;

		found_any = true;

		chain.push_back(next);
		visit[next] += 1;
		auto found_chain = dfs(chain, visit);
		visit[next] -= 1;
		chain.pop_back();

		if (found_chain.size() > chain_max.size()){
			chain_max = found_chain;

			can_skip_headtails.clear();
			for (size_t i = chain.size(); i < chain_max.size(); ++i)
				if (headtails[next].size()<=1)
					can_skip_headtails.insert(chain_max[i]);

			if (chain_max.size() > max_length)
			{
				max_length = chain_max.size();
				auto end_time = high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - begin_time);
				std::cout << "--- " << max_length << " words (" << duration.count() / 1000000.0 << " sec.) ---" << std::endl;

				for (auto ri = chain_max.cbegin(); ri != chain_max.cend();  ++ri)
				{
					std::cout << words[headtails[*ri][std::count(chain_max.cbegin(), ri, *ri)]] << std::endl;
				}
			}
		}
	}

	return found_any ? chain_max : chain;
}

int main(int argc, char *argv []){

	for (size_t i = 0; i < words.size(); i++){
		headtails[get_headtail(words[i])].push_back(i);
	}

	for (size_t i = 0; i < words.size(); i++){
		for (size_t j = 0; j < words.size(); j++){
			if (get_headtail(words[j]) == get_headtail(words[i])) continue;
			if (words[i].front() == words[j].back()){
				headtail_edges[get_headtail(words[j])].insert(get_headtail(words[i]));
			}
		}
	}

	// word chain for buffer
	vector<HeadTail> chain;
	
	// visited(>0) or unvisited(=0) flag
	unordered_map<HeadTail, size_t> visit;

	for (auto &hi : headtails){
		HeadTail head = hi.first;

		chain.push_back(head);
		visit[head] = 1;
		dfs(chain, visit);
		visit[head] = 0;
		chain.pop_back();
	}
}
