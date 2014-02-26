OUTPUTDIR=lru-solution

mkdir -p ${OUTPUTDIR}

\rm -f testcase.c

for testcase in $( ls testcases/testcase*.c ); do
    echo $testcase
    cp $testcase testcase.c
    make buftest
    ./buftest > ${OUTPUTDIR}/${testcase#testcases/}.soln
    rm -f *.o
    rm buftest
done

\rm -f testcase.c
