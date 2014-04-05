#!/usr/bin/env sh
# Experiment A: Measure performance of PostgreSQL's hash join as X is varied

### load data into R and S
# sh ./loaddata.sh 100000 10

### Run query Q1 for different values of selection constant X
for i in 50000/2 
do
psql -e -v x=$i assign2 <<EOF
	SET enable_nestloop TO FALSE;
	SET enable_mergejoin TO FALSE;
	SET work_mem TO 64; 
	SET hash_method TO 2;
	SET bitvector_size TO 512;
	-- measure query running time
	\timing on
	SELECT COUNT(*) FROM R, S WHERE R.A = S.A AND R.B <= :x;
	\timing off
	-- examine query plan
	EXPLAIN ANALYZE SELECT COUNT(*) FROM R, S WHERE R.A = S.A AND R.B <= :x;
	\q
EOF
done


