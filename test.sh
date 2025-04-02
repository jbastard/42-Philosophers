#!/bin/bash

# Exécute le programme et enregistre la sortie
./philo 5 800 200 200 7 > output.log

# Compte le nombre de fois où "x is eating" apparaît
grep -oE '[0-9]+ : is eating' output.log | awk '{count[$1]++} END {for (philo in count) print "Philosophe " philo " a mangé " count[philo] " fois."}' | sort -n -k2