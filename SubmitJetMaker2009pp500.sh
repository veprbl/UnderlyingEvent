#!/bin/sh

for runnumber in `cat final_runnumber326.list` ; do
	dir=/gpfs01/star/i_bnl/gdwebb/Run9/500GeVJets/Data/$runnumber
	[ -d $dir ] || mkdir -p $dir/{log,err}
	star-submit-template -template Run500GeVJetProduction.xml -entities runnumber=$runnumber
done
