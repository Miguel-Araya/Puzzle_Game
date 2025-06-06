#include "raylib.h"
#include <time.h>

#ifndef FIGURE_H
#define FIGURE_H

#define FIGURE_SIZE 64

typedef struct Figure {
  int id;
} Figure;

void printFigure(struct Figure *figureList, int size){

  for (int i = 0; i < size; i++){
        
    printf("\nID figure %d", figureList[i].id);

  }
    
}

//change texturePuzzle copy by a reference
void getFigure(Texture2D texturePuzzle, int idFigure, Rectangle *sourceRect){

  //also add the type of the figure assign to a variable
  int limitLineX = texturePuzzle.width/FIGURE_SIZE;

  int positionY = idFigure/limitLineX;

  int positionX = idFigure-(positionY*limitLineX);

  sourceRect->x =  positionX*FIGURE_SIZE;

  sourceRect->y = positionY*FIGURE_SIZE;

}

void randomAssignFigure(struct Figure *figureList, int totalFigure){
  
  srand(time(NULL));
  int randomIndex = 0;

  int idAvailable[totalFigure];

  for (int i = 0; i < totalFigure; i++) {

    idAvailable[i] = i;

  }

  for (int i = 0; i < totalFigure; i++) {
    randomIndex = rand() % (totalFigure - i);
    figureList[i].id = idAvailable[randomIndex];

    idAvailable[randomIndex] = idAvailable[totalFigure - i - 1];
  }
  
}

void getSolveFigure(struct Figure *solveFigureList,struct Figure **figureList, int idFigure, int totalFigure, int solveFigureTotal){
  
  int indexDelete = -1;

  struct Figure *newFigureList = (struct Figure *)malloc((totalFigure-1) * sizeof(struct Figure));

  for (int i = 0; i < totalFigure; i++)
  {
    
    if((*figureList)[i].id == idFigure){
      solveFigureList[solveFigureTotal] = (*figureList)[i];
      indexDelete = i;
      break;
    }

    newFigureList[i] = (*figureList)[i];

  }
  
  for (int i = indexDelete+1; i < totalFigure; i++)
  {
    
    newFigureList[i-1] = (*figureList)[i];

  }
  
  free(*figureList);

  *figureList = newFigureList;

}

#endif