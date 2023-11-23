#ifndef FONCTIONSJSON_HPP
#define FONCTIONSJSON_HPP
#include <iostream>

bool verifDate(std::string date);

void ajouterEvent(void* object);
void ajouterParticip(void* object, int index);
//void ajouterStand(void* object, int index);
//void ajouterManager(void* object, int index);

void modifierEvent(void* object, int index);
void modifierParticip(void* object, int index, int indexp);
//void modifierStand(void* object, int index);
//void modifierManager(void* object, int index);

void supprimerEvent(void* object, int index);
void supprimerParticip(int index, int indexp);
//void supprimerStand(void* object, int index);
//void supprimerManager(void* object, int index);

#endif
