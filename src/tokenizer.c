#include "tokenizer.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int get_token_count(const char *data) {
  if (!data)
    return 0;

  int count = 0;
  const char *p = data;

  while (*p != '\0') {

    while (*p == ' ' || *p == '\t' || *p == '\n')
      p++;

    if (*p == '\0')
      break;

    if (*p == ',' || *p == '.' || *p == '<' || *p == '>') {
      count++;
      p++;
      continue;
    }

    if (*p == '\'') {
      p++;
      while (*p != '\0' && *p != '\'')
        p++;
      if (*p == '\'')
        p++;
      count++;
      continue;
    }

    while (*p != '\0' && *p != ' ' && *p != ',' && *p != '.' && *p != '<' &&
           *p != '>') {
      p++;
    }

    count++;
  }

  return count;
}

static Token get_token_from_str(char **pos) {
  char *p = *pos;
  char *start = p;

  int len = 1;

  while (isalpha(*pos)) {
    len++;

    p++;
  }

  Token tkn;

  tkn.len = len;
  tkn.type = STRING;
  tkn.start = start;

  *pos = p;

  return tkn;
}

static Token get_token_from_count(char **pos) {
  char *p = *pos;
  char *start = p;

  int len = 1;

  while (isdigit(*pos)) {
    len++;

    p++;
  }

  Token tkn;

  tkn.len = len;
  tkn.type = NUMBER;
  tkn.start = start;

  return tkn;
}

static Token get_next_token(char **pos) {
  char *p = *pos;

  while (*p && isspace(*p))
    p++;

  Token tkn;

  if (isalpha(*p)) {
    tkn = get_token_from_str(&p);

    *pos = p + 1;

    return tkn;
  }

  if (isdigit(*p)) {
    tkn = get_token_from_count(&p);

    *pos = p + 1;

    return tkn;
  }

  switch (*p) {
  case '(':
    tkn.type = LBRACE;
    tkn.len = 1;
    tkn.start = p;

    *pos = p + 1;

    return tkn;

  case ')':
    tkn.type = RBRACE;
    tkn.len = 1;
    tkn.start = p;

    *pos = p + 1;

    return tkn;
  case ',':
    tkn.type = COMMA;
    tkn.len = 1;
    tkn.start = p;

    *pos = p + 1;

    return tkn;

  case ';':
    tkn.type = SEMICOLON;
    tkn.len = 1;
    tkn.start = p;

    *pos = p + 1;

    return tkn;

  case '>':
    tkn.type = GREATER;
    tkn.len = 1;
    tkn.start = p;

    *pos = p + 1;

    return tkn;
  case '<':
    tkn.type = LESS;
    tkn.len = 1;
    tkn.start = p;

    *pos = p + 1;

    return tkn;
  case '=':
    tkn.type = EQUAL;
    tkn.len = 1;
    tkn.start = p;

    *pos = p + 1;

    return tkn;
  case '\'':
    tkn.type = QUOTATION_MARK;
    tkn.len = 1;
    tkn.start = p;

    *pos = p + 1;

    return tkn;
  case '*':
    tkn.type = ASTERISK;
    tkn.len = 1;
    tkn.start = p;

    *pos = p + 1;

    return tkn;
  default:
    fprintf(stderr, "unknown symbol: %c", *p);

    tkn.type = UNKNOWN;

    return tkn;
  }
}

Token *tokenize(char *data) {
  int token_number = get_token_count(data);

  Token *start = calloc(token_number, sizeof(Token));
  if (!start) {
    fprintf(stderr, "failed allocate memory for tokens");

    return NULL;
  }

  Token *position = start;
  Token tkn;

  char *p = data;

  while (*p != '\0') {
    tkn = get_next_token(&p);

    printf("new token with len: %zu\n", tkn.len);

    if (position - start >= token_number - 1) {
      fprintf(stderr, "Too many tokens (max %d)\n", token_number - 1);
      free(start);
      return NULL;
    }

    *position = tkn;
    position++;

    if (tkn.type == UNKNOWN) {
      fprintf(stderr, "Unknown token near position %zu\n", (size_t)(p - data));
      free(start);
      return NULL;
    }
  }

  tkn.type = EOF_TOKEN;
  tkn.len = 0;
  tkn.start = NULL;

  *position = tkn;

  return start;
}
