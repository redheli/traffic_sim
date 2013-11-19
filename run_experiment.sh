#!//bin/bash
## loop the length of segments

##
## different length of segments


rm length.txt
rm timestep.txt
rm loading_volumn.txt

for length2 in 100 200 500 1000 2000 5000 10000 20000 50000
do

echo "length $length2" >> length.txt

for loop in {1..10}
do

./Debug/traffic_sim 86400 2 $length2 48000 0 >> length.txt

done ##end of loop
echo "-----------------------------" >> length.txt

done ##end of loop length

echo "========================================"
echo "========================================"
echo "========================================"

##
##different time set
for timestep2 in 2 4 6 8 10 12 14 16 18 20 22 24 32
do

echo "time $timestep2" >> timestep.txt

for loop in {1..10}
do

##echo "./Debug/traffic_sim 7200 $timestep2 5000 4000 0"
./Debug/traffic_sim 86400 $timestep2 5000 48000 0 >> timestep.txt

done ##end of loop
echo "-----------------------------" >> timestep.txt

done ##end of loop length

echo "========================================"
echo "========================================"
echo "========================================"

##
##different time set
for loading_volumn2 in 1000 2000 5000 10000 20000 50000 100000
do

echo "loading_volumn $loading_volumn2" >> loading_volumn.txt

for loop in {1..10}
do

./Debug/traffic_sim 86400 2 5000 $loading_volumn2 0 >> loading_volumn.txt

done ##end of loop
echo "-----------------------------" >> loading_volumn.txt

done ##end of loop length
