/* SPDX-License-Identifier: MIT OR X11
 *
 * Copyright © 2024 Enrico Weigelt, metux IT consult <info@metux.net>
 */
#include <dix-config.h>

#include "dix/dix_priv.h"
#include "include/dix.h"
#include "include/screenint.h"
#include "include/scrnintstr.h"
#include <stdio.h> // for snprintf
#include <stdlib.h>
#include <string.h>

const char *display = "0";
int displayfd = -1;

const char *dixGetDisplayName(ScreenPtr *pScreen)
{
    // Use new entry displayName if it exists
    if (pScreen && (*pScreen)->displayName)
		return (*pScreen)->displayName;

    return display;
}

void dixSetDisplayName(ScreenPtr pScreen, const char *name)
{
    if (!pScreen)
        return;

    // Safe copy of a str
    if (pScreen->displayName)
        free((void *)pScreen->displayName);

    pScreen->displayName = strdup(name ? name : "0");
}


void dixSetDisplayNameAuto(ScreenPtr pScreen)
{
    if (!pScreen)
        return;

    if (pScreen->displayName) {
        free(pScreen->displayName);
        pScreen->displayName = NULL;
    }

    char buf[64];
    snprintf(buf, sizeof(buf), "Display-%d", pScreen->myNum); // myNum — номер экрана
    pScreen->displayName = strdup(buf);
}
