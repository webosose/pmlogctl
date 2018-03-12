# Copyright (c) 2011-2018 LG Electronics, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0

#
# pmlogctl/CMakeLists.txt
#

cmake_minimum_required(VERSION 2.8.7)

project(PmLogCtl C)

include(webOS/webOS)
webos_modules_init(1 0 0 QUALIFIER RC4)
webos_component(3 0 0)

include(FindPkgConfig)

# Check that we have PmLogLib
pkg_check_modules(PMLOGLIB REQUIRED PmLogLib)
include_directories(${PMLOGLIB_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${PMLOGLIB_CFLAGS_OTHER})

webos_add_compiler_flags(ALL -Wall -g)
webos_add_linker_options(ALL --no-undefined)

include_directories(src)
file(GLOB SOURCE_FILES src/*.c)
webos_configure_source_files(SOURCE_FILES src/PmLogView.c)

# Build the PmLogCtl executable
add_executable(PmLogCtl ${SOURCE_FILES})
target_link_libraries(PmLogCtl ${PMLOGLIB_LDFLAGS})

webos_build_program()
