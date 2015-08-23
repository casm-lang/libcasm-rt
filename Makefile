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

AR=ar

CC=clang
CCFLAG += -std=c11
CCFLAG += -g -O0
CCFLAG += -Wall

CPP=clang
CPPFLAG += -std=c++11
CPPFLAG += -g -O0
CPPFLAG += -Wall
#CPPFLAG += -Wextra

TARGET += libcasm-rt.a

CPPOBJECTS += obj/Backend.o
CPPOBJECTS += obj/LLCodeBackend.o

INCLUDE += -I ../
INCLUDE += -I ../casm-ir/src/


STDLL_DIR   = ../stdll
GTEST_DIR   = ../gtest
GTEST_OBJ   = uts/obj

.PHONY: include llvm uts

default: obj $(TARGET)

obj:
	mkdir -p obj

obj/%.o: src/%.cpp
	@echo "CPP " $<
	@$(CPP) $(CPPFLAG) $(INCLUDE) -c $< -o $@

$(TARGET): $(CPPOBJECTS)
	@echo "AR  " $@
	@$(AR) rsc $@ $(filter %.o,$^)
	@ranlib $@

clean:
	@echo "RM  " obj
	@rm -rf obj
	@echo "RM  " $(TARGET)
	@rm -f $(TARGET)
	@rm -f casm-rt*.bc
	@rm -f casm-rt*.ll
#@rm -f $(GTEST_OBJ)/*


help:
	@echo "usage: make <OPTION>"
	@echo
	@echo "OPTION: help       prints this help message"
	@echo "        clean      removes all generated object files"
	@echo "        llvm       link all llvm IR files to a llvm single"
	@echo "                   byte-code object file"
	@echo "        test       run the unit test suite"


llvm: casm-rt

casm-rt: llvm/*.ll
	llvm-link llvm/*.ll -S -o $@.ll
	opt $@.ll -o $@.bc
	grep -r $@.ll -e "attributes" > $@.ir
	grep -r $@.ll -e "declare" >> $@.ir
	grep -r $@.ll -e "type" >> $@.ir
	grep -r $@.ll -e "define linkonce_odr" | \
		sed "s/define linkonce_odr/declare/g" | \
		sed "s/{//g" >> $@.ir

stdll: $(STDLL_DIR)/stdll.bc

$(STDLL_DIR)/stdll.bc:
	$(MAKE) llvm -C $(STDLL_DIR)

test: stdll llvm $(GTEST_OBJ) $(GTEST_OBJ)/gtest
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

GTEST_LL  = casm-rt.bc
GTEST_LL += $(STDLL_DIR)/stdll.bc

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






