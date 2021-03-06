/*===- InstrProfilingPlatformLinux.c - Profile data Linux platform ------===*\
|*
|*                     The LLVM Compiler Infrastructure
|*
|* This file is distributed under the University of Illinois Open Source
|* License. See LICENSE.TXT for details.
|*
\*===----------------------------------------------------------------------===*/

#if defined(__linux__) || defined(__FreeBSD__) || \
    (defined(__sun__) && defined(__svr4__))

#include <stdlib.h>

#include "InstrProfiling.h"

#define PROF_DATA_START INSTR_PROF_SECT_START(INSTR_PROF_DATA_SECT_NAME)
#define PROF_DATA_STOP INSTR_PROF_SECT_STOP(INSTR_PROF_DATA_SECT_NAME)
#define PROF_NAME_START INSTR_PROF_SECT_START(INSTR_PROF_NAME_SECT_NAME)
#define PROF_NAME_STOP INSTR_PROF_SECT_STOP(INSTR_PROF_NAME_SECT_NAME)
#define PROF_CNTS_START INSTR_PROF_SECT_START(INSTR_PROF_CNTS_SECT_NAME)
#define PROF_CNTS_STOP INSTR_PROF_SECT_STOP(INSTR_PROF_CNTS_SECT_NAME)
#define PROF_VNODES_START INSTR_PROF_SECT_START(INSTR_PROF_VNODES_SECT_NAME)
#define PROF_VNODES_STOP INSTR_PROF_SECT_STOP(INSTR_PROF_VNODES_SECT_NAME)

/* Declare section start and stop symbols for various sections
 * generated by compiler instrumentation.
 */
extern __llvm_profile_data PROF_DATA_START COMPILER_RT_VISIBILITY;
extern __llvm_profile_data PROF_DATA_STOP COMPILER_RT_VISIBILITY;
extern uint64_t PROF_CNTS_START COMPILER_RT_VISIBILITY;
extern uint64_t PROF_CNTS_STOP COMPILER_RT_VISIBILITY;
extern char PROF_NAME_START COMPILER_RT_VISIBILITY;
extern char PROF_NAME_STOP COMPILER_RT_VISIBILITY;
extern ValueProfNode PROF_VNODES_START COMPILER_RT_VISIBILITY;
extern ValueProfNode PROF_VNODES_STOP COMPILER_RT_VISIBILITY;

/* Add dummy data to ensure the section is always created. */
__llvm_profile_data
    __prof_data_sect_data[0] COMPILER_RT_SECTION(INSTR_PROF_DATA_SECT_NAME_STR);
uint64_t
    __prof_cnts_sect_data[0] COMPILER_RT_SECTION(INSTR_PROF_CNTS_SECT_NAME_STR);
char __prof_nms_sect_data[0] COMPILER_RT_SECTION(INSTR_PROF_NAME_SECT_NAME_STR);
ValueProfNode __prof_vnodes_sect_data[0] COMPILER_RT_SECTION(INSTR_PROF_VNODES_SECT_NAME_STR);

COMPILER_RT_VISIBILITY const __llvm_profile_data *
__llvm_profile_begin_data(void) {
  return &PROF_DATA_START;
}
COMPILER_RT_VISIBILITY const __llvm_profile_data *
__llvm_profile_end_data(void) {
  return &PROF_DATA_STOP;
}
COMPILER_RT_VISIBILITY const char *__llvm_profile_begin_names(void) {
  return &PROF_NAME_START;
}
COMPILER_RT_VISIBILITY const char *__llvm_profile_end_names(void) {
  return &PROF_NAME_STOP;
}
COMPILER_RT_VISIBILITY uint64_t *__llvm_profile_begin_counters(void) {
  return &PROF_CNTS_START;
}
COMPILER_RT_VISIBILITY uint64_t *__llvm_profile_end_counters(void) {
  return &PROF_CNTS_STOP;
}

COMPILER_RT_VISIBILITY ValueProfNode *
__llvm_profile_begin_vnodes(void) {
  return &PROF_VNODES_START;
}
COMPILER_RT_VISIBILITY ValueProfNode *__llvm_profile_end_vnodes(void) {
  return &PROF_VNODES_STOP;
}
COMPILER_RT_VISIBILITY ValueProfNode *CurrentVNode = &PROF_VNODES_START;
COMPILER_RT_VISIBILITY ValueProfNode *EndVNode = &PROF_VNODES_STOP;

#endif
