#include "lexer.h"
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool match_token(Token *tkn, char *str) {
    if (tkn == NULL) {
        return false;
    } 

    char *token_str = calloc(tkn->len+1, sizeof(char));
    strncpy(tkn->start, token_str, tkn->len);

    if (strcmp(token_str, str) == 0) {
        return true;
    } else {
        return false;
    }
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

static SelectStmt *parse_select_stmt(Token *start) {
    SelectStmt *stmt = create_select_stmt();
    if (stmt == NULL) {
        return NULL;
    }

    if (!match_token(start, "select")) {
        fprintf(stderr, "start token is not select");

        return NULL;
    }

    start++;

    ColumnRef *column_ref = parse_columnref(start);
}

static ColumnRef *parse_columnref(Token *start){}