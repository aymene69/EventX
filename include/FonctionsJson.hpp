/********************************************************************
    created:	2023-11-22
    file path:	include/FonctionsJson.hpp
    author:		W.I.P.
    copyright:	UNLICENSE

    purpose: W.I.P.
*********************************************************************/

#ifndef FONCTIONSJSON_HPP
#define FONCTIONSJSON_HPP
#include <iostream>

bool verifDate(std::string date);

void ajouterEvent(void* object);
void ajouterParticip(void* object, int index);
void ajouterStand(void* object, int index);
void ajouterManager(void* object, int index, int indexs);

void modifierEvent(void* object, int index);
void modifierParticip(void* object, int index, int indexp);
void modifierStandd(void* object, int index, int indexs);
void modifierManag(void* object, int index, int indexs, int indexm);

void supprimerEvent(void* object, int index);
void supprimerParticip(int index, int indexp);
void supprimerStandd(int index, int indexs);
void supprimerManag(int index, int indexs, int indexm);

#endif
