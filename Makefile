all: clean testHeap

heap:
	gcc main.c binary_tree.c -o heap.out

testHeap: heap
	echo "" > result.txt
	echo "# Test 1:\n" >> result.txt
	cat test/heap1.in | ./heap.out >> result.txt
	echo "\n# Test 2:\n" >> result.txt
	cat test/heap2.in | ./heap.out >> result.txt
	echo "\n# Test 3:\n" >> result.txt
	cat test/heap3.in | ./heap.out >> result.txt
	echo "\n# Test 4:\n" >> result.txt
	cat test/heap4.in | ./heap.out >> result.txt
	echo "\n# Test 5:\n" >> result.txt
	cat test/heap5.in | ./heap.out >> result.txt
	echo "\n# Test 6:\n" >> result.txt
	cat test/heap6.in | ./heap.out >> result.txt
	echo "\n# Test 7:\n" >> result.txt
	cat test/heap7.in | ./heap.out >> result.txt
	echo "\n# Test 8:\n" >> result.txt
	cat test/heap8.in | ./heap.out >> result.txt
	cat result.txt
	diff -bB -I '#.*' test/expected.txt result.txt
clean:
	-rm *.out result*.txt *.exe heap
