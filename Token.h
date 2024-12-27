#ifndef TOKEN_H
#define TOKEN_H
#include <string>

using namespace std;

enum class TokenType {
    FUNCTION, //MAIN
    ID, //VAR
    CONST, //NUM
    KEYWORD, //INT
    SEPARATORS,//( ) , .
    ERROR,
    TYPE, //
    OPERATOR,//+ - =
};

class Token {
public:
    TokenType type;
    string value;

    Token() {}
    Token(TokenType t, const string& v) : type(t), value(v) {}
    string getLexem() const {
        return value;
    }

    string getLexemType() const {
        return tokenTypeToString(type);
    }

    void setLexemName(const string& newName) {
        value = newName;
    }

    void setLexemType(TokenType newType) {
        type = newType;
    }

private:
    string tokenTypeToString(TokenType t) const {
        switch (t) {
        case TokenType::FUNCTION: return "FUNCTION";
        case TokenType::ID: return "ID";
        case TokenType::CONST: return "CONST";
        case TokenType::KEYWORD: return "KEYWORD";
        case TokenType::SEPARATORS: return "SEPARATORS";
        case TokenType::ERROR: return "ERROR";
        case TokenType::TYPE: return "TYPE";
        case TokenType::OPERATOR: return "OPERATOR";
        default: return "UNKNOWN";
        }
    }
};

#endif