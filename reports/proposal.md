# Emu Wars: A CHIP-8 Emulator

**Annabelle Platt**

## Goals

The goal of this project is to create a [CHIP-8 emulator](https://en.wikipedia.org/wiki/CHIP-8) that can successfully play Pong and other 8-bit games. As a stretch goal, it would be great to add nice debugging capabilities or upgrade to support SUPER-CHIP, which increases the resolution and adds a bit more functionality. 

## Learning Goals

My learning goals are to become more comfortable working with C on the hardware level. This project is great for that because not only will I be working on the hardware level with C but also literally emulating the hardware of another system. 

I would also like there to be a visual component to my project. Since part of the emulator is the display, I will be able to achieve this as well. 

## Resources

Writing CHIP-8 emulators is almost universally recommended as a first emulation project and as such is extremely well documented. There are also many other simple emulator builds out there which contain similar concepts that will be useful. Below are a few of the resources I've found: 

* [Guide to Making a CHIP-8 Emulator](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/): a language agnostic process walkthrough that provides good concepts and pseudocode but leaves the implementation up to you
* [Emulator 101](http://www.emulator101.com/): guide to making an arcade game emulator but has tutorials for many concepts that will be useful for emulation in general
* [How to write an emulator (CHIP-8 interpreter)](https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/): another walkthrough, this time focused in C but again providing mostly pseudocode and leaving the implementation to the reader
* [Writing a CHIP-8 Emulator](http://craigthomas.ca/category/emulation.html): another walkthrough, this one a bit more detail-oriented and less high-level concepts. Unfinished but has some useful content
* [Write Your Own Virtual Machine](https://justinmeiners.github.io/lc3-vm/): since an emulator runs similarly to a virtual machine in some ways, this has some very helpful concepts. It's also written in C and has a Github repo I can reference if I get stuck. 

## First Steps 

First, I need to set up the memory and the registers. Next, I need to set up the font and the display. I will then need to implement a stack data structure of some kind. At some point I will need to register user keystrokes, which is not something I'm already familiar with in C so that will be a good learning experience. 