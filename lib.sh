export LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH
gcc -o test test.c -I./ -L./ -lrobot -lwiringPi