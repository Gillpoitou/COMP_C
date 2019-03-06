# COMP_C

## PRÉSENTATION DU PROJET

## TECHNOLOGIES

## STRUCTURE

Il y a un dossier par sprint nommé SprintX avec X = numéro du sprint
Chacun de ces dossiers contient le fichier de grammaire, l'exécutable et un dossier nommé comme son parent, dans lequel se trouve les fichier C++ (générés par antlr4 ou écrit à la main)

## MANUEL

Les commandes ci-dessous sont à exécuter à la racine du projet

### ANTLR4
L'utilisation de ANTLR4 pour générer des fichiers C++ à partir de l'analyse de la grammaire se fait avec un script shell qui execute la commande suivante (il faudrait pouvoir passer le numéro du sprint en paramètre):

      antlr4 -visitor -no-listener -Dlanguage=Cpp -o <DossierDuSprint> <DossierDuSprint>/<NomDeLaGrammaire>.g4

### COMPILATION
La compilation se fait à l'aide d'un autre script shell qui exécute la commande suivante

      clang++ -g -std=c++11 -I antlr4-cpp-runtime-4/antlr4-runtime/ -o <DossierDuSprint>/exe <DossierDuSprint>/<DossierDuSprint>/*.cpp antlr4-cpp-runtime-4/lib/libantlr4-runtime.a

### EXECUTION
L'execution s'effectue avec un nouveau script shell utilisant la commande suivante :

      <DossierDuSprint>/exe
