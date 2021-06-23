
g++ -std=c++17 genTopSpin.cpp -o genTopSpin

./genTopSpin 12 4 > topSpin12_4.psvn
./genTopSpin 14 4 > topSpin14_4.psvn
./genTopSpin 17 4 > topSpin17_4.psvn

rm genTopSpin