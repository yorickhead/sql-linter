#include "lexer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

static bool match_token(Token *tkn, char *str) {
  if (tkn == NULL) {
    return false;
  }

  char *token_str = calloc(tkn->len + 1, sizeof(char));
  strncpy(tkn->start, token_str, tkn->len);

  token_str[tkn->len + 1] = '\0';

  bool res = false;

  if (strcmp(token_str, str) == 0) {
    res = true;
  } else {
    res = false;
  }

  free(token_str);

  return res;
}

static char *str_from_token(Token *tkn) {
  if (tkn == NULL) {
    return false;
  }

  char *token_str = calloc(tkn->len + 1, sizeof(char));
  strncpy(tkn->start, token_str, tkn->len);

  return token_str;
}

static bool *column_has_alias(Token *pos, int *index) {
  Token *p = pos;

  while (pos->type != COMMA && !match_token(pos, "FROM") &&
         !match_token(p, "from")) {

    if (match_token(p, "as") || match_token(p, "AS")) {
      *index = p - pos;

      return true;
    }

    p++;
  }

  *index = 0;

  return false;
}

static SelectStmt *create_select_stmt() {
  SelectStmt *stmt = malloc(sizeof(SelectStmt));
  if (stmt == NULL) {
    fprintf(stderr, "failed allocate memory for select statement");

    return NULL;
  }

  stmt->base.type = NODE_SELECT_STMT;

  return stmt;
}

static SelectStmt *parse_select_stmt(Token **pos) {
  Token *p = *pos;

  SelectStmt *stmt = create_select_stmt();
  if (stmt == NULL) {
    return NULL;
  }

  if (!match_token(p, "select")) {
    fprintf(stderr, "start token is not select");

    return NULL;
  }

  p++;

  size_t column_count = 0;

  while (!match_token(p, "FROM") && !match_token(p, "from")) {
    int index;

    if (column_has_alias(p, &index)) {
      parse_alias(&p, index);
    } else {
      ColumnRef *column_ref = parse_columnref(&p);
      if (column_ref == NULL) {
        return NULL;
      }
    }

    column_count++;
  }

  
}

static FromClause *create_fromclause() {
  FromClause *fc = malloc(sizeof(FromClause));
  if (!fc) {
    fprintf(stderr, "failed allocate memory for from clause");

    return NULL;
  }

  fc->base.type = NODE_FROM_CLAUSE;

  return fc;
}

static FromClause *parse_fromclause(Token **start) {
  FromClause *fc = create_fromclause();
  if (fc == NULL) {
    return NULL;
  }

  TableRef *tableref = parse_table_ref(Token **start)

}

static ColumnRef *create_columnref() {
  ColumnRef *cr = malloc(sizeof(ColumnRef));
  if (!cr) {
    fprintf(stderr, "failed allocate memory for column ref");

    return NULL;
  }

  cr->base.type = NODE_COLUMN_REF;

  return cr;
}

static ColumnRef *parse_columnref(Token **pos) {
  Token *p = *pos;

  ColumnRef *columnref = create_columnref();
  if (!columnref) {
    return NULL;
  }

  if (p->type != STRING) {
    fprintf(stderr, "columnref start type is not string");

    return NULL;
  }

  columnref->table = str_from_token(p);

  p++;

  if (p->type != DOTE) {
    fprintf(stderr, "columnref separator is not dote");

    return NULL;
  }

  p++;

  if (p->type != STRING) {
    fprintf(stderr, "columnref end type is not string");

    return NULL;
  }

  columnref->column = str_from_token(p);

  return columnref;
}

static Alias *create_alias() {
  Alias *alias = malloc(sizeof(Alias));
  if (!alias) {
    fprintf(stderr, "failed allocate memory for alias");

    return NULL;
  }

  alias->base.type = NODE_ALIAS;

  return alias;
}

static Alias *parse_alias(Token **pos, int as_token_index) {
  Token *p = *pos;

  Alias *alias = create_alias();
  if (alias == NULL) {
    return NULL;
  }

  Token *expr_start = p;


}