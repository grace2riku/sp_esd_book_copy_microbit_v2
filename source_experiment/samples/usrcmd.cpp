/**
 * @file usrcmd.c
 * @author CuBeatSystems
 * @author Shinichiro Nakamura
 * @copyright
 * ===============================================================
 * Natural Tiny Shell (NT-Shell) Version 0.3.1
 * ===============================================================
 * Copyright (c) 2010-2016 Shinichiro Nakamura
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "ntopt.h"
#include "ntlibc.h"

#include "MicroBit.h"
#include "Tests.h"
#define uart_puts uBit.serial.send

#include <stdlib.h> // atoi

typedef int (*USRCMDFUNC)(int argc, char **argv);

static int usrcmd_ntopt_callback(int argc, char **argv, void *extobj);
static int usrcmd_help(int argc, char **argv);
static int usrcmd_info(int argc, char **argv);
static int usrcmd_setPixelValue(int argc, char **argv);

typedef struct {
    char *cmd;
    char *desc;
    USRCMDFUNC func;
} cmd_table_t;

static const cmd_table_t cmdlist[] = {
    { "help", "This is a description text string for help command.", usrcmd_help },
    { "info", "This is a description text string for info command.", usrcmd_info },
    { "setPixelValue", "This is a description text string for setPixelValue command.", usrcmd_setPixelValue },
};

int usrcmd_execute(const char *text)
{
    return ntopt_parse(text, usrcmd_ntopt_callback, 0);
}

static int usrcmd_ntopt_callback(int argc, char **argv, void *extobj)
{
    if (argc == 0) {
        return 0;
    }
    const cmd_table_t *p = &cmdlist[0];
    for (int i = 0; i < sizeof(cmdlist) / sizeof(cmdlist[0]); i++) {
        if (ntlibc_strcmp((const char *)argv[0], p->cmd) == 0) {
            return p->func(argc, argv);
        }
        p++;
    }
    uart_puts("Unknown command found.\r\n");
    return 0;
}

static int usrcmd_help(int argc, char **argv)
{
    const cmd_table_t *p = &cmdlist[0];
    for (int i = 0; i < sizeof(cmdlist) / sizeof(cmdlist[0]); i++) {
        uart_puts(p->cmd);
        uart_puts("\t:");
        uart_puts(p->desc);
        uart_puts("\r\n");
        p++;
    }
    return 0;
}

static int usrcmd_info(int argc, char **argv)
{
    if (argc != 2) {
        uart_puts("info sys\r\n");
        uart_puts("info ver\r\n");
        return 0;
    }
    if (ntlibc_strcmp(argv[1], "sys") == 0) {
        uart_puts("NXP LPC824 Monitor\r\n");
        return 0;
    }
    if (ntlibc_strcmp(argv[1], "ver") == 0) {
        uart_puts("Version 0.0.0\r\n");
        return 0;
    }
    uart_puts("Unknown sub command found\r\n");
    return -1;
}

static int usrcmd_setPixelValue(int argc, char **argv) {
    int16_t x, y;
    int brightness_level;

    if (argc != 4) {
        uart_puts("setPixelValue 0 0 255\r\n");
        return -1;
    }

    x = atoi(argv[1]);
    if (x < 0 || x > 4) {
        uart_puts("Error: led x 0-4.\r\n");
        return -1;
    }

    y = atoi(argv[2]);
    if (y < 0 || y > 4) {
        uart_puts("Error: led y 0-4.\r\n");
        return -1;
    }

    brightness_level = atoi(argv[3]);
    if (brightness_level < 0 || brightness_level > 255) {
        uart_puts("Error: brightness level 0-255.\r\n");
        return -1;
    }

    uBit.display.image.setPixelValue(x, y, (uint8_t)brightness_level);

    return 0;
}
