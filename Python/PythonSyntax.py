from datetime import datetime
import math

# Datetime

now = datetime.now()
print('%s/%s/%s %s:%s:%s' % (now.month, now.day, now.year, now.month, now.day, now.year))

# String

print(ord('A'), chr(66), '\u4e2d\u6587')  # 65, B, '中文'
x = b'ABC'  # each char occupies only 1 byte instead of unicode
print('ABC'.encode('ascii'))  # b'ABC'
print('中文'.encode('utf-8'))  # b'\xe4\xb8\xad\xe6\x96\x87'
b'\xe4\xb8\xad\xe6\x96\x87'.decode('utf-8')
print(len('中文'), len('中文'.encode('utf-8')))  # 2, 6
print('Hi, %s, you have $%d.%2d-%02d %.2f %%' % ('Michael', 1000000, 3, 1, 3.1415926))

a = 'abc'
b = a.replace('a', 'A')
print(a, b)

import re

re.split(r'[\s\,\;]+', 'a,b;; c  d')  # ['a', 'b', 'c', 'd']
m = re.match(r'^(\d{3})-(\d{3,8})$', '010-12345')
m.group(0)  # '010-12345'
m.group(1)  # '010'
m.group(2)  # '12345'
re_telephone = re.compile(r'^(\d{3})-(\d{3,8})$')
re_telephone.match('010-12345').groups()

# List

classmates = ['Michael', 'Bob', 'Tracy']
print(len(classmates))  # 3
print(classmates[-1])  # 'Tracy'
classmates.append('Adam')  # ['Michael', 'Bob', 'Tracy', 'Adam']
classmates.insert(1, 'Jack')  # ['Michael', 'Jack', 'Bob', 'Tracy', 'Adam']
classmates.pop()  # 'Adam'
classmates.sort()  # ['Bob', 'Jack', 'Michael', 'Tracy']
s = ['Apple', 123, True, 'python', 'java', ['asp', 'php'], 'scheme']
print(classmates)

# Advanced - Split
L = ['Michael', 'Sarah', 'Tracy', 'Bob', 'Jack']
print(L[:3])  # L[0:3] = ['Michael', 'Sarah', 'Tracy']
print(L[-2:])  # ['Bob', 'Jack']
print(L[-2:-1])  # ['Bob']

# Advanced - Generation
print([x * x for x in range(1, 11) if x % 2 == 0])  # [4, 16, 36, 64, 100]
print([m + n for m in 'ABC' for n in 'XYZ'])  # ['AX', 'AY', 'AZ', 'BX', 'BY', 'BZ', 'CX', 'CY', 'CZ']
print([s.lower() for s in L])  # ['hello', 'world', 'ibm', 'apple']
L2 = [s.lower() for s in L if isinstance(s, str)]  # lower case ['Hello', 'World', 18, 'Apple', None]

# Tuple: Tuple is fixed and const list.
classmates = ('Michael', 'Bob', 'Tracy')
t = (1,)  # a tuple with only one element

# Generator: Generator is a list with pre-computed space
g = (x * x for x in range(10))  # <generator object


# Generator can be defined using yield and function:
def fib(max):
    n, a, b = 0, 0, 1
    while n < max:
        yield b
        a, b = b, a + b
        n = n + 1
    return 'done'


for n in fib(6):
    print(n)

# Using exception to catch the return value of generator
g = fib(6)
while True:
    try:
        x = next(g)
        print('g:', x)
    except StopIteration as e:
        print('Generator return value:', e.value)
        break

# Dict: dict is the (hash) map in C++, which finds and insert in O(1), but occupies lots of memory
d = {'Michael': 95, 'Bob': 75, 'Tracy': 85}
print(d['Michael'])  # 95
print('Thomas' in d)  # False
d.get('Thomas', -1)  # -1, None if no parameter
d.pop('Bob')
keys = ['a', 'b', 'c']
vals = [1, 2, 3]
zipped = dict(zip(keys, vals))

# Set: Set is a set of keys without values:
s1 = {1, 2, 3}
s2 = {2, 3, 4}
s1.add(4)
s1.remove(4)
print(s1 & s2)  # {2, 3}
print(s1 | s2)  # {1, 2, 3, 4}

# collections
from collections import namedtuple

## namedtuple
Point = namedtuple('Point', ['x', 'y'])
p = Point(1, 2)
Circle = namedtuple('Circle', ['x', 'y', 'r'])

