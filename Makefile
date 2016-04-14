#   
#   Copyright (c) 2014-2016 CASM Organization
#   All rights reserved.
#   
#   Developed by: Philipp Paulweber
#                 https://github.com/ppaulweber/libcasm-rt
#   
#   This file is part of libcasm-rt.
#   
#   libcasm-rt is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#   
#   libcasm-rt is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
#   
#   You should have received a copy of the GNU General Public License
#   along with this program. If not, see <http://www.gnu.org/licenses/>.
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

# TARGET += libcasm-rt.a
# CPPOBJECTS += obj/Backend.o
# CPPOBJECTS += obj/LLCodeBackend.o
# INCLUDE += -I ../
# INCLUDE += -I ../casm-ir/src/

LLSRC += llvm/type.ll
LLSRC += llvm/bool.ll
LLSRC += llvm/int.ll
LLSRC += llvm/str.ll
LLSRC += llvm/updateset.ll
LLSRC += llvm/update.ll
LLSRC += llvm/rule.ll

STDLL_DIR   = ../stdll
GTEST_DIR   = ../gtest
GTEST_OBJ   = uts/obj

.PHONY: include llvm uts

default: help
# default: obj $(TARGET)

# obj:
# 	mkdir -p obj

# obj/%.o: src/%.cpp
# 	@echo "CPP " $<
# 	@$(CPP) $(CPPFLAG) $(INCLUDE) -c $< -o $@

# $(TARGET): $(CPPOBJECTS)
# 	@echo "AR  " $@
# 	@$(AR) rsc $@ $(filter %.o,$^)
# 	@ranlib $@

clean:
#	@echo "RM  " obj
#	@rm -rf obj
#	@echo "RM  " $(TARGET)
#	@rm -f $(TARGET)
	@rm -f casm-rt*.bc
	@rm -f casm-rt*.ll
	@rm -f casm-rt*.ir
#@rm -f $(GTEST_OBJ)/*


help:
	@echo "usage: make <OPTION>"
	@echo
	@echo "OPTION: help       prints this help message"
	@echo "        clean      removes all generated object files"
	@echo "        llvm       link all llvm IR files to a llvm single"
	@echo "                   byte-code object file"
	@echo "        test       run the unit test suite"

# c11: obj libcasm-rt.c11.a

# libcasm-rt.c11.a: obj/bool.o
# 	@echo "AR  " $@
# 	@$(AR) rsc $@ $(filter %.o,$^)
# 	@ranlib $@
# 	@$(CC) $(CCFLAG) -o obj/main $@

# obj/%.o: c11/%.c
# 	@echo "CC  " $<
# 	@$(CC) $(CCFLAG) $(INCLUDE) -c $< -o $@
# 	@$(CC) $(CCFLAG) -S $(INCLUDE) -c $< -o $@.s
# 	@$(CC) -std=c11 -O3 -S $(INCLUDE) -c $< -o $@.O3.s




llvm: casm-rt

casm-rt: $(STDLL_DIR)/stdll.ll $(LLSRC)
	cat $(STDLL_DIR)/stdll.ir $(LLSRC) > $@.ir
	llvm-link $@.ir -S -o $@.ll
	opt $@.ll -o $@.bc

#	llvm-link llvm/*.ll -S -o $@.ll
#	opt $@.ll -o $@.bc
#	grep -r $@.ll -e "attributes" > $@.ir
#	grep -r $@.ll -e "declare" >> $@.ir
#	grep -r $@.ll -e "type" >> $@.ir
#	grep -r $@.ll -e "define linkonce_odr" | \
#		sed "s/define linkonce_odr/declare/g" | \
#		sed "s/{//g" >> $@.ir

stdll: $(STDLL_DIR)/stdll.bc

$(STDLL_DIR)/stdll.ll:
	$(MAKE) llvm -C $(STDLL_DIR)

test: llvm $(GTEST_OBJ) $(GTEST_OBJ)/gtest
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

GTEST_LL  = casm-rt.ll

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






