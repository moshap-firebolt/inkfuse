-- Decimals are turned into DOUBLE PRECISION
-- Any VARCHARs/CHARs (apart from char(1)) are turned into TEXT
-- Removed Primary key so other system's can't use B-Trees.
-- InkFuse always does full scans.
create table customer (
   c_custkey integer not null,
   c_name text not null,
   c_address text not null,
   c_nationkey integer not null,
   c_phone text not null,
   c_acctbal double precision not null,
   c_mktsegment text not null,
   c_comment text not null
   -- primary key (c_custkey)
);

create table orders (
   o_orderkey integer not null,
   o_custkey integer not null,
   o_orderstatus char(1) not null,
   o_totalprice double precision not null,
   o_orderdate date not null,
   o_orderpriority text not null,
   o_clerk text not null,
   o_shippriority integer not null,
   o_comment text not null
   -- primary key (o_orderkey)
);

create table lineitem (
   l_orderkey integer not null,
   l_partkey integer not null,
   l_suppkey integer not null,
   l_linenumber integer not null,
   l_quantity double precision not null,
   l_extendedprice double precision not null,
   l_discount double precision not null,
   l_tax double precision not null,
   l_returnflag char(1) not null,
   l_linestatus char(1) not null,
   l_shipdate date not null,
   l_commitdate date not null,
   l_receiptdate date not null,
   l_shipinstruct text not null,
   l_shipmode text not null,
   l_comment text not null
   -- primary key (l_orderkey,l_linenumber)
);

create table part (
  p_partkey integer not null,
  p_name varchar(55) not null,
  p_mfgr char(25) not null,
  p_brand char(10) not null,
  p_type varchar(25) not null,
  p_size integer not null,
  p_container char(10) not null,
  p_retailprice decimal(12,2) not null,
  p_comment varchar(23) not null
  -- primary key (p_partkey)
);
