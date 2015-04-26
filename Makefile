#   
#   Copyright (c) 2015 Philipp Paulweber
#   All rights reserved.
#   
#   Developed by: Philipp Paulweber
#                 https://github.com/ppaulweber/libcasm-rt
#   
#   Permission is hereby granted, free of charge, to any person obtaining a 
#   copy of this software and associated documentation files (the "Software"), 
#   to deal with the Software without restriction, including without limitation 
#   the rights to use, copy, modify, merge, publish, distribute, sublicense, 
#   and/or sell copies of the Software, and to permit persons to whom the 
#   Software is furnished to do so, subject to the following conditions:
#   
#   * Redistributions of source code must retain the above copyright 
#     notice, this list of conditions and the following disclaimers.
#   
#   * Redistributions in binary form must reproduce the above copyright 
#     notice, this list of conditions and the following disclaimers in the 
#     documentation and/or other materials provided with the distribution.
#   
#   * Neither the names of the copyright holders, nor the names of its 
#     contributors may be used to endorse or promote products derived from 
#     this Software without specific prior written permission.
#   
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
#   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
#   CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
#   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
#   WITH THE SOFTWARE.
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
GTEST_FLAGS += -I c
GTEST_FLAGS += -I ../

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






