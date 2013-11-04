#!//bin/bash
## loop the length of segments

##
## different length of segments


rm length.txt
rm timestep.txt
rm loading_freq.txt

for length in 1000 5000 10000 20000 500000 100000
do

echo "length $length" >> length.txt

for loop in {1..10}
do

./Release/traffic_sim 86400 2 $length 8 1 0 >> length.txt

done ##end of loop
echo "-----------------------------" >> length.txt

done ##end of loop length

echo "========================================"
echo "========================================"
echo "========================================"

##
##different time set
for timestep in 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
do

echo "time $timestep" >> timestep.txt

for loop in {1..10}
do

./Release/traffic_sim 86400 $timestep 5000 8 1 0 >> timestep.txt

done ##end of loop
echo "-----------------------------" >> timestep.txt

done ##end of loop length

echo "========================================"
echo "========================================"
echo "========================================"

##
##different time set
for loading_freq in 1 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
do

echo "loading_freq $loading_freq" >> loading_freq.txt

for loop in {1..10}
do

./Release/traffic_sim 86400 2 5000 $loading_freq 1 0 >> loading_freq.txt

done ##end of loop
echo "-----------------------------" >> loading_freq.txt

done ##end of loop length
