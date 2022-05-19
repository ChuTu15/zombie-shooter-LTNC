#ifndef CREATEBGR_H_INCLUDED
#define CREATEBGR_H_INCLUDED

#pragma once
#include "zombie.h"

using namespace sf;

int createBackground(VertexArray& rVA, IntRect arena);
zombie* createHorde(int numZom, IntRect arena);

#endif // CREATEBGR_H_INCLUDED
