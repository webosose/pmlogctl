// Copyright (c) 2007-2018 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

/**
 ************************************************************************
 * @file PmLogCtl.h
 *
 * @brief This file contains definitions used by PmLogCtl.
 *
 ***********************************************************************
 */


#ifndef PMLOGCTL_H
#define PMLOGCTL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/* Debugging/Error reporting utilities */

#define COMPONENT_PREFIX    "PmLogCtl: "

extern bool flag_silence;

#define DbgPrint(...) \
    {                                                       \
        fprintf(stdout, COMPONENT_PREFIX __VA_ARGS__);      \
    }

#define InfoPrint(...) \
{                                                       \
    if (!flag_silence)                                  \
        fprintf(stdout, COMPONENT_PREFIX __VA_ARGS__);  \
}

#define ErrPrint(...) \
    {                                                       \
        if (!flag_silence)                                  \
            fprintf(stderr, COMPONENT_PREFIX __VA_ARGS__);  \
    }


/*
 * 'safe' string manipulation functions.  Each function guarantees
 * the output buffer is not overflowed, and that it is null terminated
 * properly after (assuming it was beforehand).
 */


/**
 * @brief mystrcpy
 *
 * Easy to use wrapper for strcpy to make it safe against buffer
 * overflows and to report any truncations.
 */
void mystrcpy(char *dst, size_t dstSize, const char *src);


/**
 * @brief mystrcat
 *
 * Easy to use wrapper for strcat to make it safe against buffer
 * overflows and to report any truncations.
 */
void mystrcat(char *dst, size_t dstSize, const char *src);


/**
 * @brief mysprintf
 *
 * Easy to use wrapper for sprintf to make it safe against buffer
 * overflows and to report any truncations.
 */
void mysprintf(char *dst, size_t dstSize, const char *fmt, ...)
__attribute__((format(printf, 3, 4)));

/**
 * IntLabel
 *
 * Define an integer value => string label mapping.
 */
typedef struct
{
	const char *s;
	int         n;
}
IntLabel;


/**
 * @brief PrvGetIntLabel
 *
 * Look up the string label for a given integer value from the given
 * mapping table.  Return NULL if not found.
 */
const char *PrvGetIntLabel(const IntLabel *labels, int n);


/**
 * @brief PrvLabelToInt
 *
 * Look up the integer value matching a given string label from the
 * given mapping table.  Return NULL if not found.
 */
const int *PrvLabelToInt(const IntLabel *labels, const char *s);


typedef enum
{
    RESULT_OK,
    RESULT_PARAM_ERR,
    RESULT_RUN_ERR,
    RESULT_HELP
}
Result;


/**
 * @brief ParseFacility
 *
 * "user" => LOG_USER, etc.
 * @return true if parsed OK, else false.
 */
bool ParseFacility(const char *s, int *facilityP);


/**
 * @brief ParseLevel
 *
 * "err" => LOG_ERR, etc.
 * @return true if parsed OK, else false.
 */
bool ParseLevel(const char *s, int *levelP);


/**
 * @brief GetFacilityStr
 *
 * LOG_USER => "user", etc.  NULL if not recognized.
 */
const char *GetFacilityStr(int fac);


/**
 * @brief GetLevelStr
 *
 * LOG_ERR => "err", etc.  NULL if not recognized.
 */
const char *GetLevelStr(int level);


/**
 * @brief PmLogView.c
 */
Result DoCmdView(int argc, char *argv[]);


#endif /* PMLOGCTL_H */
