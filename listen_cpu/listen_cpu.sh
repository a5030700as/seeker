#!/bin/bash

for each in {1..10}
do
    echo "hello $each"
done

wodiu=1
counter=0 
for ((;;))
do 
    echo  hello cpu
    #times=`top -b -n 1 | grep "^%[Cc]pu" | awk '$2+$4 >= 0.3 {print "1"; }'`
    times=`top -b -n 1 | grep "^[Cc][pP][uU]" | awk '{if($2+$4 >= 90.5) print "1"; else print "0";}'` 
    
    echo $times
    
    #top -b -n 1 | grep "^%[Cc]pu" | awk '$2+$4 >= 0.3 {print "cpu超出了"; system("wodiu=5")}'
    if [ $times -ge 1 ]
    then 
        let counter++
        echo "let $counter"   
    else
        counter=0;    
    fi
    if [ $counter -ge 10 ]
    then 
        echo "ready for reboot"
    fi    
    sleep 1
    times=0
done
