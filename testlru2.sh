OUTPUTDIR=lru2-solution

mkdir -p ${OUTPUTDIR}

\rm -f testcase.c

for testcase in $( ls testcases/testcase*.c ); do
    echo $testcase
    cp $testcase testcase.c
    make buftest2
    ./buftest2 > ${OUTPUTDIR}/${testcase#testcases/}.soln
    rm -f *.o
    rm buftest2
done

\rm -f testcase.c
