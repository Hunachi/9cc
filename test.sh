#!/bin/bash
assert() {
  expected="$1"
  input="$2"

  ./9cc "$input" > tmp.s
  cc -o tmp tmp.s
  ./tmp
  actual="$?"

  if [ "$actual" = "$expected" ]; then
    echo "$input => $actual"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}

assert 0 "0;"
assert 42 "42;"
assert 21 "5+20-4;"
assert 27 "28-2+1;"
assert 41 " 12 + 34 - 5;"
assert 47 '5+6*7;'
assert 15 '5*(9-6);'
assert 4 '(3+5)/2;'
assert 26 '+1-5*-5;'

assert 0 "0==1;"
assert 1 "22==22;"
assert 0 "(+10+12) != 22;"
assert 1 "2 != 54;"

assert 0 "0>3;"
assert 1 "(10-3)>2;"
assert 0 "2>=(15-11);"
assert 1 "(10-5+1)>=5+1;"
assert 0 "2<(15-13);"
assert 1 "(10-5+1)<7+2;"
assert 0 "2<=(15-14);"
assert 1 "(10-5+1)<=5+1;"
assert 3 "a=(1+2);"

echo OK