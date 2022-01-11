#!/bin/bash
## To run in parallel, do:
## time ./analysis.sh HAnalysis 1

## To run in serial mode, do:
## time ./analysis.sh HAnalysis 0

## get possible error after test execution
analysis=$1
parallel=$2

## Implement validation of input parameters
## TO BE DONE

## execute and run ROOT
date
echo "starting ROOT"
##
root -l -b << EOF
.L $analysis.C
$analysis($parallel)
EOF
##
echo "end of ROOT execution"
date
