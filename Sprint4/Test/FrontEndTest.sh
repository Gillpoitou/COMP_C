
#!/bin/bash

Tester(){
	echo "Execution"
	./main $name
}
clear
menu=( $(find ./FrontEndTests/ -maxdepth 1 -type d) )
j=0
for i in ${menu[@]};
do 
	echo $j $i;
	j=$(($j + 1))
done
echo 'Choisir le dossier de test (-1 tous)'
read choice

if [ $choice -ne -1 ]
then
chemin=${menu[choice]}
echo $chemin
liste=( $(find $chemin -maxdepth 1 -type f) )
j=0
for i in ${liste[@]};
do 
echo $j $i;
j=$(($j + 1))
done
echo 'Choisir le test (-1 tous)'
read choice
if [ $choice -ne -1 ]; 
then
chemin=${liste[choice]}
fi
fi

liste=( $(find $chemin -maxdepth 2 -type f) )
j=0
for i in ${liste[@]};
do 
	echo $i;
	# Tester($i)
done


exit 0
