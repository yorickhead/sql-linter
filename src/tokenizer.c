#include "tokenizer.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

static int get_token_count_in_str(const char **start) {
  const char *p = *start;

  int sigh_count = 0;
  int quoation_mark_count = 0;

  while (*p != ' ') {
    if (*p == ',' || *p == '.' || *p == '<' || *p == '>') {
      sigh_count++;
    } else if (*p == '\'') {
      quoation_mark_count++;
    }

    p++;
  }

  p++;

  *start = p;

  if (sigh_count + quoation_mark_count == 0) {
    return 1;
  }

  if (quoation_mark_count == 0) {
    return (sigh_count * 2) + 2;
  }

  return (sigh_count * 2) + ((quoation_mark_count / 2) * 3) + 2;
}

static int get_token_count(const char *data) {
  if (data == NULL) {
    return 0;
  }

  int number = 0;

  const char *p = data;

  while (p != NULL) {
    int number_in_str = get_token_count_in_str(&p);
    if (number_in_str == 0) {
      break;
    }

    number += number_in_str;

    p++;
  }

  return number;
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
  
    exit(1);
  }
}

Token *tokenize(const char *data) {}
