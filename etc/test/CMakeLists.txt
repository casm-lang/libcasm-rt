#
#   Copyright (C) 2014-2024 CASM Organization <https://casm-lang.org>
#   All rights reserved.
#
#   Developed by: Philipp Paulweber et al.
#   <https://github.com/casm-lang/libcasm-rt/graphs/contributors>
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
#   along with libcasm-rt. If not, see <http://www.gnu.org/licenses/>.
#
#   Additional permission under GNU GPL version 3 section 7
#
#   libcasm-rt is distributed under the terms of the GNU General Public License
#   with the following clarification and special exception: Linking libcasm-rt
#   statically or dynamically with other modules is making a combined work
#   based on libcasm-rt. Thus, the terms and conditions of the GNU General
#   Public License cover the whole combination. As a special exception,
#   the copyright holders of libcasm-rt give you permission to link libcasm-rt
#   with independent modules to produce an executable, regardless of the
#   license terms of these independent modules, and to copy and distribute
#   the resulting executable under terms of your choice, provided that you
#   also meet, for each linked independent module, the terms and conditions
#   of the license of that module. An independent module is a module which
#   is not derived from or based on libcasm-rt. If you modify libcasm-rt, you
#   may extend this exception to your version of the library, but you are
#   not obliged to do so. If you do not wish to do so, delete this exception
#   statement from your version.
#

include_directories(
  ${PROJECT_BINARY_DIR}/src
  ${LIBGTEST_INCLUDE_DIR}
  ${LIBSTDHL_INCLUDE_DIR}
  ${LIBPASS_INCLUDE_DIR}
  ${LIBCASM_IR_INCLUDE_DIR}
  )

add_library( ${PROJECT}-test OBJECT
  main.cpp
  builtin/assert.cpp
  builtin/as/string/enumeration.cpp
  builtin/as/string/integer.cpp
  builtin/as/string/boolean.cpp
  builtin/as/string/binary.cpp
  builtin/as/string/string.cpp
  builtin/as/string/decimal.cpp
  builtin/as/string/rational.cpp
  builtin/as/integer/integer.cpp
  builtin/as/integer/boolean.cpp
  builtin/as/integer/binary.cpp
  builtin/as/boolean/integer.cpp
  builtin/as/boolean/boolean.cpp
  builtin/as/boolean/binary.cpp
  builtin/at/list.cpp
  builtin/abort.cpp
  builtin/println.cpp
  builtin/print.cpp
  builtin/size/enumeration.cpp
  builtin/size/list.cpp
  builtin/size/range.cpp
  constant/integer.cpp
  instruction/gth/integer.cpp
  instruction/leq/integer.cpp
  instruction/or.cpp
  instruction/add/integer.cpp
  instruction/add/string.cpp
  instruction/lth/integer.cpp
  instruction/geq/integer.cpp
  instruction/xor.cpp
  instruction/and.cpp
  instruction/equ.cpp
  instruction/imp.cpp
  instruction/inv/integer.cpp
  instruction/not.cpp
  type/integer.cpp
  )
