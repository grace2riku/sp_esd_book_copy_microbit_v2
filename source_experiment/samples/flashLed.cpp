#include "MicroBit.h"
#include "Tests.h"


// LED を点滅させる関数
static void flashLed() {
    int x, y;

    while (true) {
        for (y = 0; y < 5;y++) {
            for (x = 0;x < 5;x++) {
                uBit.display.image.setPixelValue(x, y, 255); // LED をオン
                uBit.sleep(500); // 500ms 待機
                uBit.display.image.setPixelValue(x, y, 0); // LED をオフ
                uBit.sleep(500); // 500ms 待機
            }
        }

//        uBit.display.image.setPixelValue(2, 2, 255); // LED をオン
//        uBit.sleep(100); // 100ms 待機
//        uBit.display.image.setPixelValue(2, 2, 0); // LED をオフ
//        uBit.sleep(100); // 100ms 待機
    }
}


void start_flashLed() {
    // flashLed 関数を新しい Fiber として起動
    create_fiber(flashLed);
}
