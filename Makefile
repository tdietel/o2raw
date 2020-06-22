
all: extract

# all: run_raw_analysis

.PHONY: run_raw_analysis

RAWROOTFILE=/Users/tom/alice/data/2018/LHC18r/000296934/raw/18000296934039.915.root

run_raw_analysis:

extract:
	mkdir -p data
	cd data ; echo aliroot -b -q -l 'dumpraw.C("$(RAWROOTFILE)")'
