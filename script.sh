#!/bin/bash

# Compilation du programme
make re || { echo "Compilation failed"; exit 1; }

echo "==== TESTS PHILOSOPHERS ===="

#!/bin/bash

# Exécute le programme et enregistre la sortie
./philo 5 800 200 200 7 > output.log

# Compte le nombre de fois où "x is eating" apparaît
grep -oE '[0-9]+ : is eating' output.log | awk '{count[$1]++} END {for (philo in count) print "Philosophe " philo+1 " a mangé " count[philo] " fois."}' | sort -n -k2

# Test 1 : 5 philosophes, ils doivent tous manger sans mourir
echo "Test 1: 5 philosophes, 800 ms pour mourir, 200 ms pour manger, 200 ms pour dormir, 7 repas"
./philo 5 800 200 200 7 | grep "died" && echo "❌ Échec" || echo "✅ Succès"

# Test 2 : Philosophe seul, il doit mourir après time_to_die
echo "Test 2: 1 philosophe, doit mourir après 310 ms"
./philo 1 310 200 100 | grep "died" && echo "✅ Succès" || echo "❌ Échec"

# Test 3 : Synchronisation correcte avec plus de philosophes
echo "Test 3: 4 philosophes, gestion des fourchettes correcte"
./philo 4 410 200 200 5 | grep "died" && echo "❌ Échec" || echo "✅ Succès"

# Test 4 : Vérification du deadlock
echo "Test 4: 5 philosophes, valeurs proches, pas de deadlock"
timeout 10 ./philo 200 600 200 200 | grep "died" && echo "❌ Deadlock détecté" || echo "✅ Pas de deadlock"

# Test 5 : Timing serré, vérifie si un philosophe meurt
echo "Test 5: 5 philosophes, time_to_die trop court"
./philo 5 200 100 100 | grep "died" && echo "✅ Un philosophe est mort, comportement normal" || echo "❌ Erreur, il devrait mourir"

echo "Tests terminés."

rm output.log
