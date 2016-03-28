#!/bin/sh
ptmin=$1
ptmax=$2
star-submit-template -template RunPythia500GeVJetProduction.xml -entities ptmin=$ptmin,ptmax=$ptmax 

