#include "tokenizer.h"

typedef enum {
    NODE_SELECT_STMT,
    NODE_COLUMN_REF,
    NODE_FUNCTION_CALL,
    NODE_BINARY_EXPR,
    NODE_TABLE_REF,
    NODE_ALIAS,
    NODE_LITERAL,
    NODE_FROM_CLAUSE,
}NodeType;

typedef enum {
    B_EQUAL,
    B_GREATER,
    B_AND,
    B_LESS,
    B_OR
}BinaryOp;

typedef struct AstNode{
    NodeType type;
}AstNode;

typedef struct {
    AstNode base;
    AstNode **columns;
    size_t column_count;
    AstNode *from;
    AstNode *where;
    AstNode *group_by;
    AstNode *order_by;
    AstNode *limit;
} SelectStmt;

typedef struct {
    AstNode base;
    char *table;             // can be NULL
    char *column;
} ColumnRef;

typedef struct {
    AstNode base;
    char *func_name;         // "COUNT", "SUM"
    AstNode **args;
    size_t arg_count;
} FunctionCall;

typedef struct {
    AstNode base;
    AstNode *expr;
    char *alias;
}Alias;

typedef struct {
    AstNode base;
    AstNode *left;
    BinaryOp op;             // EQ, GT, AND, OR...
    AstNode *right;
} BinaryExpr;

typedef struct {
    AstNode base;
    char *name;
    char *alias;
} TableRef;

typedef enum{
    LIT_STRING,
    LIT_NUMBER
}LiteralType;

typedef struct{
    AstNode base;
    LiteralType type;
}Literal;

typedef struct{
    AstNode base;
    TableRef *table_ref;
}FromClause;

AstNode *get_ast(Token *tokens);

static SelectStmt *parse_select_stmt(Token **start);
static ColumnRef *parse_columnref(Token **start);
static FunctionCall *parse_function_call(Token **start);
static BinaryExpr *parse_binary_expr(Token **start);
static Alias *parse_alias(Token **start, int as_token_index);
static TableRef *parse_table_ref(Token **start);
static FromClause *parse_from_clause(Token **start);