cd src
pc main.c pcx.c sprite.c bug.c msdos.c /o..\obj\
cd ..
del bin\chrome_bug.exe
move obj\main.exe bin\chrome_bug.exe
