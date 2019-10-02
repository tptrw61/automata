#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "FiniteAutomata.h"


const std::string ALPHABET = "01";

std::string stripToAlphabet(const std::string& str, const std::string& alphabet);

int main(int argc, char **argv) {
	std::vector<std::string> args;
	for (int i = 1; i < argc; i++) {
		args.push_back(stripToAlphabet(argv[i], ALPHABET));
	}

	FiniteAutomata fa({"s","a","b","c","d","e"});

	//start state
	fa.addRule("s", EPSILON, "a");
	fa.addRule("s", EPSILON, "c");

	//exactly 2n 0s
	fa.addRule("a", '0', "a");
	fa.addRule("b", '0', "b");
	fa.addRule("a", '1', "b");
	fa.addRule("b", '1', "a");

	//exactly 3n 1s
	fa.addRule("c", '1', "c");
	fa.addRule("d", '1', "d");
	fa.addRule("e", '1', "e");
	fa.addRule("c", '0', "d");
	fa.addRule("d", '0', "e");
	fa.addRule("e", '0', "c");

	//start and accept states
	fa.setStartState("s");
	fa.setAcceptState("a");
	fa.setAcceptState("c");

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
