./ubuntu_runmake.sh -j8
./compiler/build/ifcc ./demo/life.c > ./demo/life.s
gcc -o ./demo/exe-life ./demo/life.s
./demo/exe-life