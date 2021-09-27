#!/bin/bash
outloop=$1
inloop=$2

echo "===== glibc start ======"
for i in {1..15}
do
	./main-glibc ${i} ${outloop} ${inloop}
done
echo "===== glibc end ======"
sleep 3

echo "===== tcmalloc start ======"
for i in {1..15}
do
	./main-tcmalloc ${i} ${outloop} ${inloop}
done
echo "===== tcmalloc end ======"
sleep 3

echo "===== jemalloc start ======"
for i in {1..15}
do
	./main-jemalloc ${i} ${outloop} ${inloop}
done
echo "===== jemalloc end ======"