#!/usr/bin/env sh
# Experiment B: Measure performance of PostgreSQL's hash join as work_mem is varied

### load data into R and S
# sh ./loaddata.sh 100000 10

### Run query Q1 for different values of work_mem
for i in 128 256 512 1024 2048 4096 
do
psql -e -v wm=$i assign2 <<EOF
	SET enable_nestloop TO FALSE;
	SET enable_mergejoin TO FALSE;
	SET work_mem TO 64; 
    SET bitvector_size to :wm;
    SET hash_method to 1;
	-- measure query running time
	\timing on
	SELECT COUNT(*) FROM S WHERE EXISTS (SELECT * FROM R WHERE R.A = S.A AND R.B <= 50000);
	\timing off
	-- examine query plan
	EXPLAIN ANALYZE SELECT COUNT(*) FROM S WHERE EXISTS (SELECT * FROM R WHERE R.A = S.A AND R.B <= 50000);  
	\q
EOF
done


