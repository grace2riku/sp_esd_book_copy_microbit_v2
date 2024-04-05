#include "MicroBit.h"
#include "samples/Tests.h"

MicroBit uBit;


int main() {
    // micro:bit 初期化
    uBit.init();
    
    // LED点滅開始
//    start_flashLed();

    start_ntshell_task();

    // main タスクは何か他の作業をするか、または単に終了しないように待機します
    release_fiber();
}
