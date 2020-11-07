
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

// エラーを報告するための関数
// printfと同じ引数を取る
void error(char *fmt, ...);

// エラー箇所を報告する.
void error_at(char *loc, char *fmt, ...);

// 次のトークンが期待している記号のときには、
// トークンを1つ読み進めて真を返す。
// それ以外の場合には偽を返す。
bool consume(char *op);

// 次のトークンが期待している 記号 の場合トークンを1つ読み進め，
// それ以外の場合にはエラーになる
void expect(char *op);

// 次のトークンが 数値 の場合トークンを1つ読み進めてその数値を返す．
// それ以外の場合にはエラーになる
int expect_number();

// 新しいトークンを作成して cur につなげる
Token *new_token(TokenKind kind, Token *cur, char *str, int len);

bool startswith(char *p, char *q);

// 入力文字列pをトークナイズしてそれを返す
Token *tokenize(char *p);

// ノードの型だけ指定されたノードを作る
Node *new_node(NodeKind kind);

// 数値用のノードを作る
Node *new_node_num(int val);

// 2項演算子用
Node *new_node_binary(NodeKind kind, Node *lhs, Node *rhs);

// 構文解析用の関数
// expr = equality
Node *expr();
// equality  = relational ("==" relational | "!=" relational)*
Node *equality();
// relational = add ("<" add | "<=" add | ">" add | ">=" add)*
Node *relational();
// add = mul ("+" mul | "-" mul)*
Node *add();
// mul = primary ("*" primary | "/" primary)*
Node *mul();
// unary   = ("+" | "-")? primary
Node *unary();
// primary = num | "(" expr ")"
Node *primary();

// アセンブリを生成する
void gen(Node *node);

