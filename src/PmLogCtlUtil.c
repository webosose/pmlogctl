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
 ***********************************************************************
 * @file PmLogCtlUtil.c
 *
 * @file This file contains generic utility functions.
 *
 ***********************************************************************
 */


#include "PmLogCtl.h"

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


/**
 * @brief mystrcpy
 *
 * Easy to use wrapper for strcpy to make it safe against buffer
 * overflows and to report any truncations.
 */
void mystrcpy(char *dst, size_t dstSize, const char *src)
{
	size_t  srcLen;

	if (dst == NULL)
	{
		ErrPrint("mystrcpy null dst\n");
		return;
	}

	if (dstSize < 1)
	{
		ErrPrint("mystrcpy invalid dst size\n");
		return;
	}

	dst[ 0 ] = 0;

	if (src == NULL)
	{
		ErrPrint("mystrcpy null src\n");
		return;
	}

	srcLen = strlen(src);

	if (srcLen >= dstSize)
	{
		ErrPrint("mystrcpy buffer overflow on '%s'\n", src);
		srcLen = dstSize - 1;
	}

	memcpy(dst, src, srcLen);
	dst[ srcLen ] = 0;
}


/**
 * @brief mystrcat
 *
 * Easy to use wrapper for strcat to make it safe against buffer
 * overflows and to report any truncations.
 */
void mystrcat(char *dst, size_t dstSize, const char *src)
{
	size_t  dstLen;
	size_t  srcLen;
	size_t  maxLen;

	if (dst == NULL)
	{
		ErrPrint("mystrcat null dst\n");
		return;
	}

	if (dstSize < 1)
	{
		ErrPrint("mystrcat invalid dst size\n");
		return;
	}

	dstLen = strlen(dst);

	if (dstLen >= dstSize)
	{
		ErrPrint("mystrcat invalid dst len\n");
		return;
	}

	if (src == NULL)
	{
		ErrPrint("mystrcat null src\n");
		return;
	}

	srcLen = strlen(src);

	if (srcLen < 1)
	{
		/* empty string, do nothing */
		return;
	}

	maxLen = (dstSize - 1) - dstLen;

	if (srcLen > maxLen)
	{
		ErrPrint("mystrcat buffer overflow\n");
		srcLen = maxLen;
	}

	if (srcLen > 0)
	{
		memcpy(dst + dstLen, src, srcLen);
		dst[ dstLen + srcLen ] = 0;
	}
}


/**
 * @brief mysprintf
 *
 * Easy to use wrapper for sprintf to make it safe against buffer
 * overflows and to report any truncations.
 */
void mysprintf(char *dst, size_t dstSize, const char *fmt, ...)
{
	va_list         args;
	int             n;

	if (dst == NULL)
	{
		ErrPrint("mysprintf null dst\n");
		return;
	}

	if (dstSize < 1)
	{
		ErrPrint("mysprintf invalid dst size\n");
		return;
	}

	dst[ 0 ] = 0;

	if (fmt == NULL)
	{
		ErrPrint("mysprintf null fmt\n");
		return;
	}

	va_start(args, fmt);

	n = vsnprintf(dst, dstSize, fmt, args);

	if (n < 0)
	{
		ErrPrint("mysprintf error\n");
		dst[ 0 ] = 0;
	}
	else if (((size_t) n) >= dstSize)
	{
		ErrPrint("mysprintf buffer overflow\n");
		dst[ dstSize - 1 ] = 0;
	}

	va_end(args);
}


/**
 * @brief PrvGetIntLabel
 *
 * Look up the string label for a given integer value from the given
 * mapping table.  Return NULL if not found.
 */
const char *PrvGetIntLabel(const IntLabel *labels, int n)
{
	const IntLabel *p;

	for (p = labels; p->s != NULL; p++)
	{
		if (p->n == n)
		{
			return p->s;
		}
	}

	return NULL;
}


/**
 * @brief PrvLabelToInt
 *
 * Look up the integer value matching a given string label from the
 * given mapping table. Return NULL if not found.
 */
const int *PrvLabelToInt(const IntLabel *labels, const char *s)
{
	const IntLabel *p;

	for (p = labels; p->s != NULL; p++)
	{
		if (strcmp(p->s, s) == 0)
		{
			return &p->n;
		}
	}

	return NULL;
}
