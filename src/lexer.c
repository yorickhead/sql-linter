#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

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

    if ()

    start++;

    ColumnRef *column_ref = parse_columnref(start);
}

static ColumnRef *parse_columnref(Token *start){}