# EmuWars: A CHIP-8 Emulator

**Annabelle Platt**

## Goals:
The goal of this project is to build a [CHIP-8 Emulator](https://en.wikipedia.org/wiki/CHIP-8) virtual machine that can play Pong and other 8-bit games. 

My lower bound for this project is a functional CPU and basic graphics that can decode, execute, and appropriately display the 35 CHIP-8 opcodes. My middle goal, which I'm reasonably confident I can reach, is taking user input. My stretch goals are to add [Super CHIP-8 opcodes](https://en.wikipedia.org/wiki/CHIP-8#CHIP-8_extensions_and_variations) and increase the display size (Super CHIP-8 is a later system with slightly more functionality and a bigger display). My super stretch goal, if everything else gets accomplished, would be to include audio. 

## Learning Goals 
My learning goals for this project were to become more comfortable with C on the hardware level and to have a visual component to the project. 

I have already made significant progress towards my first goal. I feel like I have gained a much greater understanding of how systems like this function on a hardware level through simulating one in software. Now whenever I boot up a much more complex emulator like CEMU, I feel like I have a bit of a peak into what's happening inside. 

My second goal I have not yet made progress towards, but I will in the coming week as I implement my display using SDL. 

## Progress 

### Resource and Learning Progress
I have been primarily relying on a combination of [this](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/#dxyn-display) CHIP-8 conceptual explanation, [this](https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/) other conceptual explanation, [this](https://austinmorlan.com/posts/chip8_emulator/) C++ implementation, and [this](https://github.com/dmatlack/chip8) implementation on Github. I have been leaning most heavily on the C++ implementation for the logic, occasionally checking the Github implementation for some C-specific structural things. However, my project is structured differently from both projects and I am navigating those decisions on my own. I am balancing learning what I simply don't know from their implementations while challenging myself to impelement what I can on my own. As the project has gone on I've found myself less and less reliant on the actual code, and starting to shift more towards the conceptual explanations to challenge myself with the implemenation. 

### Technical Progress
So far I have set up the data structures of the CPU and written a function to initialize them, a function to load a game into memory, and a function to fetch and decode the next opcode (this function is not complete as I have not added the bulk of the switch statement for decoding). I am adding these functions to the main program loop as I go. I have also started writing opcode functions. These are extremely fun to write, as each one is a little puzzle that does a single chunk of something (some are more complex than others). Already I have become very comfortable with bitwise operators in a way I don't think I could have just from learning them in class. Most importantly, I have spent a good amount of time thinking about how best to structure my project and share code between all the files. 

## Current Work 
I have several tasks ongoing at the moment. They are:

* Building out the entire switch statement for decoding opcodes. This is done when all opcodes have been accounted for and any unknown opcodes will result in an error.
* Create a header file for the opcode functions and include it in the main loop. This also is done once all opcode functions are accounted for and actually needs to be done in order for the switch statement in the previous task to call these functions, but can still be done in parallel. 
* Successfully run the IBM logo program. This is a program that draws the IBM logo on the screen and then enters an infinite loop. It requires only a small number of opcodes and will help me ensure that all the basics of my system are working. Once this is done, all I should need to do is implement the rest of the opcodes. There are two things I need to do in order for this to happen: 
    * Implement the DXYN opcode. This is one of the most complex opcodes, which draws a sprite and deals with collisions between sprites. This is the last of the necessary opcodes for the IBM logo.
    * Implement simple graphics system. This is done when there is an init function, a quit function, and a draw function for the graphics, and they have been integrated into the main program loop. 

## Link to project
https://github.com/olincollege/SoftSysEmuWars 