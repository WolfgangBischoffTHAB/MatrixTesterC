# Msys2: install gcc

```
pacman -S mingw-w64-ucrt-x86_64-gcc
```

gcc.exe is installed to C:\msys64\mingw64\bin
Add it to the path environment variable

```
set PATH=%PATH%;C:\msys64\mingw64\bin\
```

# Copy the Makefile template

https://github.com/TheNetAdmin/Makefile-Templates/blob/master/SmallProject/Template/Makefile

# Compile an application

```
gcc main.c
```

or use the Makefile

```
make
```