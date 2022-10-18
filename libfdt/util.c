// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright 2011 The Chromium Authors, All Rights Reserved.
 * Copyright 2008 Jon Loeliger, Freescale Semiconductor, Inc.
 *
 * util_is_printable_string contributed by
 *	Pantelis Antoniou <pantelis.antoniou AT gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "libfdt.h"
#include "util.h"

int isprint(int c)
{
    if ((c >= '0' && c <= '9') || \
        (c >= 'a' && c <= 'z') || \
        (c >= 'A' && c <= 'A'))
        return true;

    return false;
}

bool util_is_printable_string(const void *data, int len)
{
	const char *s = data;
	const char *ss, *se;

	/* zero length is not */
	if (len == 0)
		return 0;

	/* must terminate with zero */
	if (s[len - 1] != '\0')
		return 0;

	se = s + len;

	while (s < se) {
		ss = s;
		while (s < se && *s && isprint((unsigned char)*s))
			s++;

		/* not zero, or not done yet */
		if (*s != '\0' || s == ss)
			return 0;

		s++;
	}

	return 1;
}

void utilfdt_print_data(const char *data, int len)
{
	int i;
	const char *s;

	/* no data, don't print */
	if (len == 0)
		return;

	if (util_is_printable_string(data, len)) {
		printf(" = ");

		s = data;
		do {
			printf("\"%s\"", s);
			s += strlen(s) + 1;
			if (s < data + len)
				printf(", ");
		} while (s < data + len);

	} else if ((len % 4) == 0) {
		const fdt32_t *cell = (const fdt32_t *)data;

		printf(" = <");
		for (i = 0, len /= 4; i < len; i++)
			printf("0x%08x%s", fdt32_to_cpu(cell[i]),
			       i < (len - 1) ? " " : "");
		printf(">");
	} else {
		const unsigned char *p = (const unsigned char *)data;
		printf(" = [");
		for (i = 0; i < len; i++)
			printf("%02x%s", *p++, i < len - 1 ? " " : "");
		printf("]");
	}
}
