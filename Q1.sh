#!/bin/bash

_notreadinif=1										 ## flag to read file 

if [ $# -ne 1 ]										 ## Checking if number of arguments are correct
then												 ## If wrong usage, then force to enter filename
	echo "Normal usage is <Q1.sh> <filename> but i'am letting you to keep"
	echo -n 'Enter the file name: '
	read _filename
	_notreadinif=0
fi

if [[ _notreadinif -eq 1 ]]							## Check if correct argument
then 
	_filename=$1; 									## Get the first argument
fi


while IFS= read -r line || [[ -n "$line" ]]; do 	## Get the line in the file

    for word in $line; do 							## Get the word in the line

    	_uppercase=0
		_lowercase=0
		_totalnumberofdigits=0
		_totalnumberofothercharacters=0

    	for (( k=0; k<${#word}; k++ )); do 			## Get the character in the word

    		ch=${word:k:1};

    		if [[ $ch =~ [A-Z] ]]; then				## Upper case control
    			_uppercase=$((_uppercase + 1))
    		elif [[ $ch =~ [a-z] ]]; then 			## Lower case control
    			_lowercase=$((_lowercase + 1))
       	elif [[ $ch =~ [0-9] ]]; then			## Digit control
    			_totalnumberofdigits=$((_totalnumberofdigits + 1))
    		else
          _totalnumberofothercharacters=$((_totalnumberofothercharacters + 1))
    		fi

    	done

    	echo -n $_uppercase.$_lowercase.$_totalnumberofdigits.$_totalnumberofothercharacters' '
    
    done
echo ''
done < $_filename






