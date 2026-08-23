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
  tkn.start = p;
  tkn.len = 0;

  if (*p == '\0') {
    tkn.type = EOF_TOKEN;
    return tkn;
  }

  if (isalpha(*p)) {
    tkn = get_token_from_str(&p);
    *pos = p;
    return tkn;
  }

  if (isdigit(*p)) {
    tkn = get_token_from_count(&p);
    *pos = p;
    return tkn;
  }

  switch (*p) {
  case '(':
    tkn.type = LBRACE;
    break;
  case ')':
    tkn.type = RBRACE;
    break;
  case ',':
    tkn.type = COMMA;
    break;
  case ';':
    tkn.type = SEMICOLON;
    break;
  case '>':
    tkn.type = GREATER;
    break;
  case '<':
    tkn.type = LESS;
    break;
  case '.':
    tkn.type = DOTE;
    break;
  case '=':
    tkn.type = EQUAL;
    break;
  case '\'':
    tkn.type = QUOTATION_MARK;
    break;
  case '*':
    tkn.type = ASTERISK;
    break;
  default:
    fprintf(stderr, "unknown symbol: %c\n", *p);
    tkn.type = UNKNOWN;
    *pos = p + 1;
    return tkn;
  }

  tkn.len = 1;
  *pos = p + 1;
  return tkn;
}

Token *tokenize(char *data) {
  int token_number = get_token_count(data);

  Token *start = calloc(token_number + 1, sizeof(Token));
  if (!start) {
    fprintf(stderr, "failed allocate memory for tokens");
    return NULL;
  }

  Token *position = start;
  char *p = data;

  while (1) {
    Token tkn = get_next_token(&p);

    if (tkn.type == EOF_TOKEN) {
      *position = tkn;
      break;
    }

    if (tkn.type == UNKNOWN) {
      fprintf(stderr, "Unknown token near position %zu\n", (size_t)(p - data));
      free(start);
      return NULL;
    }

    *position++ = tkn;

    if (position - start >= token_number) {
      fprintf(stderr, "Too many tokens (max %d)\n", token_number);
      free(start);
      return NULL;
    }
  }

  return start;
}