# double linked list
from collections import deque

q = deque()
q.append('x')
q.appendleft('y')

from collections import defaultdict

# defaultdict
dd = defaultdict(lambda: 'N/A')

from collections import OrderedDict

od = OrderedDict([('a', 1), ('b', 2), ('c', 3)])

from collections import Counter

c = Counter()  # subclass of dict
for ch in 'programming':
    c[ch] = c[ch] + 1
c  # Counter({'g': 2, 'm': 2, 'r': 2, 'a': 1, 'i': 1, 'o': 1, 'n': 1, 'p': 1})


# Functional Programming
## High-order function
def add(x, y, f):
    return f(x) + f(y)


add(-5, 6, abs)


## map/reduce
# https://ai.google/research/pubs/pub62
def sqr(x):
    return x * x


r = map(sqr, [1, -2, 3, 4, -5, 6, -7, 8, 9])  # Iterator, a lazy list
list(r)

# reduce(f, [x1, x2, x3, x4]) = f(f(f(x1, x2), x3), x4)
from functools import reduce


def add(x, y):
    return x + y


reduce(add, [1, 3, 5, 7, 9])  # 13579


def str2int(s):
    def fn(x, y):
        return x * 10 + y

    def char2num(s):
        return {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}[s]

    return reduce(fn, map(char2num, s))


# lambda function

def str2int2(s):
    def char2num(s):
        return {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}[s]

    return reduce(lambda x, y: x * 10 + y, map(char2num, s))


# filter
# Filter acts like map, but removes the element depending on the return value, True or False.

def is_odd(n):
    return n % 2 == 1

print(list(filter(is_odd, [1, 2, 4, 5, 6, 9, 10, 15])))  # [1, 5, 9, 15]


def not_empty(s):
    return s and s.strip()


print(list(filter(not_empty, ['A', 'B', None, 'C', ' ']))) # ['A', 'B', 'C']

# Anonymous function
list(map(lambda x: x * x, [1, 2, 3, 4, 5, 6, 7, 8, 9]))
def build(x, y):
    return lambda: x * x + y * y

# Partial function
def int2(x, base=2):
    return int(x, base)


import functools

int2 = functools.partial(int, base=2)


def log(text):
    def decorator(func):
        def wrapper(*args, **kw):
            print('%s %s():' % (text, func.__name__))
            return func(*args, **kw)

        return wrapper

    return decorator

# Object Oriented Programming

class Student(object):
    __slots__ = ('name', 'age', 'score')  # use tuple to defined the allowed properties

    def __init__(self, name, score):
        self.name = name
        self.score = score  # _Student__score

    def print_score(self):
        print('%s: %s' % (self.name, self.score))


bart = Student('Bart Simpson', 59)
bart.print_score()
isinstance(bart, Student)
type(123)  # int
isinstance([1, 2, 3], (list, tuple))
dir('ABC')  # list all the methods and properties of a variable


# Inherit

class Animal(object):
    pass


# first level:
class Mammal(Animal):
    pass


class Bird(Animal):
    pass


# next level:
class Dog(Mammal):
    pass


class Bat(Mammal):
    pass


class Parrot(Bird):
    pass


class Ostrich(Bird):
    pass


# Enum
from enum import Enum

Month = Enum('Month', ('Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'))

for name, member in Month.__members__.items():
    print(name, '=>', member, ',', member.value)

from enum import Enum, unique


@unique
class Weekday(Enum):
    Sun = 0
    Mon = 1
    Tue = 2
    Wed = 3
    Thu = 4
    Fri = 5
    Sat = 6


for name, member in Weekday.__members__.items():
    print(name, '=>', member)



# Debug
try:
   print('try...')
   r = 10 / int('2')
   print('result:', r)
except ValueError as e:
   print('ValueError:', e)
except ZeroDivisionError as e:
   print('ZeroDivisionError:', e)
else:
   print('no error!')
finally:
   print('finally...')
print('END')


assert x != 0, 'n is zero!'


import unittest
# if __name__ == '__main__':
#     unittest.main()
class TestDict(unittest.TestCase):
   def test_init(self):
       d = dict(a=1, b='test')
       self.assertEqual(d.a, 1)
       self.assertEqual(d.b, 'test')
       self.assertTrue(isinstance(d, dict))

