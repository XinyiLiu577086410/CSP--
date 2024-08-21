#!bash
g++ ./baseline.cc -o baseline -std=c++11
g++ ./testee.cc -o testee -std=c++11
./baseline < ./treasure.in > baseline.out
./testee < ./treasure.in > testee.out
diff ./baseline.out ./testee.out 
