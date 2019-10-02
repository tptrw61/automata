#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include "FiniteAutomata.h"


const std::string ALPHABET = "01";

std::string stripToAlphabet(const std::string& str, const std::string& alphabet);

int main(int argc, char **argv) {
	std::vector<std::string> args;
	for (int i = 1; i < argc; i++) {
		args.push_back(stripToAlphabet(argv[i], ALPHABET));
	}

	FiniteAutomata fa(2);
	fa.addRule(0, '0', 0);
	fa.addRule(0, '1', 1);
	fa.addRule(1, '0', 1);
	fa.addRule(1, '1', 0);
	
	fa.setStartState(0);
	fa.setAcceptState(1);

	assert(fa.test("010"));
	assert(!fa.test("0101"));
	assert(!fa.test("0110 111"));
	assert(fa.test("111"));
	assert(!fa.test(""));

	if (args.size() > 0) {
		for (int i = 0; i < args.size(); i++)
			if (fa.test(args[i]))
				std::cout << "accept: " << args[i] << std::endl;
			else
				std::cout << "reject: " << args[i] << std::endl;
	}
	else {
		std::string line;
		while (std::getline(std::cin, line)) {
			line = stripToAlphabet(line, ALPHABET);
			if (fa.test(line))
				std::cout << "accept: " << line << std::endl;
			else
				std::cout << "reject: " << line << std::endl;
		}
	}

	return 0;
}

std::string stripToAlphabet(const std::string& str, const std::string& alphabet) {
	std::string ss;
	for (int i = 0; i < str.size(); i++)
		if (alphabet.find(str[i]) != std::string::npos)
			ss.push_back(str[i]);
	return ss;
}