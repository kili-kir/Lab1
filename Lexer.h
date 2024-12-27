#pragma once
#include "Token.h"
#include "hash_table.h"
#include "Function.h"
#include "dfa.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

class Lexer {
private:
	HashTable hashTable;

	void getNextToken(vector<char>& alphabet, string& s, bool& flag, int& count) {
		if (s != "") {
			if (flag) {
				if (count != 2) {
					hashTable.insert(Token(TokenType::ERROR, s));
					flag = 0;
					count = 0;
					s.clear();
					return;
				}
			}
			else if (dfa(countStatesWhile, alphabet, finalStatesWhile, transitFunctionWhile).isAccept(s)) {
				hashTable.insert(Token(TokenType::KEYWORD, s));
				s.clear();
				return;
			}
			else if (dfa(countStatesInt, alphabet, finalStatesInt, transitFunctionInt).isAccept(s)) {
				hashTable.insert(Token(TokenType::KEYWORD, s));
				s.clear();
				return;
			}
			else if (dfa(countStatesBegin, alphabet, finalStatesBegin, transitFunctionBegin).isAccept(s)) {
				hashTable.insert(Token(TokenType::KEYWORD, s));
				s.clear();
				return;
			}
			else if (dfa(countStatesEnd, alphabet, finalStatesEnd, transitFunctionEnd).isAccept(s)) {
				hashTable.insert(Token(TokenType::KEYWORD, s));
				s.clear();
				return;
			}
			else if (dfa(countStatesProcedure, alphabet, finalStatesProcedure, transitFunctionProcedure).isAccept(s)) {
				hashTable.insert(Token(TokenType::KEYWORD, s));
				s.clear();
				return;
			}
			else if (dfa(countStatesVars, alphabet, finalStatesVars, transitFunctionVars).isAccept(s)) {
				hashTable.insert(Token(TokenType::KEYWORD, s));
				s.clear();
				return;
			}
			else if (dfa(countStatesDo, alphabet, finalStatesDo, transitFunctionDo).isAccept(s)) {
				hashTable.insert(Token(TokenType::KEYWORD, s));
				s.clear();
				return;
			}
			else if (dfa(countStatesMain, alphabet, finalStatesMain, transitFunctionMain).isAccept(s)) {

				hashTable.insert(Token(TokenType::ID, s));
				s.clear();
				return;
			}
			else if (dfa(countStatesVar, alphabet, finalStatesVar, transitFunctionVar).isAccept(s)) {
				hashTable.insert(Token(TokenType::ID, s));
				s.clear();
				return;
			}
			else if (dfa(countStatesConst, alphabet, finalStatesConst, transitFunctionConst).isAccept(s))
			{
				hashTable.insert(Token(TokenType::CONST, s));
				s.clear();
				return;
			}
			
			hashTable.insert(Token(TokenType::ERROR, s));
			s.clear();
		}
	};

public:
	void Alphabet(vector<char>& alphabet, string& alp) {
		for (char c = 'a'; c <= 'z'; c++) {
			alphabet.push_back(c);
		}
		for (char c = 'A'; c <= 'Z'; c++) {
			alphabet.push_back(c);
		}
		for (char c = '0'; c <= '9'; c++) {
			alphabet.push_back(c);
		}
		alphabet.push_back('.');
		alphabet.push_back('+');
		alphabet.push_back('-');
		alphabet.push_back(',');
		alphabet.push_back(';');
		alphabet.push_back('(');
		alphabet.push_back(')');
		alphabet.push_back('=');
		alphabet.push_back('<');
		alphabet.push_back('>');
		alphabet.push_back(';');
		alphabet.push_back(':');
		alp = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	}

	bool IsValidChar(char c, const std::string& alphabet) {
		for (char validChar : alphabet) {
			if (c == validChar) {
				return true;
			}
		}
		return false;
	}

	Lexer(ifstream& cin) {
		vector<char> alphabet;
		string alp;
		Alphabet(alphabet, alp);

		if (cin.eof()) {
			hashTable.insert(Token(TokenType::ERROR, "FILE"));
			return;
		}
		string str; char temp; 	bool f = 0; int c = 0;
		while (cin.get(temp)) {
			if (temp == ',' || temp == '(' || temp == ')'|| temp == ';') {
				getNextToken(alphabet, str, f, c);
				string u = "";
				u += temp;
				hashTable.insert(Token(TokenType::SEPARATORS, u));
			}
			else if (temp == ':') {
				getNextToken(alphabet, str, f, c);
				string u = "";
				u += temp;
				char temp2;
				cin.get(temp2);
				if (temp2 == '=') {
					u += temp2;
					hashTable.insert(Token(TokenType::OPERATOR, u));
				}
				else {
					hashTable.insert(Token(TokenType::SEPARATORS, u));
				}
			}
			else if (temp == ' ') {
				getNextToken(alphabet, str, f, c);
			}
			else if (temp == '\n') {
				getNextToken(alphabet, str, f, c);
			}
			else if (temp == '+' || temp == '-' || temp == '=' || temp=='>') {
				getNextToken(alphabet, str, f, c);
				string o = "";
				o += temp;
				hashTable.insert(Token(TokenType::OPERATOR, o));
			}
			else if (temp == '<') {
				char temp2;
				cin.get(temp2);
				getNextToken(alphabet, str, f, c);
				string o = "";
				o += temp;
				if (temp2 == '>') {
					o += temp2;
					hashTable.insert(Token(TokenType::OPERATOR, o));
				}
				else if (temp2 == '\n' || temp2==' ') {
					hashTable.insert(Token(TokenType::OPERATOR, o));
				}
				else if (temp2 != '>' && temp2 != '\n' && temp2!=' ') {
					o += '>';
					hashTable.insert(Token(TokenType::OPERATOR, o));
					string o2 = "";
					if (temp2 == '+' || temp2 == '-' || temp2 == '=') {
						o2 += temp2;
						hashTable.insert(Token(TokenType::OPERATOR, o2));
					}
					else if (temp2 == ',' || temp2 == '(' || temp2 == ')') {
						o2 += temp2;
						hashTable.insert(Token(TokenType::SEPARATORS, o2));
					}
					else if (temp2 == '1' || temp2 == '2' || temp2 == '3' || temp2 == '4' || temp2 == '5' || temp2 == '6' || temp2 == '7' || temp2 == '8' || temp2 == '9' || temp2 == '0') {
						o2 += temp2;
						hashTable.insert(Token(TokenType::CONST, o2));
					}
					else if ((temp2 >='a' && temp2 <= 'z') || (temp2 >= 'A' && temp2 <= 'Z')) {
						o2 += temp2;
						char temp3;
						cin.get(temp3);
						while ((temp3 >= 'a' && temp3 <= 'z') || (temp3 >= 'A' && temp3 <= 'Z')) {
							o2 += temp3;
							cin.get(temp3);
						}
						hashTable.insert(Token(TokenType::ID, o2));
					}
				}
			}
			else if (temp == '"' || f == 1) {
				if (temp == '"') {
					c += 1;
				}
				f = 1;
				str += temp;
			}
			else if (!IsValidChar(temp, alp)) {
				getNextToken(alphabet, str, f, c);
				string e = "";
				e += temp;
				hashTable.insert(Token(TokenType::ERROR, e));
			}
			else {
				str += temp;
			}
		}
		if (!str.empty()) {
			getNextToken(alphabet, str, f, c);
		}
	}
	HashTable getHashTable()
	{
		return this->hashTable;
	}
};