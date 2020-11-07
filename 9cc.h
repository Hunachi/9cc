#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

// トークンの種類
typedef enum
{
    TK_RESERVED, // 記号
    TK_NUM,      // 整数トークン
    TK_EOF,      // 入力の終わりを表すトークン
} TokenKind;

// トークン
typedef struct Token Token;
struct Token
{
    TokenKind kind; // トークンの型
    Token *next;    // 次以降のトークン
    int val;        // kindがTK_NUM(整数トークン)の場合、その数値
    char *str;      // トークン文字列
    int len;        //トークンの長さ
};

// 抽象構文木のノードの種類
typedef enum
{
    ND_ADD, // +
    ND_SUB, // -
    ND_MUL, // *
    ND_DIV, // /
    ND_EQ,  // ==
    ND_NE,  // !=
    ND_LT,  // <
    ND_LE,  // <=
    ND_NUM  // 整数(Integer)
} NodeKind;

// 抽象構文木のノードの型
typedef struct Node Node;
struct Node
{
    NodeKind kind; // ノードの型
    Node *lhs;     // 左辺
    Node *rhs;     // 右辺
    int val;       // kindがND_NUMの場合にのみ使う
    char *str;     // トークンの文字列
    int len;       // トークンの長さ
};

// 今みているトークン
extern Token *token;

// 入力プログラム
extern char *user_input;

// ----- util.c -----
// エラーを報告するための関数
// printfと同じ引数を取る
void error(char *fmt, ...);

// ----- parce.c -----
// 入力文字列pをトークナイズしてそれを返す
Token *tokenize(char *p);
// 構文解析をしてNode型を返す
Node *expr();

// ----- codegen.c -----
// アセンブリを生成する
void gen(Node *node);

