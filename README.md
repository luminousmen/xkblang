Xkblang
======

Xkblang is a simple program for getting current keyboard layout. Primarily this program was written for [i3blocks](https://github.com/vivien/i3blocks) blocklet for getting current layout.

### Installation

The only dependency is libX11.
```Makefile
$ make
$ sudo make install
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