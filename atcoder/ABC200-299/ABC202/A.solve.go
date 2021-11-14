package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

var sc = bufio.NewScanner(os.Stdin)

func main() {
	sc.Split(bufio.ScanWords)
	A, B, C := readInt(), readInt(), readInt()
	fmt.Println(21 - A - B - C)
}

func readInt() int {
	sc.Scan()
	ret, e := strconv.Atoi(sc.Text())
	if e != nil {
		panic(e)
	}
	return ret
}

func readString() string {
	sc.Scan()
	return sc.Text()
}
