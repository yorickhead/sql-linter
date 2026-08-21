#include <stddef.h>

enum TokenType {
  LBRACE,         // "("
  RBRACE,         // ")"
  COMMA,          // ","
  DOTE,           // "."
  SEMICOLON,      // ";"
  GREATER,        // ">"
  LESS,           // "<"
  EQUAL,          // "="
  QUOTATION_MARK, // "'"
  ASTERISK,       // "*"
  STRING,
  NUMBER,

  UNKNOWN,
  EOF_TOKEN
};

typedef struct Token {
  enum TokenType type;
  char *start;
  size_t len;
} Token;

Token *tokenize(char *data);
