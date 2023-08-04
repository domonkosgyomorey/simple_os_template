# Simple 32bit OS template
## Description
A little abstracted 32bit OS template with some function.

This repo is help me to develop some custom OS stuff. Example a game or something else.

But I would like to expand this project a modular way, so I can put moduls what I need in a sertain project.

Attension !<br>
In the x86_64 folder has the hardware specific code<br>
For whos want run this code on other platform

_This repo is not an OS dev tutorial, just my personal experiace with this topic. If you want to learn more on these pls look the link below in the [referencies](#referencies) section._

## Tested on these
I wrote this OS on Linux (Debian)<br>
My machine is x86_64<br>
I was not tested on other OS or hardwares


## Dependencies
( At least for my Makefile )
- Assembler: [nasm](https://www.nasm.us/)
- Compiler: [gcc](https://gcc.gnu.org/)
- Linker: [ld (GNU linker)](https://linux.die.net/man/1/ld)
- hardware emulation: [qemu](https://www.qemu.org/)
- [GNU make](https://www.gnu.org/software/make/)

## Some features
- Very basic memory protection (GDT with flat model)
- Interaction with hardware throught IO ports
- Basic libc, with some function
- Basic keyboard handling with callback abstraction
- VGA Text graphics ( 80x25 )
- It has a timer and its own callback which invoke when the PIT "clock"
- Callbacks for interrupt exceptions
- It build a modular way for separation the backend
- The main kernel when you can initialize that you need
- A basic separated shell (a bit buggy yet).

## How to compile and run
Just compile:
```console
make
```
Compile and run:
```console
make run
```
Clean all the bin file, except os_img:
```console
make clean
```
## Shell preview
![Shell preview](./img/preview.jpg)

## Referencies
- [A little book about os](https://littleosbook.github.io/)
- [Writing a Simple Operating System —
from Scratch pdf](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
- [Os dev wiki](https://wiki.osdev.org/Expanded_Main_Page)
- [Write my own bootloader](https://dev.to/frosnerd/writing-my-own-boot-loader-3mld)