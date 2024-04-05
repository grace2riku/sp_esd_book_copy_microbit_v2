#include "MicroBit.h"
#include "Tests.h"
#include "../ntshell-v0.3.1/core/ntshell.h"
#include "usrcmd.h"

extern "C" {
    static int serial_read(char* buf, int cnt, void* extobj) {
        return uBit.serial.read((uint8_t*)buf, cnt);
    }

    static int serial_write(const char* text, int cnt, void* extobj) {
        uBit.serial.send((uint8_t*)text, cnt);
        return cnt;
    }

    static int user_callback(const char* text, void* extobj) {
        usrcmd_execute(text);
        return 0;
    }
}


// NT-Shellの初期化と実行
static void ntshell_task(void) {
    ntshell_t ntshell;
    ntshell_init(
        &ntshell,
        serial_read,
        serial_write,
        user_callback,
        NULL);
    ntshell_set_prompt(&ntshell, "NT-Shell> ");
    ntshell_execute(&ntshell);
}


void start_ntshell_task() {
    create_fiber(ntshell_task);
}
