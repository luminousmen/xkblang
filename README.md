Xkblang
======
[![Build Status](https://travis-ci.org/luminousmen/xkblang.svg?branch=master)](https://travis-ci.org/luminousmen/xkblang)

Xkblang is a simple program for getting current keyboard layout. Primarily this program was written for [i3blocks](https://github.com/vivien/i3blocks) blocklet for getting current layout.

### Installation

Xkblang written on pure C. The only dependency is libX11.

```bash
$ make
$ sudo make install
```
OR
with deb packet:
```bash
$ dpkg -i xkblang_1.0-1.deb
```

### Usage

```bash
$ xkblang -p
English (US)

```
For short version:
```bash
$ xkblang -ps
En

```
To list all available layouts:
```bash
$ xkblang -l
0. English (US)
1. Russian

```

To set layout:
```bash
$ xkblang -t 0

```