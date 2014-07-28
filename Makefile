
# 
# Copyright (c) 2014 Philipp Paulweber
# 
# This file is part of the 'libcasm-rt' project which is released under a NCSA
# open source software license. For more information, see the LICENSE.txt 
# file in the project root directory.
# 

STDLL_DIR   = ../stdll

GTEST_DIR   = ../gtest
GTEST_OBJ   = uts/obj

.PHONY: include llvm uts

default: help

help:
	@echo "usage: make <OPTION>"
	@echo
	@echo "OPTION: help       prints this help message"
	@echo "        clean      removes all generated object files"
	@echo "        llvm       link all llvm IR files to a llvm single"
	@echo "                   byte-code object file"
	@echo "        test       run the unit test suite"

clean:
	rm -f casm-rt*.bc
	rm -f $(GTEST_OBJ)/*

llvm: casm-rt.bc

casm-rt.bc:
	llvm-link llvm/*.ll > $@


test: $(GTEST_OBJ) $(GTEST_OBJ)/gtest
	@echo "===--- UNIT TEST SUITE ---==="
	./$(GTEST_OBJ)/gtest

GTEST_FLAGS  = -Wall 
GTEST_FLAGS += -Wextra 
GTEST_FLAGS += -I ${GTEST_DIR} 
GTEST_FLAGS += -I $(GTEST_DIR)/include 
GTEST_FLAGS += -I include 
GTEST_FLAGS += -I $(STDLL_DIR)/include

GTEST_CPP  = $(wildcard uts/utc/*.cpp)
GTEST_CPP += $(GTEST_DIR)/src/gtest-all.cc
GTEST_CPP += $(GTEST_DIR)/src/gtest_main.cc

GTEST_OBJS = $(addprefix $(GTEST_OBJ)/,$(notdir \
		$(patsubst %.cc,%.ll,\
		$(patsubst %.cpp,%.ll,$(GTEST_CPP)))))

GTEST_LL  = llvm/*.ll
GTEST_LL += $(STDLL_DIR)/llvm/*.ll

$(GTEST_OBJ):
	@mkdir -p uts/obj

$(GTEST_OBJ)/gtest: $(GTEST_OBJS) $(GTEST_LL)
	llvm-link $(GTEST_OBJS) $(GTEST_LL) > $@.ll
	llc -O3 $@.ll -o $@.s
	clang -lstdc++ -pthread $@.s -o $@ 

$(GTEST_OBJ)/%.ll: uts/utc/%.cpp
	clang $(GTEST_FLAGS) -emit-llvm -S $< -o $@

$(GTEST_OBJ)/%.ll: $(GTEST_DIR)/src/%.cc
	clang $(GTEST_FLAGS) -emit-llvm -S $< -o $@






