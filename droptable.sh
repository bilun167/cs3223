
psql assign1 <<END
DROP TABLE IF EXISTS pgbench_history;
DROP TABLE IF EXISTS pgbench_tellers;
DROP TABLE IF EXISTS pgbench_accounts;
DROP TABLE IF EXISTS pgbench_branches;
\q
END
