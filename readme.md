# Osu!++
## Preview

[![Preview](https://img.youtube.com/vi/mqm8GpgQXaM/0.jpg)](http://www.youtube.com/watch?v=mqm8GpgQXaM)

## how to build and run 
### 1) Install make command

install choco ->[there](https://chocolatey.org/install)<-
then type `choco install make`

### 2) Install MinGW 7.3.0 (DW2) - 32-bit

1. download it ->[there](https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit.zip)<-
   then extract it somewere on your disk

2. add the /bin folder to PATH environment variable
   ex: my mingw is installed on C:/mingw32
   -> I should add C:/mingw32/bin to path env var
   -> [indian guy ytb tutorial](https://youtu.be/guM4XS43m4I?t=320) <-

### 3) Build & run your game

put your code in src/main.cpp file
simply type `make game` :)