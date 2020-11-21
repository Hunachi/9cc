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
    TK_IDENT,    // 識別子
    TK_EOF,      // 入力の終わりを表すトークン
    TK_RETURN    // リターン
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
    ND_ADD,    // +
    ND_SUB,    // -
    ND_MUL,    // *
    ND_DIV,    // /
    ND_ASSIGN, // =(代入)
    ND_EQ,     // ==
    ND_NE,     // !=
    ND_LT,     // <
    ND_LE,     // <=
    ND_LVAR,   // ローカル変数
    ND_NUM,    // 整数(Integer)
    ND_RETURN  // return
} NodeKind;

// ローカル変数の型
typedef struct LVar LVar;
struct LVar {
  LVar *next; // 次の変数かNULL
  char *name; // 変数の名前
  int len;    // 名前の長さ
  int offset; // RBPからのオフセット
};

// 抽象構文木のノードの型
typedef struct Node Node;
struct Node
{
    NodeKind kind; // ノードの型
    Node *lhs;     // 左辺
    Node *rhs;     // 右辺
    int val;       // kindがND_NUMの場合にのみ使う
    int offset;    // kindがND_LVARの場合のみ使う
    char *str;     // トークンの文字列
    int len;       // トークンの長さ
};

// 今みているトークン
extern Token *token;

// 入力プログラム
extern char *user_input;

// 構文解析済プログラム
extern Node *code[100];

// ローカル変数
extern LVar *locals;

// ----- util.c -----
// エラーを報告するための関数
// printfと同じ引数を取る
void error(char *fmt, ...);

// ----- parce.c -----
// 入力文字列 user_input をトークナイズしてそれを返す
Token *tokenize();
// 構文解析をする
void program();

// ----- codegen.c -----
// アセンブリを生成する
void gen(Node *node);
