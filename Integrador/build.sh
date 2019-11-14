rm *.exe *.o test.db
g++ -Wall -std=c++11 -c "test.cpp"
g++ -Wall -std=c++11 -o "test.exe" "test.o" -lsqlite3
./test.exe
