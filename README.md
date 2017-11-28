# Arduino 7seg display test code for Platformio

[mattsan/arduino_7seg_test](https://github.com/mattsan/arduino_7seg_test) を [Platformio](http://platformio.org) でビルドできるようにしたものです。

[C-552SR-NW-A G/W](http://akizukidenshi.com/catalog/g/gI-00215/) を制御するためのコードを [mattsan/C-552SR-NW-A](https://github.com/mattsan/C-552SR-NW-A) に分離しています。

## 準備

Platformio をインストールします。

macOS の場合、Homebrew を使ってインストールできます。

```sh
$ brew install platformio
```


## ビルドと書き込み

```sh
$ git@github.com:mattsan/arduino_7seg_test_platformio.git
$ cd arduino_7seg_test_platformio
$ platformio run -t upload
```
