#include "global.h"

// the map that players choose, counting from 1 to ...
int game_map;

// the minions' name
char ArmyClass[][30] = {"Saber", "Saber1", "Saber2", "Saber3", "Saber4", "Saber5", "Saber6", "Saber7", "Saber8", "Saber9"};

// the towers' name
char TowerClass[][30] = {"MajorTower", "MinorTower"};

// the sound's classification is defined in GameWindow.h
double background_sound_volume = 1.0; // control the volume of all the background sound
double effect_sound_volume = 1.0; // control the volume of all the effect sound
