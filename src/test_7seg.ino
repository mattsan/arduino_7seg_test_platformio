#include <TimerOne.h>
#include "digit.h"

// 加算/減算切り替えボタンの入力ピン番号
const int BUTTON = 8;

// 回るセグメントの定義
static const byte CYCLE_SEGS[4][2] = {
  {B00001000, B00000001},
  {B00010000, B00000010},
  {B00100000, B00000100},
  {B00000001, B00001000}
};

// ボタンの以前の状態
int prev_button_state = LOW;

int digit = 0;           // 7seg 二桁で表示する数値
int point_state = 0;     // 7seg の小数点の表示状態
int cycle_pos = 0;       // 回るセグメントの位置情報
boolean cycling = false; // 回転表示の場合に true 

// タイマのコールバック関数
void callback() {
  // 小数点の表示状態のを更新する
  point_state = (point_state + 1) % 10;

  // 回るセグメントの位置情報を更新する
  cycle_pos = (cycle_pos + 1) % 4;

  // 小数点表示状態が 0 に戻ったとき、数値に増分を加える
  // 0.1 秒毎に更新され、10 回で 0 に戻るので、1 秒毎に加算される
  if (point_state == 0) {
    digit = (digit + 1) % 60;
  }
}

// 初期化
void setup() {
  // 加算/減算切り替えボタンのピンを入力に指定する
  pinMode(BUTTON, INPUT);

  // 7seg 制御の状態を初期化する
  digitInit();

  // タイマを 100,000 usec で初期化する
  Timer1.initialize(100000);
  // タイマにコールバック関数を設定する
  Timer1.attachInterrupt(callback);
}

// メインループ
void loop() {
  // ボタンの状態を取得する
  int button_state = digitalRead(BUTTON);

  // ボタンの状態が以前の状態と異なり、かつ、ボタンが押されている場合
  if (prev_button_state != button_state && button_state == HIGH) {
    // 回るセグメントを表示するか数値を表示するかの状態を切り替える
    cycling = !cycling;

    // 回るセグメント表示がオフになり数値表示に切り替わるときに、数値に乱数値を設定する
    if (!cycling) {
      digit = random(0, 60);
    }
  }

  // 現在のボタンの状態を保存する
  prev_button_state = button_state;

  if (cycling) {
    // 回るセグメントの場合

    // 左のセグメントを表示する
    digitWriteSegments(FIGURE_1, CYCLE_SEGS[cycle_pos][0]);
    delay(10);
    // 右のセグメントを表示する
    digitWriteSegments(FIGURE_2, CYCLE_SEGS[cycle_pos][1]);
    delay(10);
  } else {
    // 数値表示の場合

    // 10 の位を表示する
    digitWrite(FIGURE_1, digit / 10, point_state >= 5);
    delay(10);
    // 1 の位を表示する（小数点は 10 の位の状態と ON/OFF を反対にする）
    digitWrite(FIGURE_2, digit % 10, point_state < 5);
    delay(10);
  }
}
