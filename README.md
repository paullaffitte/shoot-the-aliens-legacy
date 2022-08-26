# Shoot The Aliens 👾 (legacy)

A 2D space shooter 🔫

## Introduction

I developped this game a long time ago when I was at high school. It started on end of **February 2014**, at this time I knew a bit how to program, but I never had made a real project yet. This project came from my ambition to develop a finished and working game that I could share to my friends. I think this project is one of the main reasons for why I'm working in IT nowdays, I remember had thought to myself at this time "Well, it's damn hard, but I love it so much I'd like to make it my job".

At this time I wasn't using git at all, but fortunately I was quite curious enough so at least I tried a bit and made 1 single commit that *I never pushed anywhere* (I didn't know about GitHub & co at this time). The code stayed *8 years* on my hard-drive, moving from computer to another, from one backup drive to the next one, until a few days ago.. What was my surprise when I saw the `.git` in the game folder! So here it is, **my first ever git commit**, ressurected from ashes (actually from my old hard drives), created during the last days I spent on the project that ignited my passion for development.

## How close it is from the original game you developped 8 years ago?

It is the same exact source code, I just added a `CMakeLists.txt` file in order to build the project reliably. I also had to refactor a singleton to make it a normal class because for an unknown reason it made the game crash.

- [`ed3ca252e57d8594a68a05d23a2b5a5dc0a10633`](https://github.com/paullaffitte/shoot-the-aliens-legacy/commit/ed3ca252e57d8594a68a05d23a2b5a5dc0a10633) is my real first ever commit
- [`75576ebc7bca92daf0a2959413d292e1385aa3a1`](https://github.com/paullaffitte/shoot-the-aliens-legacy/commit/75576ebc7bca92daf0a2959413d292e1385aa3a1) contains the project the way it was when I stopped working on it 8 years ago, but I made this commit only recently
- Subsequent commits have been written after unearthing the project.

By the way, this is not the original readme, the original ones are [`README.txt`](https://github.com/paullaffitte/shoot-the-aliens-legacy/blob/main/README.txt) and [`LISEZMOI.txt`](https://github.com/paullaffitte/shoot-the-aliens-legacy/blob/main/LISEZMOI.txt).

## How to play it?

The easiest way is to download the installer on [itch.io/shootthealiens](https://paullaffitte.itch.io/shootthealiens).

Just in case I update the description of the page later (I would like to polish a bit my work and finally release a version 1.0.0 🙃), here is the original description on the itch.io page:

> Shoot The Aliens is an infinite procedural 2d shooter game. There is no goal except have fun an make the best high score ! :D
It's very simple, you play with arrow keys, and the space ship will shoot automatically.
>
> During the conception of this game, my two main inspiration were the very famous Flappy Bird and Space Invaders. So Shoot The Aliens is like the meeting between these two fantastic games. It's my first game so it was important for me to make a game with very simple mechanics but a lot of fun. I have done code, music, graphics, sounds and everything myself just with C++, SFML, a graphic editing software and an MAO software.
>
> This game is in beta for the moment, so there are perhaps some bugs. If you find one of them, you're welcome to report it.

## How to compile it ?

### Windows

- Download [SFML 2.5.1](https://www.sfml-dev.org/download/sfml/2.5.1/) for `Visual C++ 15 (2017) - 32-bit` and extract it.
- Run `cmake -S . -B build -DSFML_DIR=PATH_TO_SFML/lib/cmake/SFML`.
- Run `cmake --build build --config Release`
- Copy the output from `./build/Release` to current folder (it has to contains the `ressources` folder) and you're ready to go!

### Linux

- Install `libsfml` and `libsfml-dev`.
- Run `cmake -S . -B build -DSFML_DIR=/usr/local/lib/cmake/SFML/`
- Run `cmake --build build --config Release`
- Copy the output from `./build` to current folder and you're ready to go!
