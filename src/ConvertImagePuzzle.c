#include <stdio.h>
#include <stdlib.h>
#include "figure.h"
#include "raylib.h"
#include "string.h"

//version to test
int main() {

    //SI SE HACE EL CAMBIO DE POSITION ENTONCES HACER EL CAMBIO EN LA VERSION FINAL
    // return 0;
    const int screenWidth = 800;
    const int screenHeight = 460;

    const int initPuzzle = 11;
    const int finalPuzzle = 11;
    //0 in loop
    //1 stop loop
    //-1 exit program
    short int status = 0; 

    // Inicializar Raylib
    InitWindow(screenWidth, screenHeight, "Dibujar Círculo en Porción de Imagen Original con Raylib");

    //SetTargetFPS(60);

    const int limitMinWidth = 299;
    const int limitMinHeight = 120;

    const int limitWidth = (screenWidth/FIGURE_SIZE)*FIGURE_SIZE;
    const int limitHeight = (screenHeight/FIGURE_SIZE)*FIGURE_SIZE;

    Texture2D textureOriginal;

    int imageWidth = 0;

    int imageHeight = 0;

    int minImageWidth = 0;

    int minImageHeight = 0;

    Image minPuzzleImage;

    char nameImage[35];
    char numParse[10];

    Image puzzleImage;
    Image imagenOriginal;
        
    for (int i = initPuzzle; i <= finalPuzzle; i++)
    {
        
        strcpy(nameImage, "../puzzle");
        sprintf(numParse, "%d", i);
        strcat(nameImage, numParse);
        strcat(nameImage, ".png");
        
        // Cargar la imagen original
        imagenOriginal = LoadImage(nameImage);

        textureOriginal = LoadTextureFromImage(imagenOriginal);
        //hacer logica
        puzzleImage = ImageCopy(imagenOriginal);

        imageWidth = textureOriginal.width > limitWidth ? limitWidth : ((textureOriginal.width)/FIGURE_SIZE)*FIGURE_SIZE;
        imageHeight = textureOriginal.height > limitHeight ? limitHeight : ((textureOriginal.height)/FIGURE_SIZE)*FIGURE_SIZE;

        minImageWidth = ( imageWidth/2 < limitMinWidth ? imageWidth/2 : limitMinWidth);
        minImageHeight = ( imageHeight/2 < limitMinHeight ? imageHeight/2 : limitMinHeight);

        minPuzzleImage = GenImageColor(minImageWidth, minImageHeight, BLANK);

        ImageCrop(&puzzleImage, (Rectangle){0,0, imageWidth, imageHeight}); 

        ImageDraw(&minPuzzleImage, puzzleImage, (Rectangle){0,0,imageWidth, imageHeight},(Rectangle){0,0,minImageWidth, minImageHeight}, WHITE);

        strcpy(nameImage, "../puzzle/puzzleImage");
        //sprintf(numParse, "%d", i);
        strcat(nameImage, numParse);
        strcat(nameImage, ".png");

        ExportImage(puzzleImage, nameImage);

        //printf(nameImage);
        
        strcpy(nameImage, "../puzzle/minPuzzleImage");
        //sprintf(numParse, "%d", i);
        strcat(nameImage, numParse);
        strcat(nameImage, ".png");

        ExportImage(minPuzzleImage, nameImage);

        UnloadImage(puzzleImage);
        UnloadImage(imagenOriginal);

        while (status == 0) {
            // Actualizar

            // Dibujar
            BeginDrawing();

            ClearBackground(RAYWHITE);

            // Dibujar la textura con el círculo en la porción de la imagen
            
            DrawTextureRec(textureOriginal, (Rectangle){0,0,imageWidth, imageHeight}, (Vector2){0,0}, WHITE);

            DrawText("Click to see the next image", 0, 0, 50, MAGENTA);

            EndDrawing();

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){

                status = 1;

            }

            if(WindowShouldClose()) status = -1;

        }
        
        UnloadTexture(textureOriginal);

        if(status == -1) break;
        
        status = 0;

    }

    CloseWindow();

    return 0;
}