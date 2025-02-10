Hello, welcome to my humble game.

This runs in VSCODE

In order to run it, you only need to find where your compiler is located at.

If you have downloaded this, do check inside .vscode/c_cpp_properties.json and change the "compilerPath": "C:/MinGW/x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev0/mingw64/bin/gcc.exe", to the location of your compiler.

next, go to .vscode/tasks.json and change "command": "C:/MinGW/x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev0/mingw64/bin/g++.exe", to once again to your compiler.
then, this "detail": "compile: C:/MinGW/x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev0/mingw64/bin/g++.exe".

once everything is done, press CTRL+SHIFT+B and after a few moments press F5.

it should run, have fun!
