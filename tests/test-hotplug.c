/*
 * libusbmuxd.c
 *
 * Copyright (C) 2018 Christophe Fergeau <cfergeau@redhat.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "usbmuxd.h"
#include <assert.h>
#include <stdio.h>
#include <unistd.h>

static void hotplug_cb1(const usbmuxd_event_t *event, void *user_data)
{
	int *flags = user_data;
	printf("%s(%d): %d\n", __func__, event->event, *flags);
	assert((*flags & 1) == 0);
	*flags |= 1;
}

int main(int argc, char **argv)
{
	int flags;

	usbmuxd_subscribe(hotplug_cb1, &flags);

	printf("Plug in iDevice\n");
	flags = 0;
	while (flags != 1) {
		usleep(100000);
	}

	return 0;
}
