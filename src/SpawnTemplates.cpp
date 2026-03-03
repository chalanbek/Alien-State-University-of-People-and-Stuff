#include "SpawnTemplates.h"
#include <stdio.h>
void SpawnTemplates::chooseTemplate(int *floorNumber, int *x, int *y){
    int choosenTemplateNum = SDL_rand(templatesNum);
    SpawnTemplate choosenTemplate = templates[choosenTemplateNum];
    *floorNumber = choosenTemplate.floorNumber;
    *x = choosenTemplate.x;
    *y = choosenTemplate.y;
}