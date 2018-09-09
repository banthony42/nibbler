# Nibbler - Terminé - VelocityPulse & banthony42

Note finale : 105/100

## Description
**Ce projet de C++ vous fait recoder le jeu Snake avec plusieurs interfaces graphiques différentes; le joueur devant pouvoir switcher entre les interfaces pendant le jeu. C'est l'occasion de voir comment charger et utiliser des bibliothèques dynamiques au runtime.**

## Librairies disponibles 
* OpenGL
* SFML
* SDL

## UML
### Aperçu
[![uml](https://github.com/VelocityPulse/nibbler/raw/master/uml/uml_screen.png)](https://github.com/VelocityPulse/nibbler/raw/master/uml/UML.pdf)

[link](https://github.com/banthony42/nibbler/blob/master/uml/UML.pdf?raw=true)

## Installation & Execution 
Disponible uniquement sur macOS

Dépendances : 
- git
- make
- brew

### Compilation 
`cd project && ./configure make`
### Execution 
`./nibbler`

Usage : `./nibbler [-size Width Height] [-lib pathLib]`

Il est possible de changer de librairies pendant l'éxecution du programme. Toute fois vous pouvez selectionner une librairie au run-time en précisant son path. 
Path disponibles :
* libOpenGL/libgraph.so
* libSFML/libgraph.so
* libSDL/libgraph.so

