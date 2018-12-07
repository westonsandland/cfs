OK = $(sort $(wildcard *.ok))
TESTS = $(patsubst %.ok,%,$(OK))
RAWS = $(patsubst %.ok,%.raw,$(OK))
OUTS = $(patsubst %.ok,%.out,$(OK))
DIFFS = $(patsubst %.ok,%.diff,$(OK))
RESULTS = $(patsubst %.ok,%.result,$(OK))
CCS = $(patsubst %.ok,%.cc,$(OK))
KERNELS = $(patsubst %.ok,%.kernel,$(OK))

PUBLIC=/u/gheith/public
PUBLIC_PATH=${PUBLIC}/bin
PUBLIC_LDPATH=${PUBLIC}/lib/expect5.45

all : t0.kernel

test : $(RESULTS);

$(TESTS) : % :

$(KERNELS) : %.kernel :
	(cd kernel; rm -f kernel.cc)
	(cd kernel; ln -s ../$*.cc kernel.cc)
	(cd kernel; make clean)
	(cd kernel; make)
	
$(RAWS) : %.raw : .FORCE %.kernel
	-env LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:${PUBLIC_LDPATH} PATH=$$PATH:${PUBLIC_PATH} timeout 20 expect e0.tcl > $*.raw

.FORCE:
	
$(OUTS) : %.out : .FORCE %.raw
	grep  '^\*\*\*' $*.raw > $*.out 2>&1

$(DIFFS) : %.diff : .FORCE %.out
	diff -wBb $*.out $*.ok > $*.diff 2>&1 || true

$(RESULTS) : %.result : .FORCE %.diff
	@echo -n "--- $* ... "
	@(test -s $*.diff && (echo "fail ---" ; echo "look for clues in $*.raw, $*.out, $*.ok, $*.cc"; echo "--- expected ---" ; cat $*.ok; echo "--- found ---" ; cat $*.out)) || (echo "pass ---")

% :
	(make -C kernel $@)

clean:
	rm -rf *.out *.raw *.diff *.result
	(make -C kernel clean)
