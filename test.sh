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

assert 5 "ho=0;for(i=0;i<5;i=i+1)ho=ho+1;return ho;"
assert 11 "ho=1;for(i=0;i<5;i=i+1)ho=ho+i;return ho;"

assert 5 "i=1;while(i<5)i=i+1;return i;"

assert 5 "if(0 == 1) return 3; else return 5;"

assert 6 "aa=3;aa+3;"
assert 3 "aa=3;"
assert 4 "a=3;b=3;if(a == b) return (b+1);"
assert 3 "a=2;b=1;a+b;"
assert 3 "aa=2;b=1;aa+b;"
assert 4 "a=3;a1=3;a1+1;"
assert 4 "aa=3;bbb=3;if(aa == bbb) return (bbb+1);"
assert 3 "if(1 != 0) return 3;"

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
assert 1 "a=1;"
assert 3 "aa=(1+2);"
assert 0 "aaaa=2*(2+3);dd=5-1;aaaa==dd;"
assert 1 "abc=3;bcd=2;abc>bcd;"
assert 0 "a=2*(2+3);d=5-1;a==d;"
assert 0 "aa=3;bb=2;aa<bb;"
assert 1 "a=3;b=2;a>b;"
assert 3 "a=3;b=2;a>b;return a;"
assert 2 "return (1+1);"
assert 10 "return 10;"

echo OK