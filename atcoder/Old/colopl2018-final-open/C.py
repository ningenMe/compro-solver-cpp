#!/usr/bin/env python3
import sys
read = sys.stdin.buffer.read
readline = sys.stdin.buffer.readline
readlines = sys.stdin.buffer.readlines

class deque:
    def __init__(self, src_arr=[], max_size=300000):
        self.N = max(max_size, len(src_arr)) + 1
        self.buf = list(src_arr) + [None] * (self.N - len(src_arr))
        self.head = 0
        self.tail = len(src_arr)
    def __index(self, i):
        l = len(self)
        if not -l <= i < l: raise IndexError('index out of range: ' + str(i))
        if i < 0:
            i += l
        return (self.head + i) % self.N
    def __extend(self):
        ex = self.N - 1
        self.buf[self.tail+1 : self.tail+1] = [None] * ex
        self.N = len(self.buf)
        if self.head > 0:
            self.head += ex
    def is_full(self):
        return len(self) >= self.N - 1
    def is_empty(self):
        return len(self) == 0
    def append(self, x):
        if self.is_full(): self.__extend()
        self.buf[self.tail] = x
        self.tail += 1
        self.tail %= self.N
    def appendleft(self, x):
        if self.is_full(): self.__extend()
        self.buf[(self.head - 1) % self.N] = x
        self.head -= 1
        self.head %= self.N
    def pop(self):
        if self.is_empty(): raise IndexError('pop() when buffer is empty')
        ret = self.buf[(self.tail - 1) % self.N]
        self.tail -= 1
        self.tail %= self.N
        return ret
    def popleft(self):
        if self.is_empty(): raise IndexError('popleft() when buffer is empty')
        ret = self.buf[self.head]
        self.head += 1
        self.head %= self.N
        return ret
    def __len__(self):
        return (self.tail - self.head) % self.N
    def __getitem__(self, key):
        return self.buf[self.__index(key)]
    def __setitem__(self, key, value):
        self.buf[self.__index(key)] = value
    def __str__(self):
        return 'Deque({0})'.format(str(list(self)))

class ConvexHullTrick:
    def __init__(self,unit):
        self.lines = deque()
        self.comp = self.comp_min
        self.unit = unit

    def comp_min(self,l,r):
        return l<r

    def is_required(self,line1,line2,line3):
        return self.comp(
            (line2[1]-line3[1])*(line2[0]-line1[0]),(line1[1]-line2[1])*(line3[0]-line2[0])
        )
     
    def insert_back(self,line):
        lines = self.lines
        sz = len(lines)
        if sz > 0 and lines[sz-1][0] == line[0]:
            if self.comp(lines[sz-1][1],line[1]):
                return
            else :
                lines.pop()
        while len(lines) >= 2 and (not self.is_required(lines[len(lines)-2],lines[len(lines)-1],line)):
            lines.pop()
        lines.append(line)

    def insert_front(self,line):
        lines = self.lines
        sz = len(lines)
        if sz > 0 and lines[0][0] == line[0]:
            if self.comp(lines[0][1],line[1]):
                return
            else :
                lines.popleft()
        while True:
            if len(lines) < 2:
                break
            line1 = line
            line2 = lines[0]
            line3 = lines[1]
            if self.comp((line2[1]-line3[1])*(line2[0]-line1[0]),(line1[1]-line2[1])*(line3[0]-line2[0])):
                break
            lines.popleft()
        lines.appendleft(line)

    def insert(self,line):
        lines = self.lines
        if len(lines) == 0 or line[0] <= lines[0][0]:
            self.insert_front(line)
        elif lines[len(lines)-1][0] <= line[0]:
            self.insert_back(line)
 
    def get(self,x):
        lines = self.lines
        if len(lines) == 0:
            return self.unit
        ng = -1
        ok = len(lines) - 1
        while ok - ng > 1:
            md = (ok + ng) // 2
            if self.comp(lines[md][0]*x+lines[md][1],lines[md+1][0]*x+lines[md+1][1]):
                ok = md
            else:
                ng = md
        return lines[ok][0]*x+lines[ok][1]

def main():
    N = int(input())
    A = list(map(int,input().split()))
    cht = ConvexHullTrick(0)
    for i,x in enumerate(A):
        cht.insert_front((-2*i,x+i*i))
    ans = [cht.get(i)+i*i for i in range(N)]
    print('\n'.join(map(str,ans)))    

main()
