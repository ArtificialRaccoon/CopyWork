# CopyWork
A curses based "copywork" tool.  Allows you to perform copywork on a textfile in the terminal.

![Demo](https://github.com/ArtificialRaccoon/CopyWork/blob/main/demo.gif)

# What is Copywork?

Copywork is the practice of manually transcribing an author's work, word by word, to supposedly absorb the author's style through repetition.

It is very likely to be pseudoscience in my opinion. It does have one tangible use: apprication of an author's style.  This may, or may not, help you to improve your own writing.

# Why did you fart this out?

Honestly, I wanted to give copyworking a shot; but every copywork tool I ran into was a god awful webapp.  Each one was laggy, and honestly, I hate when simple things require a god damn webbrowser.

# Building

## Windows

If you're on Windows, you can build this easily using VSCode.  Just make sure you have VCPKG installed, and built PDCurses.  As long as VCPKG is in your path, it should get picked up.

Or just use prebuilt binary.

## Linux

Assuming your using a Debian based distro, just install ncurses, configure, and make:

```
sudo apt-get install libncurses-dev
mkdir build
cd build
cmake ..
cmake --build .
```

