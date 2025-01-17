#!/bin/bash

if [[ $# < 1 ]]; then
  echo "Run as ./generate_tpch.sh <scale factor> <system={duckdb|hyper|inkfuse|umbra}>"
  exit 1
fi

# Clone TPC-H dbgen tool
git clone https://github.com/electrum/tpch-dbgen.git
cd tpch-dbgen
# Build it
make
# Generate data
./dbgen -s $1
# Move over .tbl files into separate directory
cd -
mkdir -p data
mv -f tpch-dbgen/*.tbl data
# Drop tpch-dbgen again
rm -rf tpch-dbgen

# Normalize data for system ingest
if [[ $# -ge 2 ]]; then
  if [[ $2 == "duckdb" ]]; then
    echo "Cleaning up .tbl for DuckDB"
    # Remove trailing '|' which make this invalid CSV
    sed -i 's/.$//' data/*.tbl
  fi
  if [[ $2 == "umbra" ]]; then
    echo "Cleaning up .tbl for Umbra"
    # Remove trailing '|' which make this invalid CSV
    sed -i 's/.$//' data/*.tbl
  fi
  if [[ $2 == "hyper" ]]; then
    echo "Cleaning up .tbl for Hyper"
    # Remove trailing '|' which make this invalid CSV
    sed -i 's/.$//' data/*.tbl
  fi
fi
